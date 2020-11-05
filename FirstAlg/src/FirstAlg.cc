#include "FirstAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "DataRegistritionSvc/DataRegistritionSvc.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "Event/PhyHeader.h"
#include "Event/PhyEvent.h"
#include "TFile.h"
#include "TTree.h"

//#include "G4VProcess.hh"
#include "Randomize.hh"
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
    declProp("type2-branch-buffer",m_2_branch_buffer=32000);
    declProp("type1-compress",m_1_compress_flag=0);
    declProp("type2-compress",m_2_compress_flag=0);
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
    
    sim_evt.clear();
    file_name.push_back("tree0.root");
    file_name.push_back("tree1.root");
    file_name.push_back("tree2.root"); 
   
    loop_count=1;
    
    return true;
}

 bool FirstAlg::execute()
{
     
   if(m_type==3)
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

   }
  
   LogDebug << "in the FirstAlg::execute()" << std::endl;
   std::cout<<"m_value="<<m_value<<std::endl;
   std::cout<<"m_type="<<m_type<<std::endl;
  
 
  if(m_type==1)
   {
   TFile* f=new TFile("tree1.root","recreate");
   TTree * t1=new TTree("nphotons","nphotons");
   //system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
   if(m_1_compress_flag==1)
     {
       f->SetCompressionLevel(0);
     }
   int num=m_value*1000000;  
   double *p=new double[num];
   t1->Branch("num",&num,"num/I");
   t1->Branch("E",p,"E[num]/D",32000);
   for(int i=0;i<num;i++)
    {
     *(p+i)=G4UniformRand();
    }
   system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
   
   t1->Fill();
  // system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");  
   f->Write();
   system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
   f->Close(); 
   
   }
  if(m_type==2)
   {
      TFile* f=new TFile("tree1.root","recreate");
      TTree * t1=new TTree("nphotons","nphotons");
     
      if(m_2_compress_flag==1)
        {
          f->SetCompressionLevel(0);
        }   

      JM::SimEvent* sim_event = new JM::SimEvent(10);
      int num=m_value*1000000;
      t1->Branch("event_branch","SimEvent",sim_event,m_2_branch_buffer,1);
      for(int i=0;i<=num;i++)
      {
        JM::SimPMTHit* sim_hit = sim_event->addCDHit();  
        sim_hit->setPMTID(i);
        sim_hit->setHitTime(G4UniformRand());
        sim_hit->setLocalTheta(G4UniformRand());
        sim_hit->setLocalPhi(G4UniformRand());
        sim_hit->setNPE(1); 
      }     
      
      JM::SimTrack* jm_trk = sim_event->addTrack();
        jm_trk->setPDGID(1);
        jm_trk->setTrackID(1);
        jm_trk->setInitPx(0);
        jm_trk->setInitPy(0);
        jm_trk->setInitPz(0);
        jm_trk->setInitMass(0);
        jm_trk->setInitX(0);
        jm_trk->setInitY(0);
        jm_trk->setInitZ(0);
        jm_trk->setInitT(0);
      system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
      t1->Fill();
      f->Write();
      system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
      f->Close();
   } 

    
   if(m_type==4)
   {
    
      TFile* f_old=new TFile("tree1.root","recreate");
      TTree * t1_old=new TTree("nphotons","nphotons");

      JM::SimEvent* sim_event_old = new JM::SimEvent(10);
      int num=m_value*1000000;
      t1_old->Branch("event_branch","SimEvent",sim_event_old,32000,1);
      for(int i=0;i<=num;i++)
      {
        JM::SimPMTHit* sim_hit = sim_event_old->addCDHit();
        sim_hit->setPMTID(i);
        sim_hit->setHitTime(G4UniformRand());
        sim_hit->setLocalTheta(G4UniformRand());
        sim_hit->setLocalPhi(G4UniformRand());
        sim_hit->setNPE(1);
      }   
      JM::SimTrack* jm_trk = sim_event_old->addTrack();
        jm_trk->setPDGID(1);
        jm_trk->setTrackID(1);
        jm_trk->setInitPx(0);
        jm_trk->setInitPy(0);
        jm_trk->setInitPz(0);
        jm_trk->setInitMass(0);
        jm_trk->setInitX(0);
        jm_trk->setInitY(0);
        jm_trk->setInitZ(0);
        jm_trk->setInitT(0);
      //system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");

      t1_old->Fill();
     // system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
      f_old->Write();
     // system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
      f_old->Close();
       

     // system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");   
      TFile *f=new TFile("/afs/ihep.ac.cn/users/h/huyuxiang/junofs/test_RootIO/tree1.root");
      TTree  *t1=(TTree*)f->Get("nphotons");
      std::cout<<"hello world";     
      JM::SimEvent* sim_event = new JM::SimEvent();
     // system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");       
      TBranch *branch =t1->GetBranch("event_branch");
       branch->SetAddress(&sim_event);
     //  system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
    // std::cout<<"eventID="<<sim_event->getEventID();
       

     // const std::vector<JM::SimPMTHit*> m_cd_hit;
      int nevent=t1->GetEntries();
      std::cout<<"nevent="<<nevent<<std::endl;
      system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
      for(int i=0;i<nevent;i++)
        {
           t1->GetEntry(i);
           system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
         
          const std::vector<JM::SimPMTHit*> m_cd_hit=sim_event->getCDHitsVec();
             std::cout<<"m_cd_hitsize="<<m_cd_hit.size()<<std::endl;
         }    
  

     //std::cout<<"hello world";
            

    }
 
   if( m_type == 5 )
       {
          if(loop_count == 1)
           {
                for(int k=0;k<3;k++)
                  {
                       TFile* f=new TFile(file_name[k],"recreate");
                       TTree * t1=new TTree("nphotons","nphotons");

                       JM::SimEvent* sim_event = new JM::SimEvent(10);
                       t1->Branch("event_branch","SimEvent",sim_event,32000,1);
                       for(int i=0;i<4000000;i++)
                          {
                             JM::SimPMTHit* sim_hit = sim_event->addCDHit();
                             sim_hit->setPMTID(i);
                             sim_hit->setHitTime(G4UniformRand());
                             sim_hit->setLocalTheta(G4UniformRand());
                             sim_hit->setLocalPhi(G4UniformRand());
                             sim_hit->setNPE(1);
                           }             
                        JM::SimTrack* jm_trk = sim_event->addTrack();
                  	jm_trk->setPDGID(1);
               		jm_trk->setTrackID(1);
        		jm_trk->setInitPx(0);
        		jm_trk->setInitPy(0);
        		jm_trk->setInitPz(0);
        		jm_trk->setInitMass(0);
        		jm_trk->setInitX(0);
       		 	jm_trk->setInitY(0);
        		jm_trk->setInitZ(0);
        		jm_trk->setInitT(0);
   
      			t1->Fill();
      			f->Write();
      		
      			f->Close();

                   }
                  
                
           }       

         if(loop_count!=1)
            {
                 TFile *f=new TFile("/afs/ihep.ac.cn/users/h/huyuxiang/junofs/test_RootIO/tree1.root");
                 TTree  *t1=(TTree*)f->Get("nphotons");
                 JM::SimEvent* sim_event = new JM::SimEvent();      
                 TBranch *branch =t1->GetBranch("event_branch");
                 branch->SetAddress(&sim_event);
                 int nevent=t1->GetEntries();  
                 for(int i=0;i<nevent;i++)
                    { 
                      t1->GetEntry(i);
                      system("/junofs/users/huyuxiang/test_RootIO/test_mem.sh");
                      const std::vector<JM::SimPMTHit*> m_cd_hit=sim_event->getCDHitsVec();
                      std::cout<<"m_cd_hitsize="<<m_cd_hit.size()<<std::endl;
                    }
                 f->Close();      
 
            }



       }
 
    

   loop_count++;
   return true;
}

bool FirstAlg::finalize()
{
    LogDebug << "in the FirstAlg::finalize()" << std::endl;
  //  sleep(10);
    return true;
}
   
   
