



TGraph* creat_graph(std::string path, TString title,int MarkerColor=2,int MarkerStyle=29,float MarkerSize=2){
  TGraph* g_phys=new TGraph();

  ifstream infile(path);
  double x=0;
  double y=0;
  int j=0;

  while(1)
    {
       infile>>x;
       infile>>y;
       g_phys->SetPoint(j, x, y);
       g_phys->SetTitle(title);
       g_phys->SetLineColor(kBlack);
       j++;
       if(infile.eof())
                {break;}
       std::cout<<"hello  ";
     }

     g_phys->SetMarkerStyle(MarkerStyle);
     g_phys->SetMarkerColor(MarkerColor);
     g_phys->SetMarkerSize(MarkerSize);
  return g_phys;

}









void draw_mem(std::string main_path, std::string sub_path)
{  
  ifstream infile_main(main_path);
  TString Title;
  TString X_title;
  TString Y_title;
  infile_main>>Title;
  infile_main>>X_title;
  infile_main>>Y_title;
 
  ifstream infile_sub(sub_path);
  int num_of_para;
  infile_sub>>num_of_para;
  std::vector<std::string> data_path(num_of_para);
  std::vector<TString>     sub_title(num_of_para);  
  std::vector<int>         MarkerColor(num_of_para);
  std::vector<int>         MarkerStyle(num_of_para);
  std::vector<float>         MarkerSize(num_of_para);
  
   for(int i=1; i<=num_of_para; i++)
  {  
     infile_sub>>data_path[i-1];
     infile_sub>>sub_title[i-1];
     infile_sub>>MarkerColor[i-1];
     infile_sub>>MarkerStyle[i-1];
     infile_sub>>MarkerSize[i-1];
   }   

  TMultiGraph* mg_phys = new TMultiGraph();
  for(int i=1;i<=num_of_para;i++)
   {
      TGraph* g_phys=new TGraph();
      g_phys=creat_graph(data_path[i-1],sub_title[i-1],MarkerColor[i-1],MarkerStyle[i-1],MarkerSize[i-1]);
      mg_phys->Add(g_phys);
   }

    TCanvas* c = 0;
    c = new TCanvas;
    c->SetTitle("c1");
    mg_phys->SetTitle(Title);  
    mg_phys->GetXaxis()->SetTitle(X_title);
    mg_phys->GetYaxis()->SetTitle(Y_title);
    mg_phys->Draw("ALP");
    c->BuildLegend();
    c->SaveAs("data.png");

 /* std::cout<<"type="<<type<<std::endl;
  std::vector<std::string> path(num_of_type);
  std::vector<int>         MarkerColor(num_of_type);
  std::vector<int>         MarkerStyle(num_of_type);
  std::vector<TString> Title(num_of_type);
  std::vector<TString> X_Title(num_of_type);
  std::vector<TString> Y_Title(num_of_type);
  */
  /*std::map<int,std::vector<std::string>> map_path;
  std::vector<std::string> sub_path_2(4);
  sub_path_2[2]="./sub_path2-2";
  map_path[2]=sub_path_2;   
  std::cout<<"this is new="<<map_path[2][2]<<std::endl;*/

 /* path[1]="./output-type.1.tmp";
  MarkerColor[1]=2;
  MarkerStyle[1]=29;
  Title[1]="Memory";
  X_Title[1]="size of array(M)";
  Y_Title[1]="memory_need (MB)";


  path[2]="./output-type.2.tmp";
  MarkerColor[2]=2;
  MarkerStyle[2]=29;
  Title[2]="Memory";
  X_Title[2]="number of hit (M)";
  Y_Title[2]="memory_need (MB)";



  path[4]="./output-type.4.tmp";
  MarkerColor[4]=2;
  MarkerStyle[4]=29;
  Title[4]="input of Root File";
  X_Title[4]="number of hit (M)";
  Y_Title[4]="memory_need (MB)";*/
 

 /* TMultiGraph* mg_phys = new TMultiGraph();
  TGraph* g_phys=new TGraph();
  g_phys=creat_graph(path[type],MarkerColor[type],MarkerStyle[type]);
  mg_phys->Add(g_phys);


    TCanvas* c = 0;
    c = new TCanvas;
    c->SetTitle("de");
    mg_phys->SetTitle(Title[type]);  
    mg_phys->GetXaxis()->SetTitle(X_Title[type]);
    mg_phys->GetYaxis()->SetTitle(Y_Title[type]);*/
   // mg_phys->GetXaxis()->SetLimits(1,15);
 //   mg_phys->SetMinimum(0.);
   // mg_phys->SetMaximum(200.);
    
   // mg_phys->Draw("ALP");
  //  c->SaveAs("data.png"); 
   // c->BuildLegend();
}




/*TGraph* draw_a_graph(string path){
   
     ifstream infile(path);
     TGraph* g_phys = new TGraph();    
     int j=0;
  double mem;
  double time=0;  
  
     for(int i=1;i<=10;i++)
         { string s;
           infile>>s;
           cout<<s<<endl;
         }
     while(1)
         {
           infile>>mem;
           mem=mem/1024;
           cout<<mem<<endl;
           time=time+0.1/3600;
           g_phys->SetPoint(j, time , mem);
           j++;
           if(infile.eof())
               {break;}


           infile>>mem;
         }
    
    return g_phys;
}*/
