#include "FirstAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "DataRegistritionSvc/DataRegistritionSvc.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "Event/PhyHeader.h"
#include "Event/PhyEvent.h"
#include "TFile.h"
#include "TTree.h"
//#include "event.cc"


#ifdef WITH_G4OPTICKS
#error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
#endif

#include "DataCollSvc/IDataCollSvc.h"
static IDataCollSvc* m_datacollsvc;
static std::string key;
#include "JunoTimer/IJunoTimerSvc.h"
#include "JunoTimer/JunoTimer.h"
static IJunoTimerSvc* m_timersvc;
static JunoTimerPtr fill_array;
static JunoTimerPtr clear_vector;
static JunoTimerPtr push_vector;
static JunoTimerPtr mem_set;


DECLARE_ALGORITHM(FirstAlg);

FirstAlg::FirstAlg(const std::string& name)
    : AlgBase(name),
      m_count(0)
{
    declProp("TheValue", m_value = 1);
    declProp("Message",  m_msg);
    declProp("Thetype",m_type=1);
}

bool FirstAlg::initialize()
{
     SniperPtr<IDataCollSvc> _datacollsvc(this->getParent(), "DataCollSvc");
    if (_datacollsvc.invalid()) {
        LogError << "Can't Locate DataCollSvc. If you want to use it, please "
                 << "enalbe it in your job option file."
                 << std::endl;
    }
    m_datacollsvc = _datacollsvc.data();

   SniperPtr<IJunoTimerSvc> _timersvc(this->getParent(), "JunoTimerSvc");
    if (_timersvc.invalid()) {
        LogError << "Can't Locate JunoTimerSvc. If you want to use it, please "
                 << "enalbe it in your job option file."
                 << std::endl;
    }
    m_timersvc = _timersvc.data();
    fill_array = m_timersvc->get("fill_array");
    clear_vector=m_timersvc->get("clear_vector");
    push_vector=m_timersvc->get("push_vector");
    mem_set=m_timersvc->get("mem_set");
  
    LogDebug << "in the FirstAlg::initialize()" << std::endl;
    return true;
}

 bool FirstAlg::execute()
{
   fill_array->start();      
   for(int i=0;i<2000000;i++)
     {
       a[i]=0;
       b[i]=0;
       c[i]=0;
       d[i]=0;
       e[i]=0;
     }
   fill_array->stop(); 
   key = "fill_array";
   m_datacollsvc->collectData(key, fill_array->elapsed());

   clear_vector->start();
   
        v_a.clear();        
        v_b.clear();
        v_c.clear();
        v_d.clear();
        v_e.clear();
   clear_vector->stop();
   key="clear_vector";
   m_datacollsvc->collectData(key, clear_vector->elapsed());
 
   push_vector->start();   
     for(int i=0;i<2000000;i++)
      {
         v_a.push_back(1);  
         v_b.push_back(1);
         v_c.push_back(1);
         v_d.push_back(1);
         v_e.push_back(1);
      }
   push_vector->stop();
   key="push_vector";
    m_datacollsvc->collectData(key, push_vector->elapsed());

  
   mem_set->start();
   memset(a,0,2000000*sizeof(double));
   memset(b,0,2000000*sizeof(double));
   memset(c,0,2000000*sizeof(double));
   memset(d,0,2000000*sizeof(double));
   memset(e,0,2000000*sizeof(double));
   mem_set->stop();
   key="mem_set";
   m_datacollsvc->collectData(key, mem_set->elapsed());
 //   LogDebug << "in the FirstAlg::execute()" << std::endl;
        
 //  /* ++m_count;
 //   m_value *= m_count;
 //   LogInfo << "Loop " << m_count << m_msg << m_value << std::endl;*/
 //   std::cout<<"m_value="<<m_value<<std::endl;
 //   std::cout<<"m_type="<<m_type<<std::endl;

 //   
 //   TFile* f=new TFile("tree1.root","recreate");
 //  // f->SetCompressionLevel(0);
 //   TTree * t1=new TTree("nphotons","nphotons"); 
 //   system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
 //  // t1->SetAutoSave(15000000);  
 //  if(m_type==1)
 //   {
 //   int num=m_value*10000000;  
 //   double *p=new double[num];
 //   t1->Branch("num",&num,"num/I");
 //   t1->Branch("E",p,"E[num]/D",3200000);
 //  // system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
 //   for(int i=0;i<num;i++)
 //    {
 //     *(p+i)=20;
 //    }
 //   system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
 //   }
 //  if(m_type==2)
 //   {
 //      JM::SimEvent* sim_event = new JM::SimEvent(10);
 //      int num=m_value*1000000;
 //      t1->Branch("event_branch","SimEvent",sim_event,320,1);
 //      for(int i=0;i<=num;i++)
 //      {
 //        JM::SimPMTHit* sim_hit = sim_event->addCDHit();  
 //        sim_hit->setPMTID(20);
 //        sim_hit->setHitTime(200);
 //        sim_hit->setLocalTheta(0.6);
 //        sim_hit->setLocalPhi(0.6);
 //        sim_hit->setNPE(1);     
 //      }     
 //      
 //      JM::SimTrack* jm_trk = sim_event->addTrack();
 //        jm_trk->setPDGID(1);
 //        jm_trk->setTrackID(1);
 //        jm_trk->setInitPx(0);
 //        jm_trk->setInitPy(0);
 //        jm_trk->setInitPz(0);
 //        jm_trk->setInitMass(0);
 //        jm_trk->setInitX(0);
 //        jm_trk->setInitY(0);
 //        jm_trk->setInitZ(0);
 //        jm_trk->setInitT(0);
 //      system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");

 //   }     
 //   

 //// system("/junofs/users/huyuxiang/juno/offline/Examples/FirstAlg/src/test.sh");   
 //// sleep(10); 

 ///*  std::cout<<"hello world"<<std::endl;
 // event *evt=new event(); 
 //  std::cout<<"hello world"<<std::endl; 
 // t1.Branch("branch_hit","event",&evt,32000,1);
 // std::cout<<"hello world"<<std::endl;
 //   for(int i=0; i<100;i++)
 //     {
 //       evt->add_hittime(3);
 //     }*/
 // 
 //  // t1->AutoSave();
 //   
 //   t1->Fill();
 // // sleep(20);
 //  // t1->AutoSave();

 //  //delete[]  p;
 //  system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh"); 
 // // sleep(10);
 // f->Write();  
 // //f->Write(0,0,8);
 //  system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
 //  f->Close();
 // // delete[]  p;
   return true;
}

bool FirstAlg::finalize()
{
    LogDebug << "in the FirstAlg::finalize()" << std::endl;
  //  sleep(10);
    return true;
}
   
   
