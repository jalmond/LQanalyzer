//// Code makes directory of histograms and cutflow. 
#include "MakeDataMCCompPlots.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "CMS_lumi.h"

int main(int argc, char *argv[]) {
  
  /////////////////////////////////////////////////////
  //
  //  3 stages to setup : 
  //  1: McatNloWZ specifies with WZ MC we plot
  //  2: reg: specifies which fake region is plotted
  //  3: BM specifies if we plot 1.2 or 4.7 fb-1
  //
  //////////////////////////////////////////////////////
  
  TH1::SetDefaultSumw2(true);
  
  if(argc == 1) {
    cout << "No config file set" << endl;
    return 0;  
  }
  
  /// Set Plotting style
  setTDRStyle();
  //gSystem->Load("libCMS_lumi.so");
  
  gStyle->SetPalette(1);
  
  //read in config
  
  for (int i = 1; i < argc; ++i) {
    string configfile = argv[i];   
    SetUpMasterConfig(configfile);
    int a =MakeCutFlow_Plots(configfile);
  }
  
  system(("scp -r " + output_path + " jalmond@lxplus5.cern.ch:~/www/SNU/WebPlots/").c_str());

  cout << "Open plots in " << output_index_path << endl; 
  return 0;
}




int MakeCutFlow_Plots(string configfile){
  
  std::string pname = "/home/jalmond/WebPlots/"+ path + "/indexCMS.html";
  std::string phistname = "/home/jalmond/WebPlots/"+ path + "/histograms/" + histdir  + "/indexCMS.html";
  output_path = "/home/jalmond/WebPlots/"+ path ;
  output_index_path = string("https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/")+ path + "/histograms/" + histdir  + "/indexCMS.html";
  system(("mkdir /home/jalmond/WebPlots/" + path).c_str());
  system(("mkdir /home/jalmond/WebPlots/" + path+ "/histograms/").c_str());
  system(("mkdir /home/jalmond/WebPlots/" + path+"/histograms/" + histdir + "/").c_str());
  cout << "HIST page is set to " << phistname.c_str() << endl;

  histpage.open(phistname.c_str());
  page.open(pname.c_str());
  
  page << "<html><font face=\"Helvetica\"><head><title> HvyN Analysis </title></head>" << endl;
  page << "<body>" << endl;
  page << "<h1> HvyN Analysis Plots </h1>" << endl;
  page << "<br> <font size=\"4\"><b> " << message <<  " </b></font> <br><br>" << endl;
  page << "<a href=\"histograms/" +histdir + "/indexCMS.html\">"+ histdir + "</a><br>"; 

  MakeCutFlow(histdir);  
  int M=MakePlots(histdir);  

  return 1;

}


