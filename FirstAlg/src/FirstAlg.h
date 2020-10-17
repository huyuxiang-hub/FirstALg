#ifndef FIRST_ALG_H
#define FIRST_ALG_H

#include "SniperKernel/AlgBase.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"


#include "Event/SimHeader.h"
#include "Event/SimEvent.h"


namespace JM {
    class SimEvent;
}
//#include "event.h"

//class event;
class FirstAlg : public AlgBase
{
    public:
        FirstAlg(const std::string& name);  //constructor

        bool initialize();
        bool execute();
        bool finalize();

    private:
        unsigned int  m_count;  //the count of event loop
        int           m_value;  //an int property
        std::string   m_msg;    //a string property
        int          m_type;
};

#endif
