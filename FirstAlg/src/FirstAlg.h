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
        
        std::vector<double> v_a;
        std::vector<double> v_b;
        std::vector<double> v_c;
        std::vector<double> v_d;
        std::vector<double> v_e;

        double a[4000000];
        double b[4000000];
        double c[4000000];
        double d[4000000];
        double e[4000000];
        
  
};

#endif