int MakePlots(string hist) {

  
  cout << "\n ---------------------------------------- " << endl;
  cout << "MakeDataMCCompPlots::MakePlots(string hist) " << endl;
  
  ////////////////////// ////////////////
  ////  MAIN PART OF CODE for user/
  ///////////////////////////////////////
  //// What samples to use in histogram
  vector<pair<pair<vector<pair<TString,float> >, int >, TString > > samples;  
  vector<string> cut_label;
  //// Sets flags for using CF/NP/logY axis/plot data/ and which mc samples to use
  
  SetUpConfig( samples, cut_label);  
  cuts.clear();

  // ----------Get list of cuts to plot  ----------------------
  ifstream cut_name_file(cutfile.c_str());
  if(!cut_name_file) {
    cerr << "Did not find " + cutfile + ", exiting ..." << endl;
    return 1;
  }
  while(!cut_name_file.eof()) {
    string cutname;
    cut_name_file >> cutname;
    if(cutname=="END") break;
    allcuts.push_back(cutname);
    cout << "Added " << cutname << endl;
  }
  

  ifstream histo_name_file(histfile.c_str());
  if(!histo_name_file) {
    cerr << "Did not find " << histfile << ", exiting ..." << endl;
    return 1;
  }
  
  histpage << "<table border = 1><tr>"
	   << "<th> <a name=\"PlotName (variable_Cut)\"> PlotName (variable_Cut) </a> </th>"
	   << "<th> Data/MC Plot </th>"
	   << "<th> Data/MC LogPlots </th>"
	   << "</tr>" << endl;
  
  while(!histo_name_file.eof()) {
    string h_name;
    int rebin;
    double xmin,xmax;
    histo_name_file >> h_name;
    if(repeat(h_name))continue;
    if(h_name=="END") break;
    histo_name_file >> rebin;
    histo_name_file >> xmin;
    histo_name_file >> xmax;
    
    if(h_name.find("#")!=string::npos) continue;
    
    for(unsigned int ncut=0; ncut<allcuts.size();  ncut++){
      string name = allcuts.at(ncut) + "/" + h_name+ "_" + allcuts.at(ncut);
       
	cout << "\n------------------------------------------------------- \n" << endl;
	cout << "Making histogram " << name << endl;
	
	
	/// Make nominal histogram stack
	map<TString, TH1*> legmap;
	
	cout << "Making Nominal histogram " << endl;
	THStack* mstack=  MakeStack(samples , "Nominal",name, xmin, xmax, legmap, rebin );
	
	//// mhist sets error config
	map<TString,TH1*> mhist;
	mhist["Nominal"] = MakeSumHist(mstack);
	
	TH1* hup = MakeStackUp(mhist, name+"UP");
	TH1* hdown = MakeStackDown(mhist, name+"DOWN");
	
	cout << "Final Background Integral = " <<  MakeSumHist(mstack)->Integral() << " : Up = " << hup->Integral() << " : Down= " << hdown->Integral() << endl;
	
	/// Make data histogram
	TH1* hdata = MakeDataHist(name, xmin, xmax, hup, ylog, rebin);
	CheckHist(hdata);	
	float ymin (0.), ymax( 1000000.);
	ymax = GetMaximum(hdata, hup, ylog, name);
	
	
	TFile* file_sig40 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee40_nocut_5_3_14.root"));
	TH1* hsig_40 = dynamic_cast<TH1*> ((file_sig40->Get(name.c_str()))->Clone());
	hsig_40->Rebin(rebin);
	FixOverUnderFlows(hsig_40, xmax);
	SetTitles(hsig_40, name);
	ymax = GetMaximum(hsig_40, hsig_40, ylog, name);
	hsig_40->GetXaxis()->SetRangeUser(xmin,xmax);	
	hsig_40->GetYaxis()->SetRangeUser(ymin,ymax);	
	float int_bkg = hup->Integral()/2.;
	
	hsig_40->Scale(1/hsig_40->Integral());
	hsig_40->Scale(int_bkg);
	hsig_40->SetLineColor(kRed);
	hsig_40->SetLineWidth(2.);
		
	TFile* file_sig80 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee80_nocut_5_3_14.root"));
        TH1* hsig_80 = dynamic_cast<TH1*> ((file_sig80->Get(name.c_str()))->Clone());
	hsig_80->Rebin(rebin);
	FixOverUnderFlows(hsig_80, xmax);
	hsig_80->Scale(1./hsig_80->Integral());
	hsig_80->Scale(int_bkg);
	hsig_80->SetLineColor(kBlue);
	hsig_80->SetLineWidth(2.);

	TFile* file_sig100 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee100_nocut_5_3_14.root"));
        TH1* hsig_100 = dynamic_cast<TH1*> ((file_sig100->Get(name.c_str()))->Clone());
        hsig_100->Rebin(rebin);
        FixOverUnderFlows(hsig_100, xmax);
        hsig_100->Scale(1./hsig_100->Integral());
        hsig_100->Scale(int_bkg);
        hsig_100->SetLineColor(kGreen);
        hsig_100->SetLineWidth(2.);

	

	TFile* file_sig150 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee150_nocut_5_3_14.root"));
        TH1* hsig_150 = dynamic_cast<TH1*> ((file_sig150->Get(name.c_str()))->Clone());
        hsig_150->Rebin(rebin);
        FixOverUnderFlows(hsig_150, xmax);
        hsig_150->Scale(1./hsig_150->Integral());
        hsig_150->Scale(int_bkg);
        hsig_150->SetLineColor(kCyan);
        hsig_150->SetLineWidth(2.);

	TFile* file_sig200 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee200_nocut_5_3_14.root"));
        TH1* hsig_200 = dynamic_cast<TH1*> ((file_sig200->Get(name.c_str()))->Clone());
        hsig_200->Rebin(rebin);
        FixOverUnderFlows(hsig_200, xmax);
        hsig_200->Scale(1./hsig_200->Integral());
        hsig_200->Scale(int_bkg);
        hsig_200->SetLineColor(kOrange);
        hsig_200->SetLineWidth(2.);


	TFile* file_sig300 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee300_nocut_5_3_14.root"));
        TH1* hsig_300 = dynamic_cast<TH1*> ((file_sig300->Get(name.c_str()))->Clone());
        hsig_300->Rebin(rebin);
        FixOverUnderFlows(hsig_300, xmax);
        hsig_300->Scale(1./hsig_300->Integral());
        hsig_300->Scale(int_bkg);
        hsig_300->SetLineColor(kMagenta+1);
        hsig_300->SetLineWidth(2.);

	TFile* file_sig400 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee400_nocut_5_3_14.root"));
        TH1* hsig_400 = dynamic_cast<TH1*> ((file_sig400->Get(name.c_str()))->Clone());
        hsig_400->Rebin(rebin);
        FixOverUnderFlows(hsig_400, xmax);
        hsig_400->Scale(1./hsig_400->Integral());
        hsig_400->Scale(int_bkg);
        hsig_400->SetLineColor(kGreen-2);
        hsig_400->SetLineWidth(2.);

	TFile* file_sig500 =  TFile::Open(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee500_nocut_5_3_14.root"));
        TH1* hsig_500 = dynamic_cast<TH1*> ((file_sig500->Get(name.c_str()))->Clone());
        hsig_500->Rebin(rebin);
        FixOverUnderFlows(hsig_500, xmax);
        hsig_500->Scale(1./hsig_500->Integral());
        hsig_500->Scale(int_bkg);
        hsig_500->SetLineColor(kBlue-2);
        hsig_500->SetLineWidth(2.);



	if(showdata)cout << "Total data = " <<  hdata->Integral() << endl;
	//scale =  MakeSumHist(mstack)->Integral() /  hdata->Integral();
	scale = 1.;
	/// Make legend
	TLegend* legend = MakeLegend(legmap, hdata, showdata, ylog);       		
	
        vector<THStack*> vstack;		
	vstack.push_back(mstack);   	
	

	cout << " Making canvas" << endl;
	
	TCanvas* c = CompDataMC(hdata,hsig_40,hsig_80,hsig_100, hsig_150, hsig_200,  hsig_300,  hsig_400 , hsig_500,vstack,hup,hdown, legend,name,rebin,xmin,xmax, ymin,ymax, path, histdir,ylog, showdata, channel);      	
	cout << " Made canvas" << endl;

	string canvasname = c->GetName();
	canvasname.erase(0,4);
	

	CMS_lumi( c, 2, 11 );
	c->Update();
	c->RedrawAxis();
	
	PrintCanvas(c, histdir, canvasname, c->GetName());
    }
  }            
  page.close();
  
  return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///   CODE FOR CUTFLOW
///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeCutFlow(string type){

  
  vector<string> cut_label;  
  vector<pair<pair<vector<pair<TString,float> >, int >, TString > > cfsamples;  
  SetUpConfig( cfsamples, cut_label);

  cuts.clear();    
  // ----------Get list of cuts to plot  ----------------------
  ifstream cut_name_file(cutfile.c_str());
  while(!cut_name_file.eof()) {
    string cutname;
    cut_name_file >> cutname;
    if(cutname=="END") break;
    cut_label.push_back(cutname);
    cuts.push_back((cutname+ hist +"_" + cutname).c_str());    
    cout << "Making cutflow for " << hist << " " << cutname << endl;
  }

 
  vector<float> totalnumbers;
  vector<float> totalnumbersup;
  vector<float> totalnumbersdown;  
  
  int i_cut(0);
  for(vector<string>::iterator it = cuts.begin(); it!=cuts.end(); it++, i_cut++){
    
    vector<pair<vector<pair<TString,float> >, TString> > samples;   
    for(vector<pair<pair<vector<pair<TString,float> >, int >, TString > >::iterator it2 = cfsamples.begin(); it2!=cfsamples.end(); it2++){
      samples.push_back(make_pair(it2->first.first,it2->second));      
    }
    
      
    /// Vectors for cutflow	table
    map<TString,float> samples_numbers;
    map<TString,float> samples_numbers_staterr;
    map<TString,float> samples_numbers_up;
    map<TString,float> samples_numbers_down;
    
    /// Vector for systematic table
    map<TString,float> syst_stat;
    map<TString,float> syst_norm;
    map<TString,float> syst_total;

    
    float totalbkg(0.),totalbkgdown(0.), totalbkgup(0.); 
    for(vector<pair<vector<pair<TString,float> >, TString> >::iterator it2 = samples.begin() ; it2!= samples.end(); it2++){
      TString cutname = *it;
      totalbkg+= Calculate(*it,"Normal",*it2);
      totalbkgup+= Calculate(*it,"Up",*it2);
      totalbkgdown+= Calculate(*it,"Down",*it2);
      
      samples_numbers[it2->second] = Calculate(cutname,"Normal",*it2);
      samples_numbers_up[it2->second] = Calculate(cutname,"Down",*it2);
      samples_numbers_down[it2->second] = Calculate(cutname,"Up",*it2);
      samples_numbers_staterr[it2->second] = Calculate(cutname,"StatErr",*it2);
    }	
    
    
    float totaldata(0.);
    if(showdata) totaldata = GetIntegral(*it,"data","data");
    float errdata(0.);
    if(showdata) errdata= GetError(*it,"data","data");
    
    
    float totalerr_up(0.),totalerr_down(0.),totalerrup(0.),totalerrdown(0.),total_staterr(0.);
    for(map<TString,float>::iterator mapit = samples_numbers.begin(); mapit!= samples_numbers.end(); mapit++){
      
      map<TString,float>::iterator mapit_up;
      mapit_up = samples_numbers_up.find(mapit->first);
      map<TString,float>::iterator mapit_down;
      mapit_down = samples_numbers_down.find(mapit->first);
      map<TString,float>::iterator mapit_stat;
      mapit_stat = samples_numbers_staterr.find(mapit->first);
      totalerr_up += ( mapit_up->second*mapit_up->second+ mapit_stat->second*mapit_stat->second); 
      totalerr_down += (mapit_down->second*mapit_down->second + mapit_stat->second*mapit_stat->second); 
      totalerrup += (mapit_up->second*mapit_up->second); 
      totalerrdown += (mapit_down->second*mapit_down->second); 
      total_staterr += mapit_stat->second*mapit_stat->second;
      TString sample = mapit->first;
      if(sample.Contains("t#bar{t}+V")) sample = "t$\bar{t}$+V";
      cout << sample << " background = " << mapit->second<< " +- " << mapit_stat->second << " + " << mapit_up->second << " - " << mapit_down->second <<  endl;      
   
      
    }
  
    
    totalerr_up = sqrt(totalerr_up);
    totalerr_down = sqrt(totalerr_down);
    total_staterr = sqrt(total_staterr);
    totalerrup = sqrt(totalerrup);
    totalerrdown = sqrt(totalerrdown);
    
    cout << "Total Bkg   = " << totalbkg << "+- " << total_staterr << " + " << totalerrup << " - " << totalerrdown << endl;
    if(showdata)cout << "Total Data  = " << totaldata << endl;
    cout << "-------------" << endl;
    if(totaldata > totalbkg)cout <<"Significance = " << (totaldata - totalbkg) / (sqrt( (errdata*errdata) + (totalerr_up*totalerr_up))) << endl;
    else cout <<"Significance = " << (totaldata - totalbkg) / (sqrt( (errdata*errdata) + (totalerr_down*totalerr_down))) << endl;
    float significance = (totaldata - totalbkg) / (sqrt( (errdata*errdata) + (totalerr_up*totalerr_up))) ;
    
    if(significance < 0.) significance = (totaldata - totalbkg) / (sqrt( (errdata*errdata) + (totalerr_down*totalerr_down))) ;
    

    //// Make TEX file
    ofstream ofile_tex;
    string latex_file =  "Tables/" + cut_label.at(i_cut) + ".tex";
    ofile_tex.open(latex_file.c_str());
    ofile_tex.setf(ios::fixed,ios::floatfield);
    ofile_tex << "\\documentclass[10pt]{article}" << endl;
    ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl}" << endl;

    ofile_tex << "\\begin{document}" << endl;
    ofile_tex << "\\input{Tables/" + cut_label.at(i_cut)  + "Table.txt}" << endl;
    ofile_tex << "\\end{document}" << endl;
    
    /// Make text file
    ofstream ofile;
    string latex =  "Tables/" + cut_label.at(i_cut) + "Table.txt";
    
    ofile.open(latex.c_str());
    ofile.setf(ios::fixed,ios::floatfield); 
    
    ofile.precision(1);
    ofile << "\\begin{table}[h]" << endl;
    ofile << "\\begin{center}" << endl;
    ofile << "\\begin{tabular}{lr@{\\hspace{0.5mm}}c@{\\hspace{0.5mm}}c@{\\hspace{0.5mm}}l}" << endl;
    ofile << "\\hline" << endl;
    ofile << "\\hline" << endl;   
    //ofile << "Source & \\multicolumn{4}{c}{$\\mu\\mu\\mu$} \\"<<"\\" << endl;
    ofile << "Source & \\multicolumn{4}{c}{" << columnname << "} \\"<<"\\" << endl;
    ofile << "\\hline" << endl;   
	 
    
    for(map<TString,float>::iterator mapit = samples_numbers.begin(); mapit!= samples_numbers.end(); mapit++){
      
      map<TString,float>::iterator mapit_up;
      mapit_up = samples_numbers_up.find(mapit->first);
      map<TString,float>::iterator mapit_down;
      mapit_down = samples_numbers_down.find(mapit->first);
      map<TString,float>::iterator mapit_stat;
      mapit_stat = samples_numbers_staterr.find(mapit->first);
      
      TString sample = mapit->first;
      if(sample.Contains("t#bar{t}+V")) sample = "t$\\bar{t}$+V";
      if(mapit->second!=0.0){
	ofile << sample + "&" <<  mapit->second << "& $\\pm$& "  << mapit_stat->second <<  "&$^{+" <<  mapit_up->second << "}_{-" <<  mapit_down->second  << "}$" ; 
	ofile  <<  "\\"  << "\\" << endl;	   
      }
    }
    ofile << "\\hline" << endl;
    ofile << "Total&" << totalbkg << "& $\\pm$&"  << total_staterr << "&$^{+" << totalerrup  << "}_{-" << totalerrdown << "}$" ; 
    ofile  <<  "\\"  << "\\" << endl;
    ofile << "\\hline" << endl;
    
    ofile << "Data&  \\multicolumn{4}{c}{$" << totaldata << "$}\\" << "\\" <<endl;
    ofile << "\\hline" << endl;
    if(significance < 0) ofile << "Signficance&  \\multicolumn{4}{c}{$" << significance << "\\sigma$}\\" << "\\" <<endl;
    if(significance > 0) ofile << "Signficance&  \\multicolumn{4}{c}{$+" << significance << "\\sigma$}\\" << "\\" <<endl;
    ofile << "\\hline" << endl;   
    ofile << "\\hline" << endl;   
    ofile << "\\end{tabular}" << endl;
    ofile << "\\caption{" << caption << "}" << endl;
    ofile << "\\end{center}" << endl;
    ofile << "\\end{table}" << endl;    
     
  
    string latex_command = "latex Tables/" + cut_label.at(i_cut) +".tex";
    string dvi_command = "dvipdf " + cut_label.at(i_cut) +".dvi";
    string mv_command = "mv " + cut_label.at(i_cut) +".pdf /home/jalmond/WebPlots/" + path +"/histograms/"+ histdir ;
    
    system((latex_command.c_str()));
    system((dvi_command.c_str()));
    system((mv_command.c_str()));
    system(("rm *aux"));
    system(("rm *log"));
    system(("rm *dvi"));
    
    string cftitle = cut_label.at(i_cut);
    
    histpage << "<tr><td>"<< "cutflow " + cut_label.at(i_cut)  <<"</td>"<<endl;
    histpage <<"<td>"<<endl;
    histpage << "<a href=\"" << cut_label.at(i_cut)  << ".pdf\">";
    histpage << "Cutflow: " + cut_label.at(i_cut)  + ".pdf</p>";
    histpage << "</td>" << endl;
  }

  return;
}

