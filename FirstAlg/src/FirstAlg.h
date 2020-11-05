#ifndef FIRST_ALG_H
#define FIRST_ALG_H

#include "SniperKernel/AlgBase.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"

class FirstAlg : public AlgBase
{
    public :

        FirstAlg(const std::string& name);

        bool initialize();
        bool execute();
        bool finalize();

    private :

        int m_loop;
        int m_gap;
        int m_mode;

        JM::NavBuffer* m_buf;
        TRandom        m_r;
};

#endif
