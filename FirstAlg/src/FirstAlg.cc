#include "FirstAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "DataRegistritionSvc/DataRegistritionSvc.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "Event/PhyHeader.h"
#include "Event/PhyEvent.h"

#ifdef WITH_G4OPTICKS
#error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
#endif

DECLARE_ALGORITHM(FirstAlg);

FirstAlg::FirstAlg(const std::string& name)
    : AlgBase(name),
      m_loop(0)
{
    declProp("EvtTimeGap", m_gap = 200000);  //nano second
    //RunMode: 0, nothing to do; 1, reading; 2, generating;
    declProp("RunMode",    m_mode = 0);  
}

bool FirstAlg::initialize()
{
    LogDebug << "initializing" << std::endl;

    SniperDataPtr<JM::NavBuffer>  navBuf(getParent(), "/Event");
    if ( navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = navBuf.data();

    // ... Only For Generating
    if ( m_mode == 2 ) {
        SniperPtr<DataRegistritionSvc> drSvc(getParent(), "DataRegistritionSvc");
        if ( drSvc.invalid() ) {
            LogError << "Failed to get DataRegistritionSvc instance!"
                     << std::endl;
            return false;
        }
        drSvc->registerData("JM::PhyEvent", "/Event/PhyEvent");
    }

    return true;
}

bool FirstAlg::execute()
{
    if ( m_mode == 1 ) {  //reading
        LogDebug << "reading: " << m_loop++
                 << "  buffer_size: " << m_buf->size()
                 << "  cur: " << m_buf->curEvt()->TimeStamp()
                 << std::endl;
    }
    else if ( m_mode == 2 ) {
        //make a dummy EvtNavigator
        JM::EvtNavigator* nav = new JM::EvtNavigator();
        static TTimeStamp time(2014, 7, 20, 10, 10, 2, 111);
        time.Add(TTimeStamp(0, int(abs(m_r.Gaus(m_gap, m_gap/5)))));
        nav->setTimeStamp(time);

        //TODO: register the EvtNavigator to Memory Store
        SniperPtr<IDataMemMgr> mMgr(getParent(), "BufferMemMgr");
        mMgr->adopt(nav, "/Event");

        //set headers and events ...
        JM::PhyEvent* event = new JM::PhyEvent();
        event->setEnergy(m_r.Gaus(10,3));
        event->setRawEvis(m_r.Gaus(8,2));
        event->setEnrec(m_r.Gaus(12,3));
        event->setEprec(m_r.Gaus(12,3));
        JM::PhyHeader* header = new JM::PhyHeader();
        header->setEvent(event);
        nav->addHeader("/Event/PhyEvent", header);

        LogDebug << "executing: " << m_loop++
                 << "  buffer_size: " << m_buf->size()
                 << std::endl;
    }
    //else, mode 0 nothing to do

    return true;
}

bool FirstAlg::finalize()
{
    LogDebug << "finalizing" << std::endl;
    return true;
}
