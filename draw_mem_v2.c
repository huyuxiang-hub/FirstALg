
void draw_mem_v2(){
  TCanvas *c = new TCanvas("c","Graph2D example",0,0,600,400); 

  TString title="memory";
  std::string path="./important.txt"; 
  TGraph2D* g_phys=new TGraph2D();
 
  g_phys->SetTitle("Memory peak value;hit number(M); the time of reading the root file; ");

  ifstream infile(path);
  double x=0;
  double y=0;
  double z=0;
  int j=0;
  
  while(1)
    {
     
       infile>>x;
       if(infile.eof())
                {break;}

       infile>>y;
       infile>>z;
       x=x/1000000;
 //      std::cout<<"x="<<x<<std::endl;
       z=z/1024.0;
      // std::cout<<"z="<<z<<std::endl;
   
       g_phys->SetPoint(j, x, y,z);
     //  g_phys->SetTitle(title);
       j++;
    std::cout<<"j="<<j<<std::endl;
       std::cout<<"hello";
     } 

   g_phys->Draw("CONT4Z");
   
}