bool repeat (string hname){
  map<string,int>::iterator mit = norepeatplot.find(hname);
  if(mit!=norepeatplot.end())return true;
  else{
    norepeatplot[hname]=1;
    return false;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintCanvas(TCanvas* c1, string folder, string plot_description, string title){

  std::string tpdf = "/home/jalmond/WebPlots/"+ path +  "/histograms/"+folder+"/"+title;
  
  if(plot_description.empty())plot_description=title;
  histpage << "<tr><td>"<< plot_description <<"</td>"<<endl;
  histpage <<"<td>"<<endl;
  histpage << "<a href=\"" << title.c_str() << ".png\">";
  histpage << "<img src=\"" << title.c_str() << ".png\" width=\"100%\"/>";
  histpage << "</td>" << endl;
  histpage <<"<td>"<<endl;
  histpage << "<a href=\"" << title.c_str() << "_log.png\">";
  histpage << "<img src=\"" << title.c_str() << "_log.png\" width=\"100%\"/>";
  histpage << "</td>" << endl;

  
  return;
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


TLegend* MakeLegend(map<TString, TH1*> map_legend,TH1* hlegdata,  bool rundata , bool logy){
  
  double x1 = 0.6;
  double y1 = 0.6;
  double x2 = 0.6;
  double y2 = 0.9;

  
  int nbinsX=hlegdata->GetNbinsX();
  
  /// 
  if((hlegdata->GetBinContent(nbinsX*0.8) / hlegdata->GetMaximum()) < 0.5){
    x1 = 0.6;
    y1 = 0.6;
    x2 = 0.9;
    y2 = 0.9;
  }
  else{
    if((hlegdata->GetBinContent(nbinsX*0.3) / hlegdata->GetMaximum()) < 0.5){
      x1 = 0.2;
      y1 = 0.6;
      x2 = 0.5;
      y2 = 0.9;
    }
  }
  
  TLegend* legendH = new TLegend(x1,y1,x2,y2);
  legendH->SetFillColor(10);
  legendH->SetBorderSize(0);
  legendH->SetTextSize(0.02);
  
  
  if(rundata) 	legendH->AddEntry(hlegdata,"Data","pl");
  
  for(map<TString, TH1*>::iterator it = map_legend.begin(); it!= map_legend.end(); it++){
    legendH->AddEntry(it->second,it->first.Data(),"f");    
  }

  return legendH;
  
}




TH1* MakeDataHist(string name, double xmin, double xmax, TH1* hup, bool ylog, int rebin){

  /// Make data histogram
  TFile* file_data =  TFile::Open((dataloc).c_str());
  TH1* hdata = dynamic_cast<TH1*> ((file_data->Get(name.c_str()))->Clone());
  
  hdata->Rebin(rebin);

  float ymin (0.), ymax( 1000000.);
  ymax = GetMaximum(hdata, hup, ylog, name);
  
  /// Set Ranges / overflows
  FixOverUnderFlows(hdata, xmax);  
  
  cout << "Ymax = " << ymax << endl;
  hdata->GetXaxis()->SetRangeUser(xmin,xmax);
  
  hdata->GetYaxis()->SetRangeUser(ymin, ymax);

  hdata->SetMarkerStyle(20);
  hdata->SetMarkerSize(1.2);
	
 
  //// X title  
  SetTitles(hdata, name);
  
  return hdata;

}

void CheckHist(TH1* h){
  if(!h) {
    cout << "Not able to find data histogram" << endl;
  }
}


vector<pair<TString,float> >  InitSample (TString sample){
  
  vector<pair<TString,float> > list;  
  
  if(sample.Contains("dy_")){
    list.push_back(make_pair("DY10to50",0.2));    
    list.push_back(make_pair("DY50plus",0.2));    
  }
  
  if(sample.Contains("dyplusbb")){
    list.push_back(make_pair("DY10to50",0.2));
    list.push_back(make_pair("DY50plus",0.2));
    list.push_back(make_pair("Zbb",0.2));
  }
    
  ///// Top samples //////////////////    
  if(sample.Contains("top")){
    list.push_back(make_pair("ttbar",0.1));
    list.push_back(make_pair("stbar_sch",0.1));
    list.push_back(make_pair("stbar_tch",0.1));
    list.push_back(make_pair("stbar_tW",0.1));
    list.push_back(make_pair("st_sch",0.1));
    list.push_back(make_pair("st_tch",0.1));
    list.push_back(make_pair("st_tW",0.1));
  }
  
  if(sample.Contains("ttbar")){
    list.push_back(make_pair("ttbar",0.1));
  }
  
  if(sample.Contains("qcd"))
    {
      list.push_back(make_pair("QCDEl",0.30));
    }

  if(sample.Contains("ttv")){
    list.push_back(make_pair("ttW",0.3));
    list.push_back(make_pair("ttZ",0.3));
  }
  
  
  //////// Diboson ////////
  if(sample.Contains("wz_py")){    
    list.push_back(make_pair("WZ_py",0.15));
    //list.push_back(make_pair("WgammaE",0.22));
    //list.push_back(make_pair("WgammaTau",0.22));

  }
  
  if(sample.Contains("zz_py")){
    list.push_back(make_pair("ZZ_py",0.15));
  }
  
  if(sample.Contains("ww_py")){      
    list.push_back(make_pair("WW_py",0.15));
  }
  
  if(sample.Contains("vv_py")){
    list.push_back(make_pair("WZ_py",0.15));
    list.push_back(make_pair("ZZ_py",0.15));
    list.push_back(make_pair("WW_py",0.15));
    list.push_back(make_pair("SSWmWm",0.22));
    list.push_back(make_pair("SSWpWp",0.22));
    list.push_back(make_pair("WW_dp",0.22));

    ////list.push_back(make_pair("WgammaE",0.22));
    //list.push_back(make_pair("WgammaTau",0.22));
  }
  if(sample.Contains("vv_mg")){
    list.push_back(make_pair("WZtollqq_mg",0.15));
    list.push_back(make_pair("WZtoqqln_mg",0.15));
    list.push_back(make_pair("WZtollln_mg",0.15));
    list.push_back(make_pair("ZZtollnn_mg",0.15));
    list.push_back(make_pair("ZZtollqq_mg",0.15));
    list.push_back(make_pair("ZZtollll_mg",0.15));
    list.push_back(make_pair("WW_mg",0.15));
    //list.push_back(make_pair("WgammaE",0.22));
    //list.push_back(make_pair("WgammaTau",0.22));
  }

  if(sample.Contains("wz_mg")){
    list.push_back(make_pair("WZtollqq_mg",0.15));
    list.push_back(make_pair("WZtoqqln_mg",0.15));
    list.push_back(make_pair("WZtollln_mg",0.15));
    //list.push_back(make_pair("WgammaE",0.22));
    //list.push_back(make_pair("WgammaTau",0.22));

  }
  
  if(sample.Contains("zz_mg")){
    list.push_back(make_pair("ZZtollnn_mg",0.15));
    list.push_back(make_pair("ZZtollqq_mg",0.15));
    list.push_back(make_pair("ZZtollll_mg",0.15));
  }
  
  if(sample.Contains("ww_mg")){
    list.push_back(make_pair("WW_mg",0.15));
  }
  
  
  if(sample.Contains("zz_pow")){
    list.push_back(make_pair("Ztoeemm",0.15));
    list.push_back(make_pair("Ztoeett",0.15));
    list.push_back(make_pair("Ztommtt",0.15));
    list.push_back(make_pair("Ztoeeee",0.15));
    list.push_back(make_pair("Ztommmm",0.15));
    list.push_back(make_pair("Ztotttt",0.15));
  }
  
  //// Wjets
  if(sample.Contains("wjet_")){
    list.push_back(make_pair("Wjets",0.15));
  }
  if(sample.Contains("wjetplusbb")){
    list.push_back(make_pair("Wjets",0.15));
    list.push_back(make_pair("Wbb",0.15));
  }
  
  
  //////// SS WW /////////  
  if(sample.Contains("ss_mg")){         
    list.push_back(make_pair("SSWmWm",0.22));              
    list.push_back(make_pair("SSWpWp",0.22));              
    list.push_back(make_pair("WW_dp",0.22));              
  }
  if(sample.Contains("higgs")){
    //list.push_back(make_pair("HtoZZ",0.22));
    list.push_back(make_pair("HtoTauTau",0.22));
    list.push_back(make_pair("HtoWW",0.22));
    list.push_back(make_pair("ggHtoZZ",0.22));
  }
  if(sample.Contains("vvv")){
    list.push_back(make_pair("WWW",0.22));
    list.push_back(make_pair("TTWW",0.22));
    list.push_back(make_pair("TTG",0.22));
    list.push_back(make_pair("ZZZ",0.22));
    list.push_back(make_pair("WWZ",0.22));
    list.push_back(make_pair("WWG",0.22));
  }
  if(sample.Contains("vgamma")){
    list.push_back(make_pair("Wgamma",0.22));
    list.push_back(make_pair("Zgamma",0.22));
    
  }
  if(sample.Contains("nonprompt")){
    list.push_back(make_pair("nonprompt",0.3));
  }

  if(sample.Contains("chargeflip")){
    list.push_back(make_pair("chargeflip",0.2));
  }

  if(list.size()==0) cout << "Error in making lists" << endl;
  
  return list;
}

void CheckSamples(int nsamples){
  if(nsamples==0) {
    cout << "No sample in this vector" << endl;
    exit(1);
  }
  return;
}




THStack* MakeStack(vector<pair<pair<vector<pair<TString,float> >, int >, TString > > sample, TString type, string name, float xmin, float xmax,map<TString, TH1*>& legmap , int rebin){
  
  string clonename = name;	
  THStack* stack = new THStack();
  
  bool debug(false);
  if(type.Contains("Nominal")) debug=true;

  TString fileloc = "";
 
  TDirectory* origDir = gDirectory;

  float sum_integral=0.;

  for(vector<pair<pair<vector<pair<TString,float> >, int >, TString > >::iterator it = sample.begin() ; it!= sample.end(); it++){
	
    if(type.Contains("Nominal")) fileloc = mcloc;
        
    if(!type.Contains("Nominal")) {
      if(it->first.first.at(0).first.Contains("nonprompt"))fileloc=mcloc;
    }    
    
    
    CheckSamples( it->first.first.size() );


    int isample=0;
    TFile* file =  TFile::Open((fileloc+ fileprefix + it->first.first.at(isample).first + filepostfix).Data());
    if(!file) cout << "Could not open " << fileloc+ fileprefix + it->first.first.at(isample).first + filepostfix << endl;
    
    gROOT->cd();
    TDirectory* tempDir = 0;
    int counter = 0;
    while (not tempDir) {
      std::stringstream dirname;
      dirname << "WRHNCommonLeptonFakes_%i" << counter;
      if (gROOT->GetDirectory((dirname.str()).c_str())) {
	++counter;
	continue;
      }      
      tempDir = gROOT->mkdir((dirname.str()).c_str());      
    }
            

    tempDir->cd();

    TH1* h_tmp = dynamic_cast<TH1*> ((file->Get(name.c_str()))->Clone(clonename.c_str()));

    while(!h_tmp) {
      isample++;
      gROOT->cd();
      file =  TFile::Open((fileloc+ fileprefix + it->first.first.at(isample).first + filepostfix).Data());
      tempDir->cd();
      h_tmp = dynamic_cast<TH1*> ((file->Get(name.c_str()))->Clone(clonename.c_str()));
    }
    
    CheckHist(h_tmp);

    if(debug)cout <<  it->second <<  "  contribution " << 1 << "/" << it->first.first.size()  << " is from " << fileprefix + it->first.first.at(isample).first + filepostfix <<" : Integral = " <<h_tmp->Integral() << " " << fileloc << endl;
    
    
    for(unsigned int i=isample+1; i < it->first.first.size(); i++){	    
      clonename+="A";
             
      origDir->cd();
      
      TFile* file_loop =  TFile::Open((fileloc+ fileprefix + it->first.first.at(i).first + filepostfix).Data());	    

      tempDir->cd();
      TH1* h_loop = dynamic_cast<TH1*> ((file_loop->Get(name.c_str()))->Clone(clonename.c_str()));	    	    	    
      if(!h_loop) continue;
      CheckHist(h_loop);
      cout << h_tmp << " " << h_loop   << endl;
      h_tmp->Add(h_loop);	  	    	    
            
      if(debug)cout <<  it->second <<  "  contribution " <<i+1 <<"/" << it->first.first.size()  << " is from ExampleAnalyzer_SK" << it->first.first.at(i).first << ".NTUP_SMWZ.Reco.root : Integral = " <<h_loop->Integral() << " sum integral = " << h_tmp->Integral()    << endl;
      file_loop->Close();
    }	  	  
    
    /// TH1* is now made. Now make pretty
    FixOverUnderFlows(h_tmp, xmax);	  
    ///Set colors
    h_tmp->SetFillColor(it->first.second);
    h_tmp->SetLineColor(it->first.second);	  
    
    
    if(!stack->GetHists()) {
      stack->SetName( (string("s_") + name).c_str() );
      stack->SetTitle( (string("s_") + name).c_str() );
      SetTitles(h_tmp, name);
  
    }//stack empt   
    

    h_tmp->Rebin(rebin);
    SetErrors(h_tmp, it->first.first.at(0).second);
           
    stack->Add(h_tmp);
    sum_integral+=h_tmp->Integral();
    
    if(type.Contains("Nominal")) {
      legmap[it->second] = h_tmp;
    }
    
    file->Close();	  
    origDir->cd();
  }
  
  cout << type << " has integral = " << sum_integral << endl;
  
  return stack;
}


TH1* MakeStackUp(map<TString, TH1*> map_of_stacks, TString clonename){
  
  map<TString, TH1*>::iterator it =  map_of_stacks.find("Nominal");
  
  float norm=1;
  TH1* h_up = dynamic_cast<TH1*>(it->second->Clone(clonename.Data())); // copy of nominal
  
  for(int binx=1 ; binx < h_up->GetNbinsX()+1; binx++){
    float nom_content = h_up->GetBinContent(binx);
    float nom_error = h_up->GetBinError(binx);
    
    /// Now use 5%+ norm + stat error
    float errup2 =  nom_error*nom_error + 0.05*0.05*nom_content*nom_content;
    
    /// add rest of systs

    float new_bin = nom_content + sqrt(errup2);
    h_up->SetBinContent(binx,new_bin);
   
  }
  
  return  h_up;
  
}


TH1* MakeStackDown(map<TString, TH1*> map_of_stacks, TString clonename){
  
  map<TString, TH1*>::iterator it =  map_of_stacks.find("Nominal");
  
  float norm=1;
  TH1* h_down = dynamic_cast<TH1*>(it->second->Clone(clonename.Data())); // copy of nominal
  
  for(int binx=1 ; binx < h_down->GetNbinsX()+1; binx++){
    float nom_content = h_down->GetBinContent(binx);
    float nom_error = h_down->GetBinError(binx);
    
    
    //// nom_error = stat err + normalisation error, set previously on nom hist
    float errdown2 =  nom_error*nom_error;
    
    /// Now use 5%+ norm + stat error
    float errup2 =  nom_error*nom_error + 0.05*0.05*nom_content*nom_content;
    
    float new_bin = nom_content  - sqrt(errdown2);
    h_down->SetBinContent(binx,new_bin);
   
  }
  
  return  h_down;


}


TH1* MakeSumHist(THStack* thestack){
  
  TH1* hsum=0;  
  TList* list = thestack->GetHists();
  TIter it(list, true);
  TObject* obj=0;
  while( (obj = it.Next()) ) {
    TH1* h = dynamic_cast<TH1*>(obj);
    
    if(!hsum) hsum = (TH1*)h->Clone( (string(h->GetName()) + "_sum").c_str() );
    else {
      hsum->Add(h, 1.0);
    }
  }//hist loop
  
  return hsum;
}


void SetErrors(TH1* hist, float normerr){

  
  for(int binx =1; binx < hist->GetNbinsX()+1; binx++){
    float newbinerr = hist->GetBinError(binx)*hist->GetBinError(binx) + hist->GetBinContent(binx)*hist->GetBinContent(binx)*normerr*normerr;
    hist->SetBinError(binx, sqrt(newbinerr));
  }
  
  return;

}



void SetTitles(TH1* hist, string name){
  
  string xtitle ="";
  string ytitle ="Entries";

  float binedge_up = hist->GetBinLowEdge(2);
  float binedge_down = hist->GetBinLowEdge(1);
  
  float width = binedge_up - binedge_down;
  
  std::ostringstream str_width;
  str_width<< width;

  if(HistInGev(name)) ytitle = "Entries / " +str_width.str() + " GeV";
  
  if(name.find("h_MET")!=string::npos){
    xtitle="E^{miss}_{T} [GeV]"; 
    if(name.find("phi")!=string::npos){
      xtitle="#phi_{E^{miss}_{T}} "; 
    }
  }
  if(name.find("h_MT")!=string::npos) xtitle="M_{T} [GeV]";
  if(name.find("h_dphi_METe")!=string::npos) xtitle="#Delta (#phi_{E^{miss}_{T}} - #phi_{el})";
  if(name.find("h_dphi_METm")!=string::npos) xtitle="#Delta (#phi_{E^{miss}_{T}} - #phi_{mu})";

  if(name.find("h_jet_emfra")!=string::npos) xtitle="Jet EMFrac";
  if(name.find("jet_el_ptratio")!=string::npos) xtitle="El p_{T}/ Jet p_{T}";

    
  if(name.find("muons_eta")!=string::npos)xtitle="Muon #eta";
  if(name.find("muons_phi")!=string::npos)xtitle="Muon #phi";
  if(name.find("MuonPt")!=string::npos)xtitle="Muon p_{T} [GeV]";
  if(name.find("MuonD0")!=string::npos)xtitle="d0";
  if(name.find("MuonD0Sig")!=string::npos)xtitle="d0/#Sigma_{d0}";
  if(name.find("leadingMuonPt")!=string::npos)xtitle="Lead p_{T} [GeV]";
  if(name.find("secondMuonPt")!=string::npos)xtitle="Second p_{T} [GeV]";
  if(name.find("thirdMuonPt")!=string::npos)xtitle="Third p_{T} [GeV]";

  if(name.find("electrons_eta")!=string::npos)xtitle="Electron #eta";
  if(name.find("electrons_phi")!=string::npos)xtitle="Electron #phi";
  if(name.find("el_pt")!=string::npos)xtitle="Electron p_{T} [GeV]";
  if(name.find("leadingElectronPt")!=string::npos)xtitle="Lead p_{T} [GeV]";
  if(name.find("secondElectronPt")!=string::npos)xtitle="Second p_{T} [GeV]";
  if(name.find("thirdELectronPt")!=string::npos)xtitle="Third p_{T} [GeV]";
  
  if(name.find("charge")!=string::npos)xtitle="sum of lepton charge";

  if(name.find("mumumass")!=string::npos)xtitle="m(#mu#mu) [GeV]";
  if(name.find("eemass")!=string::npos)xtitle="m(ee) [GeV]";
  if(name.find("emumass")!=string::npos)xtitle="m(e#mu) [GeV]";
  
  if(name.find("jets_eta")!=string::npos)xtitle="jet #eta";
  if(name.find("jets_phi")!=string::npos)xtitle="jet #phi";
  if(name.find("Njets")!=string::npos)xtitle="Number of jets";
  if(name.find("Nbjet")!=string::npos)xtitle="Number of bjets";
  if(name.find("bTag")!=string::npos)xtitle="CSV";

  if(name.find("el1jet_mindr")!=string::npos)xtitle="min#Delta R(e_{1}j)";
  if(name.find("el2jet_mindr")!=string::npos)xtitle="min#Delta R(e_{2}j)";

  if(name.find("leadMuonJetdR")!=string::npos)xtitle="min#Delta R(#mu j)";
  if(name.find("leadJetdR")!=string::npos)xtitle="min#Delta R(jj)";
  if(name.find("mu1jjmass")!=string::npos)xtitle="m(#mu_{1}jj) [GeV]";
  if(name.find("mu2jjmass")!=string::npos)xtitle="m(#mu_{2}jj) [GeV]";
  if(name.find("mumujjmass")!=string::npos)xtitle="m(#mu#mujj) [GeV]";

  if(name.find("leadElectronJetdR")!=string::npos)xtitle="min#Delta R(e_j)";
  if(name.find("e1jjmass")!=string::npos)xtitle="m(e_{1}jj) [GeV]";
  if(name.find("e2jjmass")!=string::npos)xtitle="m(e_{2}jj) [GeV]";
  if(name.find("eejjmass")!=string::npos)xtitle="m(eejj) [GeV]";

  if(name.find("leadingMuonIso")!=string::npos)xtitle="PF Iso #mu_{1} [GeV]";
  if(name.find("secondMuonIso")!=string::npos)xtitle="PF Iso #mu_{2} [GeV]";

  if(name.find("leadingElectronIso")!=string::npos)xtitle="PF Iso e_{1} [GeV]";
  if(name.find("secondELectronIso")!=string::npos)xtitle="PF Iso e_{2} [GeV]";

  if(name.find("MuonD0_")!=string::npos)xtitle="d0";
  if(name.find("MuonD0Sig")!=string::npos)xtitle="d0sig";
  
  if(name.find("D0_")!=string::npos)xtitle="d0";
  if(name.find("D0Sig")!=string::npos)xtitle="d0sig";

  if(name.find("nVertice")!=string::npos)xtitle="Number of vertices";

  if(name.find("MuonJetdR")!=string::npos)xtitle="mindR(#mu,jet)";
  if(name.find("ElectronJetdR")!=string::npos)xtitle="mindR(e,jet)";
  if(name.find("LeadJetdR")!=string::npos)xtitle="mindR(jet,jet)";
  if(name.find("LeadMuondR")!=string::npos)xtitle="mindR(#mu,#mu)";
  if(name.find("LeadElectrondR")!=string::npos)xtitle="mindR(e,e)";
  

  if(name.find("muon_deta_")!=string::npos)xtitle="#Delta #eta (#mu,#mu)";
  if(name.find("el_deta_")!=string::npos)xtitle="#Delta #eta (e,e)";
  if(name.find("leaddimudeltaR_")!=string::npos)xtitle="#Delta R (#mu,#mu)";
  if(name.find("leaddieldeltaR_")!=string::npos)xtitle="#Delta R (e,e)";

  if(name.find("dijetsmass")!=string::npos)xtitle="m(j_{1}j_{2}) [GeV]";
  if(name.find("leaddijetdr")!=string::npos)xtitle="#Delta R(j_{1}j_{2})";
  if(name.find("leadingJetPt")!=string::npos)xtitle="jet1 p_{T} [GeV]";
  if(name.find("secondJetPt")!=string::npos)xtitle="jet2 p_{T} [GeV]";



  hist->GetXaxis()->SetTitle(xtitle.c_str());
  hist->GetYaxis()->SetTitle(ytitle.c_str());

  return;
}


bool HistInGev(string name){
  
  bool ingev=false;
  if(name.find("_pt_")!=string::npos)ingev=true;
  if(name.find("mass_")!=string::npos)ingev=true;
  
  return ingev;

}


float  GetMaximum(TH1* h_data, TH1* h_up, bool ylog, string name){

  float yscale= 2.;
  if(!showdata) yscale = 2.;
  
  cout << name << endl;
  //if(name.find("eta")!=string::npos) yscale*=1.5;
  //if(name.find("MET")!=string::npos) yscale*=1.;
  //if(name.find("charge")!=string::npos) yscale*=2.5;
  //if(name.find("deltaR")!=string::npos) yscale*=2.;
  
  float max_data = h_data->GetMaximum()*yscale;
  float max_bkg = h_up->GetMaximum()*yscale;

  
  if(max_data > max_bkg) return max_data;
  else return max_bkg;
  
  return -1000.;
}



float GetTotal(TString cut, vector<pair<TString,float> > samples){
  
  float total(0.);
  for(vector<pair<TString,float> >::iterator it = samples.begin(); it!=samples.end(); it++){
    total += GetIntegral(cut,(*it).first,"MC");
  }
  
  return total;    
}


float GetStatError2(TString cut, vector<pair<TString,float> > samples){  
  float err = GetStatError(cut,samples);
  err = err*err;
  return err;
}

float GetStatError(TString cut, vector<pair<TString,float> > samples){  

  TString path  = mcloc;
  
  int isample=0;
  TFile* f0 =  TFile::Open((path+ fileprefix + samples.at(isample).first +  filepostfix).Data());  

  TH1* h_tmp=NULL;
  if((f0->Get(cut.Data()))){
    h_tmp = dynamic_cast<TH1*> ((f0->Get(cut.Data()))->Clone());
  }
    float stat_error(-99999.);

  while(!h_tmp){
    isample++;
    f0 =  TFile::Open((path+ fileprefix + samples.at(isample).first +  filepostfix).Data());
    if((f0->Get(cut.Data()))) h_tmp = dynamic_cast<TH1*> ((f0->Get(cut.Data()))->Clone());
  }
    
  for(unsigned int i=isample+1; i < samples.size(); i++){
    TFile* f =  TFile::Open((path+ fileprefix + samples.at(i).first +  filepostfix).Data());
    if(!f->Get(cut.Data())) continue;
    TH1* h = dynamic_cast<TH1*> ((f->Get(cut.Data()))->Clone());
    h_tmp->Add(h);
    f->Close();
    if(i == (samples.size()- 1)){
      stat_error = Error(h_tmp);
    }
  }

  if(samples.size()==1) stat_error = Error(h_tmp);
  
  f0->Close();
  return stat_error;
  
}




float GetIntegral(TString cut, TString isample, TString type){
  
  TString filepath = mcloc  + fileprefix + isample + filepostfix;
  if(type.Contains("data")) filepath=dataloc;
  TFile* f =  TFile::Open(( filepath.Data()));
    
  if(!((f->Get(cut.Data())))){
    cout << "Histogram " << cut << " in "  << mcloc+  fileprefix + isample + filepostfix << " not found" << endl;
    return 0.;
  }
  

  TH1* h = dynamic_cast<TH1*> ((f->Get(cut.Data())->Clone()));
  
  
  if(!h) {
    cout << "Histogram " << cut << " in "  <<  (mcloc + fileprefix + isample + filepostfix) << " not found" << endl;
    return 0.;
  }
  float integral = h->Integral();
 
  f->Close();

  return integral;
  
}

float GetError(TString cut, TString isample, TString type){
  
  TString filepath = mcloc  + fileprefix + isample + filepostfix;
  if(type.Contains("data")) filepath=dataloc;
  TFile* f =  TFile::Open(( filepath.Data()));
  
  TH1* h = dynamic_cast<TH1*> ((f->Get(cut.Data())->Clone()));
  cout << h << endl;
  
  if(!h) {
    cout << "Histogram " << cut << " in "  << (path+ fileprefix + isample + filepostfix) << " not found" << endl;
    return 0.;
  }
  
      
  float err = Error(h);
  
  f->Close();

  return err;
  
}


float GetNormErr(TString cut, vector<pair<TString,float> > samples){
  
  float norm_err(0.);
  int i=0;
  for( vector<pair<TString,float> >::iterator it = samples.begin(); it!=samples.end(); it++, i++){
    norm_err += GetIntegral(cut,it->first,"MC")* it->second*GetIntegral(cut,it->first,"MC")* it->second;
  }
  
  return sqrt(norm_err);
}

float GetNormErr2(TString cut,  vector<pair<TString,float> > samples){

  float err = GetNormErr(cut,samples);
  err = err*err;
  return err;
  
}



float GetErr2(TString cut, vector<pair<TString,float> > samples, TString err_type,TString var){
  
  float err = GetErr(cut,samples,err_type,var);
  err = err*err;
  return err;

}

float GetErr(TString cut, vector<pair<TString,float> > samples, TString err_type,TString var){

  float total(0.);
  float total_witherr(0.);
  
  int i=0;
  for(vector<pair<TString,float> >::iterator it = samples.begin(); it!=samples.end(); it++, i++){
    total += GetIntegral(cut,it->first,("MC/"));
    total_witherr += GetIntegral(cut,it->first,("MC_" + err_type));
  }
  
  
  float err=  total - total_witherr;      
  

  if(err_type.Contains("MM")){    
    if((var.Contains("UP")||var.Contains("Up"))) {
      if(( ( total - total_witherr)< 0.)) return fabs(err);
      else return total*0.1;
    }
    if((var.Contains("DOWN")||var.Contains("Down")) && ( ( total - total_witherr > 0.))) return err;
    else return total*0.1;  
  }
  
  if((var.Contains("UP")||var.Contains("Up"))) {
    if(( ( total - total_witherr)< 0.)) return fabs(err);
    else return 0.;
  }
  if((var.Contains("DOWN")||var.Contains("Down"))){
    if( ( total - total_witherr > 0.)) return err;
    else return 0.;  
  }

    return err;

}



float GetSystPercent(TString cut, TString syst, pair<vector<pair<TString,float> >,TString > samples ){

  return ( 100.*(GetSyst(cut, syst,samples )/ Calculate(cut,"Normal",samples)));
}



float GetSyst(TString cut, TString syst, pair<vector<pair<TString,float> >,TString > samples ){
  
  if(syst.Contains("Stat"))return GetStatError(cut,samples.first) ;    
  if(syst.Contains("Normalisation")) return GetNormErr(cut,samples.first);

  if(syst.Contains("TOTAL"))return sqrt(  GetStatError2(cut,samples.first)+
					  GetNormErr2(cut,samples.first));  
  return -9999.;
}


float Calculate(TString cut, TString variance, pair<vector<pair<TString,float> >,TString > samples ){
  
  cout << cut << " " << variance << " " << samples.second << endl;
  
  if(samples.second.Contains("NonPrompt")){
    if(variance.Contains("Normal"))  return GetTotal(cut,samples.first) ;  
    if(variance.Contains("StatErr")) return GetStatError(cut,samples.first) ;  
  }
  
  
  if(variance.Contains("Up") || variance.Contains("UP")||variance.Contains("Down") || variance.Contains("DOWN")  ){
    
    return fabs(sqrt( (GetNormErr2(cut,samples.first))));
    
  }
  
  if(variance.Contains("Normal")) return GetTotal(cut,samples.first) ;    
  
  if(variance.Contains("StatErr")) return GetStatError(cut,samples.first) ;    
    
  return -999999.;

}




float Error(TH1* h){
  double err ;
  double integral = h->IntegralAndError(0,h->GetNbinsX(),err,"");
  
  return err;
}



void SetUpMasterConfig(string name){
  
  // Get list of cuts to plot
  ifstream master_config_name_file(name.c_str());
  if(!master_config_name_file) {
    cerr << "Did not find " + name + ", exiting ..." << endl;
    return;
  }
  while(!master_config_name_file.eof()) {
    string tmp;
    string tmppath;
    master_config_name_file >> tmp;
    master_config_name_file >> tmppath;
    
    if(tmp=="END") break;
    if(tmp.find("#")!=string::npos) continue;
    
    if(tmp=="mcpath") mcloc = tmppath;
    if(tmp=="datapath") dataloc = tmppath;
    if(tmp=="nonpromptpath") nonpromptloc = tmppath;
    if(tmp=="prefix") fileprefix = tmppath;
    if(tmp=="postfix") filepostfix = tmppath;
    if(tmp=="plottingpath") plotloc = tmppath;
    if(tmp=="cutpath")  cutloc = tmppath;
    if(tmp=="outputdir")    path = tmppath;

    if(tmp=="showdata")    {
      if (tmppath == "true") showdata=true;
      else showdata=false;
    }
    if(tmp=="ylog") {
      if (tmppath == "true")ylog=true;
      else ylog = false;
    }

    if(tmp=="usenp"){
      if (tmppath == "true")usenp = true;
      else usenp=false;
    }
    
    if(tmp=="samples"){
      listofsamples.push_back(tmppath);
    }
    
    if(tmp=="histdir") histdir = tmppath;
    
    cutfile = cutloc;
    histfile =  plotloc;
  }
}

void  SetUpConfig(vector<pair<pair<vector<pair<TString,float> >, int >, TString > >& samples, vector<string>& cut_label){
    
  cout << " /// MakeDataMCComplots::SetUpConfig " << endl;
  /// colours of histograms
  int tcol(0), zzcol(0), fcol(0), zcol(0), wzcol(0), sscol(0),  wwcol(0), wcol(0),  ttvcol(0), higgscol(0), vvvcol(0), vvcol(0), vgammacol(0);
  
  // Get list of cuts to plot  
  ifstream colour_name_file("Config/colour.txt");
  if(!colour_name_file) {
    cerr << "Did not find Config/colour.txt, exiting ..." << endl;
    return;
  }
  while(!colour_name_file.eof()) {        
    string histname;
    int col;
    colour_name_file >> histname;    
    if(histname=="END") break;
    colour_name_file >> col;

    if(histname=="tcol") tcol =col;
    if(histname=="zzcol") zzcol =col;
    if(histname=="fcol") fcol =col;
    if(histname=="zcol") zcol =col;
    if(histname=="wzcol")wzcol =col;
    if(histname=="sscol") sscol =col;
    if(histname=="wwcol") wwcol =col;
    if(histname=="wcol") wcol =col;
    if(histname=="higgscol") higgscol =col;
    if(histname=="ttvcol") ttvcol =col;
    if(histname=="vvvcol") vvvcol =col;
    if(histname=="vvcol") vvcol =col;
    if(histname=="vgammacol") vgammacol =col;
    
  }
  
  /// Setup list of samples: grouped into different processes 
  vector<pair<TString,float> > top = InitSample("top");
  vector<pair<TString,float> > ttbar = InitSample("ttbar");
  
  vector<pair<TString,float> > wz_py = InitSample("wz_py");
  vector<pair<TString,float> > zz_py = InitSample("zz_py");
  vector<pair<TString,float> > ww_py = InitSample("ww_py");
  vector<pair<TString,float> > wz_mg = InitSample("wz_mg");
  vector<pair<TString,float> > zz_mg = InitSample("zz_mg");
  vector<pair<TString,float> > zz_pow = InitSample("zz_pow");
  vector<pair<TString,float> > vv_mg = InitSample("vv_mg");
  vector<pair<TString,float> > vv_py = InitSample("vv_py");
  
  // Zjet
  vector<pair<TString,float> > z = InitSample("dy_");
  // Zjet + Zbb
  vector<pair<TString,float> > zplusbb = InitSample("dyplusbb");
  /// Wjet
  vector<pair<TString,float> > w = InitSample("wjet_");
  /// Wjet + Wbb
  vector<pair<TString,float> > wplusbb = InitSample("wjetplusbb");
  /// QCD samples
  vector<pair<TString,float> > QCD = InitSample("qcd");
  /// ALL same sign processes
  vector<pair<TString,float> > ss_mg = InitSample("ss_mg");

  vector<pair<TString,float> > vvv = InitSample("vvv");
  vector<pair<TString,float> > vv = InitSample("vv");
  vector<pair<TString,float> > ttv   = InitSample("ttv");
  vector<pair<TString,float> > higgs   = InitSample("higgs");
  vector<pair<TString,float> > vgamma   = InitSample("vgamma");


  /// NP is nonprompt
  vector<pair<TString,float> > np;
  np.push_back(make_pair("nonprompt",0.3));
  
  vector<pair<TString,float> > cf;
  cf.push_back(make_pair("chargeflip",0.2));
  
  for( unsigned int i = 0; i < listofsamples.size(); i++){
    if(listofsamples.at(i) =="ww_py")samples.push_back(make_pair(make_pair(ww_py,wwcol),"WW")); 
    if(listofsamples.at(i) =="zz_py")samples.push_back(make_pair(make_pair(zz_py,zzcol),"ZZ"));
    if(listofsamples.at(i) =="wz_py")samples.push_back(make_pair(make_pair(wz_py,wzcol),"WZ"));
    if(listofsamples.at(i) =="zz_mg")samples.push_back(make_pair(make_pair(zz_mg,zzcol),"ZZ"));
    if(listofsamples.at(i) =="wz_mg")samples.push_back(make_pair(make_pair(wz_mg,wzcol),"WZ"));
    if(listofsamples.at(i) =="zz_pow")samples.push_back(make_pair(make_pair(zz_pow,zzcol),"ZZ"));
    if(listofsamples.at(i) =="vv_py")samples.push_back(make_pair(make_pair(vv_py,vvcol),"VV"));
    if(listofsamples.at(i) =="vv_mg")samples.push_back(make_pair(make_pair(vv_mg,vvcol),"VV"));

    if(listofsamples.at(i) =="ss_mg")samples.push_back(make_pair(make_pair(ss_mg,sscol),"SS"));
    if(listofsamples.at(i) =="dy")samples.push_back(make_pair(make_pair(z,zcol),"DY"));
    if(listofsamples.at(i) =="dyplusbb")samples.push_back(make_pair(make_pair(zplusbb,zcol),"DY"));
    if(listofsamples.at(i) =="top")samples.push_back(make_pair(make_pair(top,tcol),"Top"));
    if(listofsamples.at(i) =="ttbar")samples.push_back(make_pair(make_pair(ttbar,tcol),"ttbar"));
    if(listofsamples.at(i) =="wjet")samples.push_back(make_pair(make_pair(w,wcol),"Wjet"));
    if(listofsamples.at(i) =="wjetplusbb")samples.push_back(make_pair(make_pair(wplusbb,wcol),"Wjet"));

    if(listofsamples.at(i) =="ttv")samples.push_back(make_pair(make_pair(ttv,ttvcol),"t#bar{t}+V"));
    if(listofsamples.at(i) =="vvv")samples.push_back(make_pair(make_pair(vvv,vvvcol),"VVV"));
    if(listofsamples.at(i) =="vgamma")samples.push_back(make_pair(make_pair(vgamma,vgammacol),"Vgamma"));
    if(listofsamples.at(i) =="higgs")samples.push_back(make_pair(make_pair(higgs,higgscol),"Higgs"));
    
    if(listofsamples.at(i) =="qcd")samples.push_back(make_pair(make_pair(QCD,fcol),"QCD"));
    if(listofsamples.at(i) =="nonprompt")samples.push_back(make_pair(make_pair(np,fcol),"nonprompt"));   
    if(listofsamples.at(i) =="chargeflip")samples.push_back(make_pair(make_pair(cf,zcol),"chargeflip"));   
  }

  ///// Fix cut flow code
  caption="Number of events containing one prompt loose electron in 19 fb$^{-1}$ of CMS data at 8~TeV";
  hist = "/h_leadingElectronPt";
  columnname="";

  return;

}


TCanvas* CompDataMC(TH1* hdata, TH1* hsig_40, TH1* hsig_80, TH1* hsig_100,TH1* hsig_150,TH1* hsig_200, TH1* hsig_300,TH1* hsig_400,TH1* hsig_500, vector<THStack*> mcstack,TH1* hup, TH1* hdown,TLegend* legend, const string hname, const  int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel) {
  
  TH1* hdata_clone_for_log = (TH1*)hdata->Clone( "log");

  string cname;
  if(hdata) cname= string("c_") + hdata->GetName();
  else cname = string("c_") + ((TNamed*)mcstack.at(0)->GetHists()->First())->GetName();
  
  string label_plot_type = "";
  //Create Canvases

  int W = 800;
  int H = 600;
  TCanvas* canvas = new TCanvas((cname+ label_plot_type).c_str(), (cname+label_plot_type).c_str(),10,10,W,H);
  TCanvas* canvas_log = new TCanvas((cname+ label_plot_type+"log").c_str(), (cname+label_plot_type+"log").c_str(),10,10,W,H);

  int H_ref = 600;
  int W_ref = 800;

  // references for T, B, L, R                                                                                                                                                                                   
  float T = 0.08*H_ref;
  float B = 0.15*H_ref;
  float L = 0.17*W_ref;
  float R = 0.04*W_ref;
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );
  canvas->SetTickx(0);
  canvas->SetTicky(0);

  canvas_log->SetFillColor(0);
  canvas_log->SetBorderMode(0);
  canvas_log->SetFrameFillStyle(0);
  canvas_log->SetFrameBorderMode(0);
  canvas_log->SetLeftMargin( L/W );
  canvas_log->SetRightMargin( R/W );
  canvas_log->SetTopMargin( T/H );
  canvas_log->SetBottomMargin( B/H );
  canvas_log->SetTickx(0);
  canvas_log->SetTicky(0);
    
  setTDRStyle();
  
  std::string title=canvas->GetName();
  std::string tpdf = "/home/jalmond/WebPlots/"+ path + "/histograms/"+folder+"/"+title+".png";
  std::string tlogpdf = "/home/jalmond/WebPlots/"+ path + "/histograms/"+folder+"/"+title+"_log.png";
  
  ///####################   Standard plot
  canvas_log->SetLogy();
  canvas->cd();
  
  
  //// %%%%%%%%%% TOP HALF OF PLOT %%%%%%%%%%%%%%%%%%
  TH1* h_nominal = MakeSumHist2(mcstack.at(0));
  MakeLabel(0.2,0.8);

  TH1* errorband = MakeErrorBand(h_nominal,hup, hdown) ;
  SetNomBinError(h_nominal, hup, hdown);
  
  cout << "Scaling data by " << scale << endl;


  
  TH1 *frame = new TH1F("frame","",1000,40,600);
  frame->SetMinimum(1e-5);
  frame->SetMaximum(10);
  frame->SetDirectory(0);
  frame->SetStats(0);
  frame->GetXaxis()->SetTitle("m_{N} (GeV)");
  //frame->GetXaxis()->SetTitleSize(0.045);                                                                                                                                                                      
  frame->GetXaxis()->SetTitleOffset(1.05);
  //frame->GetXaxis()->SetTickLength(0.02);                                                                                                                                                                      
  //frame->GetXaxis()->SetLabelSize(0.04);                                                                                                                                                                       
  frame->GetXaxis()->SetRangeUser(40, 500);
  frame->GetYaxis()->SetTitle("#||{V_{#muN}}^{2}");
  //frame->GetYaxis()->SetTitleSize(0.045);                                                                                                                                                                      
  //frame->GetYaxis()->SetTitleOffset(0.95);                                                                                                                                                                     
  //frame->GetYaxis()->SetLabelSize(0.04);                                                                                                                                                                       
  frame->GetYaxis()->SetRangeUser(0.00001,1.0);
  frame->Draw(" ");
  
  
  //hdata->Draw("9pX0");
  //hdata->GetYaxis()->SetTitleOffset(1.5);
  hsig_40->Draw("hist9");
  
  mcstack.at(0)->Draw("HIST9same");
  //hdata->Draw("9samepX0");
  //hdata->Draw("axis same");
  errorband->Draw("E2same");
  
  /// Draw data again
  /*const double alpha = 1 - 0.6827;
    TGraphAsymmErrors * g = new TGraphAsymmErrors(hdata);
    for (int i = 0; i < g->GetN(); ++i) {
    int N = g->GetY()[i];
    double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
    double U =  (N==0) ?  ( ROOT::Math::gamma_quantile_c(alpha,N+1,1) ) :
    ( ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) );
    if ( N!=0 ) {
    g->SetPointEYlow(i, N-L );
    g->SetPointEXlow(i, 0);
    g->SetPointEYhigh(i, U-N );
    g->SetPointEXhigh(i, 0);
    }
    else {
    g->SetPointEYlow(i, 0.);
    g->SetPointEXlow(i, 0);
    g->SetPointEYhigh(i, 0.);
    g->SetPointEXhigh(i, 0);
    }
    }
    g->SetLineWidth(2.0);
    g->SetMarkerSize(0.);
    g->Draw( ("9samep") );
    
    hdata->SetMarkerStyle(20);
    hdata->SetMarkerSize(1.2);
    hdata->SetLineWidth(2.0);
    hdata->Draw( ("9samepX0") );
  */
  //hsig_40->Draw("hist9same");
  //hsig_80->Draw("hist9same");
  hsig_100->Draw("hist9same");
  hsig_150->Draw("hist9same");
  //hsig_200->Draw("hist9same");
  //hsig_300->Draw("hist9same");
  //hsig_400->Draw("hist9same");
  //hsig_500->Draw("hist9same");

  //legend->AddEntry(hsig_40, "m_{N} = 40 GeV","l"); 
  //legend->AddEntry(hsig_80, "m_{N} = 80 GeV","l"); 
  legend->AddEntry(hsig_100, "m_{N} = 100 GeV","l"); 
  legend->AddEntry(hsig_150, "m_{N} = 150 GeV","l"); 
  //legend->AddEntry(hsig_200, "m_{N} = 200 GeV","l"); 
  //legend->AddEntry(hsig_300, "m_{N} = 300 GeV","l"); 
  //legend->AddEntry(hsig_400, "m_{N} = 400 GeV","l"); 
  //legend->AddEntry(hsig_500, "m_{N} = 500 GeV","l"); 
  legend->Draw("same");

  /*if(usedata){
    //// %%%%%%%%%% BOTTOM (SIGNIFICANCE) HALF OF PLOT %%%%%%%%%%%%%%%%%%

    /// Make significance hist

    TH1* h_significance=(TH1F*)hdata->Clone();
    TH1* h_divup=(TH1F*)hup->Clone();
    TH1* h_divdown=(TH1F*)hdown->Clone();

    TH1* errorbandratio = (TH1*)h_nominal->Clone("AA");

    hdata->GetXaxis()->SetLabelSize(0.); ///
    hdata->GetXaxis()->SetTitle("");

    h_divup->Divide(h_nominal);
    h_divdown->Divide(h_nominal);

    for(int i=1; i < errorbandratio->GetNbinsX()+1; i++){

      float bc = ((h_divup->GetBinContent(i)+h_divdown->GetBinContent(i))/2.);
      float bd = ((h_divup->GetBinContent(i)-h_divdown->GetBinContent(i))/2.);

      errorbandratio->SetBinContent(i,bc);
      errorbandratio->SetBinError(i,bd);
    }

    errorbandratio->SetFillStyle(3354);
    errorbandratio->SetFillColor(kBlue-8);
    errorbandratio->SetMarkerStyle(0);

    for(int i=1; i < h_significance->GetNbinsX()+1; i++){
      float num = h_significance->GetBinContent(i) - h_nominal->GetBinContent(i);
      float denom = sqrt( (h_significance->GetBinError(i)*h_significance->GetBinError(i) + h_nominal->GetBinError(i)*h_nominal->GetBinError(i)));
      float sig = 0.;
      if(denom!=0.) sig = num / denom;
      h_significance->SetBinContent(i,sig);
    }


    // How large fraction that will be taken up by the data/MC ratio part
    double FIGURE2_RATIO = 0.35;
    double SUBFIGURE_MARGIN = 0.15;
    canvas->SetBottomMargin(FIGURE2_RATIO);
    TPad *p = new TPad( "p_test", "", 0, 0, 1, 1.0 - SUBFIGURE_MARGIN, 0, 0, 0);  // create new pad, fullsize to have equal font-sizes in both plots
    p->SetTopMargin(1-FIGURE2_RATIO);   // top-boundary (should be 1 - thePad->GetBottomMargin() )
    p->SetFillStyle(0);     // needs to be transparent
    p->Draw();
    p->cd();
    
    h_significance->SetFillColor(kGray+1);
    h_significance->SetLineColor(kGray+1);

    h_significance->GetYaxis()->SetNdivisions(10204);
    h_significance->GetYaxis()->SetTitle("Significance");
    h_significance->GetYaxis()->SetRangeUser(-4., 4.);
    h_significance->GetXaxis()->SetRangeUser(xmin, xmax);
    h_significance->Draw("hist");
    TLine *line = new TLine(h_significance->GetBinLowEdge(h_significance->GetXaxis()->GetFirst()),1.0,h_significance->GetBinLowEdge(h_significance->GetXaxis()->GetLast()+1),1.0);
    
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->Draw();
    h_significance->Draw("HISTsame");
    
  }
  */
  canvas->Print(tpdf.c_str(), ".png");

  //// %%%%%%%%%% PRINT ON LOG
  canvas_log->cd();

  
  //// %%%%%%%%%% TOP HALF OF PLOT %%%%%%%%%%%%%%%%%%
  
  if(usedata){
    hdata_clone_for_log->GetYaxis()->SetRangeUser(1., ymax*100.);
    hdata_clone_for_log->Draw("p");
    mcstack.at(0)->Draw("HIST same");
    hdata_clone_for_log->Draw("p same");
    hdata_clone_for_log->Draw("axis same");
    errorband->Draw("E2same");
  }
  else{
    errorband->GetXaxis()->SetRangeUser(xmin,xmax);
    errorband->GetYaxis()->SetRangeUser(ymin,ymax*100.);
    errorband->Draw("E2");
    mcstack.at(0)->Draw("same HIST");
    errorband->Draw("E2same");
  }
  legend->Draw("same");
  
  if(usedata){
    //// %%%%%%%%%% BOTTOM (SIGNIFICANCE) HALF OF PLOT %%%%%%%%%%%%%%%%%%
    /// Make significance hist
    
    TH1* h_significance=(TH1F*)hdata_clone_for_log->Clone();
    TH1* h_divup=(TH1F*)hup->Clone();
    TH1* h_divdown=(TH1F*)hdown->Clone();

    TH1* errorbandratio = (TH1*)h_nominal->Clone("AAA");

    hdata_clone_for_log->GetXaxis()->SetLabelSize(0.); ///
    hdata_clone_for_log->GetXaxis()->SetTitle("");

    h_divup->Divide(h_nominal);
    h_divdown->Divide(h_nominal);

    for(int i=1; i < errorbandratio->GetNbinsX()+1; i++){

      float bc = ((h_divup->GetBinContent(i)+h_divdown->GetBinContent(i))/2.);
      float bd = ((h_divup->GetBinContent(i)-h_divdown->GetBinContent(i))/2.);

      errorbandratio->SetBinContent(i,bc);
      errorbandratio->SetBinError(i,bd);
    }
    errorbandratio->SetFillStyle(3354);
    errorbandratio->SetFillColor(kBlue-8);
    errorbandratio->SetMarkerStyle(0);

    for(int i=1; i < h_significance->GetNbinsX()+1; i++){
      float num = h_significance->GetBinContent(i) - h_nominal->GetBinContent(i);
      float denom = sqrt( (h_significance->GetBinError(i)*h_significance->GetBinError(i) + h_nominal->GetBinError(i)*h_nominal->GetBinError(i)));
      float sig = 0.;
      if(denom!=0.) sig = num / denom;
      h_significance->SetBinContent(i,sig);
    }


    // How large fraction that will be taken up by the data/MC ratio part
    double FIGURE2_RATIO = 0.35;
    double SUBFIGURE_MARGIN = 0.15;
    canvas_log->SetBottomMargin(FIGURE2_RATIO);
    TPad *p = new TPad( "p_test", "", 0, 0, 1, 1.0 - SUBFIGURE_MARGIN, 0, 0, 0);  // create new pad, fullsize to have equal font-sizes in both plots
    p->SetTopMargin(1-FIGURE2_RATIO);   // top-boundary (should be 1 - thePad->GetBottomMargin() )
    p->SetFillStyle(0);     // needs to be transparent
    p->Draw();
    p->cd();

    h_significance->SetFillColor(kGray+1);
    h_significance->SetLineColor(kGray+1);

    h_significance->GetYaxis()->SetNdivisions(10204);
    h_significance->GetYaxis()->SetTitle("Significance");
    h_significance->GetYaxis()->SetRangeUser(-4., 4.);
    h_significance->GetXaxis()->SetRangeUser(xmin, xmax);
    h_significance->Draw("hist");
    TLine *line = new TLine(h_significance->GetBinLowEdge(h_significance->GetXaxis()->GetFirst()),1.0,h_significance->GetBinLowEdge(h_significance->GetXaxis()->GetLast()+1),1.0);

    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->Draw();
    h_significance->Draw("HISTsame");
  }
  
  canvas_log->Print(tlogpdf.c_str(), ".png");
  
  
  return canvas;



}



TH1* MakeSumHist2(THStack* thestack){

  TH1* hsum=0;
  TList* list = thestack->GetHists();
  TIter it(list, true);
  TObject* obj=0;
  while( (obj = it.Next()) ) {
    TH1* h = dynamic_cast<TH1*>(obj);
    if(!hsum) hsum = (TH1*)h->Clone( (string(h->GetName()) + "_sum").c_str() );
    else {
      hsum->Add(h, 1.0);
    }
  }//hist loop

  return hsum;
}



void SetNomBinError(TH1* hnom, TH1* hup, TH1* hdown){

  for(int i=1; i < hnom->GetNbinsX()+1; i++){

    float err1 = fabs(hnom->GetBinContent(i)- hup->GetBinContent(i));
    float err2 = fabs(hnom->GetBinContent(i)- hdown->GetBinContent(i));

    if(err1 > err2 ) hnom->SetBinError(i, err1);
    if(err2 > err1 ) hnom->SetBinError(i, err2);
  }
  return;
}



TH1* MakeErrorBand(TH1* hnom, TH1* hup, TH1* hdown){

  TH1* errorband = (TH1*)hnom->Clone("aa");

  for(int i=1; i < errorband->GetNbinsX()+1; i++){

    float bin_content = (hup->GetBinContent(i)+ hdown->GetBinContent(i))/2.;
    float bin_error = (hup->GetBinContent(i)- hdown->GetBinContent(i))/2.;

    errorband->SetBinContent(i,bin_content);
    errorband->SetBinError(i,bin_error);
  }

  errorband->SetFillStyle(3354);
  errorband->SetFillColor(kBlue-8);
  errorband->SetMarkerSize(0);
  errorband->SetMarkerStyle(0);
  errorband->SetLineColor(kWhite);
  errorband->Draw("E2Same");

  return errorband;

}


void MakeLabel(float rhcol_x, float rhcol_y){
  TLatex label;
  label.SetTextSize(0.04);
  label.SetTextColor(2);
  label.SetTextFont(42);
  label.SetNDC();
  label.SetTextColor(1);
  label.DrawLatex(rhcol_x,rhcol_y,"#int L dt = 20.4 fb^{-1}");
  label.DrawLatex(rhcol_x + 0.2,rhcol_y ,"#sqrt{s}= 8 TeV");
  label.SetTextSize(0.045);

  label.DrawLatex(rhcol_x+0.115, rhcol_y + 0.09,"Work In Progress");
  label.SetTextFont(72);
  label.DrawLatex(rhcol_x, rhcol_y + 0.09,"CMS");

  return;
}


void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }

  cout << lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }

  pad->cd();

  float posX_;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = 1-t - 0.045*(1-t-b);
          float xl_0 = posX_;
          float yl_0 = posY_ - 0.15;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, posY_, cmsText);
          if( writeExtraText )
            {
              latex.SetTextFont(extraTextFont);
              latex.SetTextAlign(align_);
              latex.SetTextSize(extraTextSize*t);
              latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
            }
        }
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
        {
          posX_ =   l +  relPosX*(1-l-r);
          posY_ =   1-t+lumiTextOffset*t;
        }
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);
    }
  return;
}

