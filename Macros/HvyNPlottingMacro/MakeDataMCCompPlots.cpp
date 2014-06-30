// STD includes
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <map>
#include <sstream>

/// Local includes
#include "HistUtils.hpp"

///ROOT includes
#include "TH1.h"
#include "TH3.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "THStack.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TStyle.h"


using namespace std;

/// LIST OF FUNCIONS FOR PLOTTER CODE
int MakePlots(std::string hist, std::string histname, float xmin,float  xmax, int rebin);

void PrintCanvas(TCanvas* c1, std::string folder, std::string plotdesciption,  std::string title, TString mass, TString channel, string hname);
bool repeat(string hname);
int MakeCutFlow_Plots(string configfile, string histname , float xmin,float  xmax, int rebin);


TCanvas* DrawMC(TH1* hsig,  const string hname, const int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel, TString mass, string hname);
TCanvas* DrawMC(TH2* hsig,  const string hname, const int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel, TString mass, string hname);
TCanvas* DrawMC(TH3* hsig,  const string hname, const int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel, TString mass, string hname);


void SetTitles(TH1* hist, string name);
void SetTitles(TH2* hist, string name);
void SetTitles(TH3* hist, string name);
bool HistInGev(string name);
void fixOverlay();
void setTDRStyle();


std::map<std::string,std::string> _htmls;

void  SetUpMasterConfig(std::string filename);


//// GLOBAL VARIABLES
int isig=0;
map<string,int> norepeatplot;
TString columnname="";
TString caption="";
  
std::string hist;
bool showdata=true;
std::string cutfile;
std::string histfile;
bool ylog;
bool usenp(false);

TString channel;

std::string plotloc="";
std::string path;
std::string message;
std::string fileprefix="";
std::string filepostfix = "";

std::ofstream masterpage;
std::ofstream histpage;

vector<string> cuts; 
vector<string> allcuts; 


string cutloc ="";
string histdir="";

string output_index_path="";
string output_path = "";



int main(int argc, char *argv[]) {
  
  TH1::SetDefaultSumw2(true);
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
  
  //read in config
  
  string configfile = "Config/hnplots.txt";
  
  SetUpMasterConfig(configfile);
  

  std::string masterpname = "/home/jalmond/WebPlots/HNSignal/indexCMS.html";

  system(("mkdir /home/jalmond/WebPlots/HNSignal/" ));
  system(("mkdir /home/jalmond/WebPlots/HNSignal/histograms/"));

  masterpage.open(masterpname.c_str());
  
  masterpage << "<html><font face=\"Helvetica\"><head><title> HvyN Analysis </title></head>" << endl;
  masterpage << "<body>" << endl;
  masterpage << "<h1> Heavy Neutrino Signal Plots </h1>" << endl;
  masterpage << "<br> <font size=\"4\"><b> " << message <<  " </b></font> <br><br>" << endl;
  
  ifstream  histo_name_file(histfile.c_str());
  while(!histo_name_file.eof()) {
    string hist;
    int rebin;
    double xmin,xmax;
    histo_name_file >> hist;
    if(repeat(hist))continue;
    if(hist=="END") break;
    histo_name_file >> rebin;
    histo_name_file >> xmin;
    histo_name_file >> xmax;
    
    if(hist.find("#")!=string::npos) continue;
    
    masterpage << "<a href=\"histograms/" + hist + "/indexCMS.html\">"+ hist + "</a><br>" << endl;
    cout << "ADD hist = " << hist << endl;
    int a =MakeCutFlow_Plots(configfile , hist , xmin, xmax,rebin);
  }

  masterpage.close();
  system(("scp -r /home/jalmond/WebPlots/HNSignal/ jalmond@lxplus5.cern.ch:~/www/SNU/WebPlots/"));
  cout << "Open plots in " << output_index_path << endl; 
  return 0;
}


void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  
  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);
  
  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
  
  tdrStyle->SetEndErrorSize(2);
  //  tdrStyle->SetErrorMarker(20);
  //  tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);
  
  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);

  
  // tdrStyle->SetDateY(Float_t y = 0.01);
  
  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.12);
  tdrStyle->SetPadLeftMargin(0.12);
  tdrStyle->SetPadRightMargin(0.1);
  
  // For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

  // For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.4);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);
  
  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:
  tdrStyle->SetPaperSize(20.,20.);


  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();

}



// fixOverlay: Redraws the axis

void fixOverlay() {
  gPad->RedrawAxis();
}


int MakeCutFlow_Plots(string configfile, string histname, float xmin,float  xmax, int rebin){
  
  std::string phistname = "/home/jalmond/WebPlots/HNSignal/histograms/" + histname  + "/indexCMS.html";
  output_path = "/home/jalmond/WebPlots/HNSignal/" ;
  output_index_path = string("https://jalmond.web.cern.ch/jalmond/SNU/WebPlots/")+ "/HNSignal/indexCMS.html";
  system(("mkdir /home/jalmond/WebPlots/HNSignal/histograms/" + histname + "/").c_str());
  cout << "HIST page is set to " << phistname.c_str() << endl;

  histpage.open(phistname.c_str());
  
  
  int M=MakePlots(histdir, histname, xmin,xmax, rebin);  

  return M;

}



int MakePlots(string hist, string h_name, float xmin,float  xmax, int rebin) {

 
  //// What samples to use in histogram
  vector<pair<pair<vector<pair<TString,float> >, int >, TString > > samples;  
  vector<string> cut_label;
  //// Sets flags for using CF/NP/logY axis/plot data/ and which mc samples to use
  
  cuts.clear();
  allcuts.clear();
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
	   << "<th> Signal Mass </th>"
	   << "<th> Channel </th>"
	   << "<th> Signal Plot </th>"
	   << "<th> Signal LogPlots </th>"
	   << "</tr>" << endl;
  
  vector<string> vchannel;
  vchannel.push_back("ee");
  //vchannel.push_back("mumu");
  
  for(vector<string>::iterator it=vchannel.begin(); it!= vchannel.end(); it++){
    
    vector<TString> masspoints;
    masspoints.push_back("50");
    masspoints.push_back("70");
    masspoints.push_back("90");
    masspoints.push_back("100");
    masspoints.push_back("125");
    masspoints.push_back("150");
    masspoints.push_back("175");
    masspoints.push_back("200");
    masspoints.push_back("225");
    masspoints.push_back("250");
    masspoints.push_back("275");
    masspoints.push_back("300");
    masspoints.push_back("400");
    masspoints.push_back("500");
    masspoints.push_back("600");
    masspoints.push_back("700");

    for(int i =0; i < masspoints.size(); i++){
      
      
      for(unsigned int ncut=0; ncut<allcuts.size();  ncut++){
	string name = allcuts.at(ncut) + "/" + "h_"+ h_name+ "_" + allcuts.at(ncut);
	
	cout << "\n------------------------------------------------------- \n" << endl;
	cout << "Making histogram " << name <<  " " << " mass = " << masspoints.at(i) << "channel = " << *it<<endl;
	
	TString sigloc = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHN" + (*it) + masspoints.at(i) + "_nocut_5_3_14.root";
      
	TFile* sig =  TFile::Open((sigloc).Data());
	cout << "WandNmass" << endl;
	if(TString(name).Contains("WandNmass")){
	  cout << name << endl;
	  TH2* hsig = dynamic_cast<TH2*> ((sig->Get(name.c_str()))->Clone());
	  cout << "WandNmass1" << endl;

	  cout << "TH@ " << hsig << endl;
          SetTitles(hsig,name);
          float ymin=0.;
          float ymax=hsig->GetMaximum();
	  
	  
          TCanvas* c = DrawMC(hsig, name,rebin,xmin,xmax, ymin,ymax, path, histdir,ylog, showdata, *it,  masspoints.at(i) , h_name);
          cout << " Made canvas" << endl;

          string canvasname = c->GetName();
          //canvasname.erase(0,4);

          PrintCanvas(c, histdir, canvasname, h_name , masspoints.at(i), *it, h_name);
          sig->Close();
	}
	else if(TString(name).Contains("3Dparm")){
	  
	  cout << name << endl;
	  TH3* hsig = dynamic_cast<TH3*> ((sig->Get(name.c_str()))->Clone());
          cout << hsig << endl;
	  SetTitles(hsig,name);
	  cout << "Set title" << endl;
	  
          float ymin=0.;
          float ymax=hsig->GetMaximum();
	  
	  cout << "Draw" << endl;
          TCanvas* c = DrawMC(hsig, name,rebin,xmin,xmax, ymin,ymax, path, histdir,ylog, showdata, *it,  masspoints.at(i) , h_name);
          cout << " Made canvas" << endl;

          string canvasname = c->GetName();
          //canvasname.erase(0,4);

          PrintCanvas(c, histdir, canvasname, h_name , masspoints.at(i), *it, h_name);
          sig->Close();
	}
	else{
	  cout << "WandNmass3" << endl;
	  TH1* hsig = dynamic_cast<TH1*> ((sig->Get(name.c_str()))->Clone());
	  SetTitles(hsig,name);
	  
	  float ymin=0.;
	  float ymax=hsig->GetMaximum();
	  
	  TCanvas* c = DrawMC(hsig, name,rebin,xmin,xmax, ymin,ymax, path, histdir,ylog, showdata, *it,  masspoints.at(i) , h_name);      	
	  cout << " Made canvas" << endl;
	  
	  string canvasname = c->GetName();
	  //canvasname.erase(0,4);
	  
	  PrintCanvas(c, histdir, canvasname, h_name , masspoints.at(i), *it, h_name);
	  sig->Close();
	}
      }    
    }
  }       
  histpage.close();
  
  return 0;
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
void PrintCanvas(TCanvas* c1, string folder, string plot_description, string title, TString mass, TString channel, string hname){

  std::string tpdf = "/home/jalmond/WebPlots/HNSignal/histograms/" + hname + "/"+ title;
  
  cout << "title = " << title << endl;
  if(plot_description.empty())plot_description=title;
  histpage << "<tr><td>"<< title <<"</td>"<<endl;
  histpage << "<td>"<< mass <<"</td>"<<endl;
  histpage << "<td>"<< channel <<"</td>"<<endl;
  histpage <<"<td>"<<endl;
  histpage << "<a href=\"" << plot_description.c_str() << ".png\">";
  histpage << "<img src=\"" << plot_description.c_str() << ".png\" width=\"100%\"/>";
  histpage << "</td>" << endl;
  histpage <<"<td>"<<endl;
  histpage << "<a href=\"" << plot_description.c_str() << "_log.png\">";
  histpage << "<img src=\"" << plot_description.c_str() << "_log.png\" width=\"100%\"/>";
  histpage << "</td>" << endl;

  
  return;
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////







void SetTitles(TH1* hist, string name){
  
  string xtitle ="";
  string ytitle ="Entries";

  float binedge_up = hist->GetBinLowEdge(2);
  float binedge_down = hist->GetBinLowEdge(1);
  
  float width = binedge_up - binedge_down;
  
  std::ostringstream str_width;
  str_width<< width;

  if(HistInGev(name)) ytitle = "Entries / " +str_width.str() + " GeV";
  
  if(name.find("h_MET")!=string::npos)xtitle="E^{miss}_{T} [GeV]"; 
  if(name.find("h_MET_phi")!=string::npos)xtitle="#phi_{E^{miss}_{T}} "; 

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
  if(name.find("leadElectronPt")!=string::npos)xtitle="Lead p_{T} [GeV]";
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


void SetTitles(TH2* hist, string name){
  std::string xtitle, ytitle;
  if(name.find("WandNmass")) {
    xtitle = "m_{W} [GeV]";
    ytitle = "m_{N} [GeV]";
    
  }
  hist->GetXaxis()->SetTitle(xtitle.c_str());
  hist->GetYaxis()->SetTitle(ytitle.c_str());

  return;
}

void SetTitles(TH3* hist, string name){
  std::string xtitle, ytitle;
  if(name.find("3Dparm")) {
    
  }
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
    
    if(tmp=="prefix") fileprefix = tmppath;
    if(tmp=="postfix") filepostfix = tmppath;
    
    if(tmp=="plottingpath") plotloc = tmppath;
    if(tmp=="cutpath")  cutloc = tmppath;
    if(tmp=="cutpath")  cerr << "tmppath = " << tmppath << std::endl;

    if(tmp=="outputdir")    path = tmppath;

    cutfile = cutloc;
    histfile =  plotloc;
  }

}




TCanvas* DrawMC(TH1* hsig ,  const string hname, const  int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel, TString mass, string dirname) {
  
  string cname =string("c_") + hsig->GetName() + string(mass)+ "_" + string(channel);
  
  string label_plot_type = "";
  //Create Canvases
  TCanvas* canvas = new TCanvas((cname+ label_plot_type).c_str(), (cname+label_plot_type).c_str(), 800, 600);
  TCanvas* canvas_log = new TCanvas((cname+ label_plot_type+"log").c_str(), (cname+label_plot_type+"log").c_str(), 800, 600);

  
  std::string title=canvas->GetName();
  std::string tpdf = "/home/jalmond/WebPlots/HNSignal/histograms/"+ dirname+"/"+title+".png";
  std::string tlogpdf = "/home/jalmond/WebPlots/HNSignal/histograms/"+dirname+"/" + title+"_log.png";
  
  canvas_log->SetLogy();
  canvas->cd();
  
  hsig->SetFillColor(kRed-4);
  hsig->SetFillStyle(3004);
  hsig->Draw("HIST");
  
  float mean = hsig->GetMean();
  TLatex label;
  label.SetTextSize(0.045);
  label.SetTextFont(42);
  label.SetNDC();
  label.SetTextColor(1);

  std::ostringstream buff;
  buff<< mean;
  string slabel = "Mean =" + buff.str();
  label.DrawLatex(0.7,0.8,slabel.c_str());

  canvas->Print(tpdf.c_str(), ".png");

  //// %%%%%%%%%% PRINT ON LOG
  canvas_log->cd();
  
  hsig->Draw("HIST");

  
  canvas_log->Print(tlogpdf.c_str(), ".png");
   
  return canvas;

}



TCanvas* DrawMC(TH2* hsig ,  const string hname, const  int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel, TString mass, string dirname) {

  string cname =string("c_") + hsig->GetName() + string(mass)+ "_" + string(channel);
  cout << "TH@ Draw" << endl;
  string label_plot_type = "";
  //Create Canvases
  TCanvas* canvas = new TCanvas((cname+ label_plot_type).c_str(), (cname+label_plot_type).c_str(), 800, 600);
  TCanvas* canvas_log = new TCanvas((cname+ label_plot_type+"log").c_str(), (cname+label_plot_type+"log").c_str(), 800, 600);


  std::string title=canvas->GetName();
  std::string tpdf = "/home/jalmond/WebPlots/HNSignal/histograms/"+ dirname+"/"+title+".png";
  std::string tlogpdf = "/home/jalmond/WebPlots/HNSignal/histograms/"+dirname+"/" + title+"_log.png";

  canvas_log->SetLogy();
  canvas->cd();

  hsig->Draw("COLZ");

  float mean = hsig->GetMean();
  TLatex label;
  label.SetTextSize(0.045);
  label.SetTextFont(42);
  label.SetNDC();
  label.SetTextColor(1);

  std::ostringstream buff;
  buff<< mean;
  string slabel = "Mean =" + buff.str();
  label.DrawLatex(0.7,0.8,slabel.c_str());

  canvas->Print(tpdf.c_str(), ".png");

  //// %%%%%%%%%% PRINT ON LOG
  canvas_log->cd();

  hsig->Draw("COLZ");


  canvas_log->Print(tlogpdf.c_str(), ".png");

  return canvas;

}



TCanvas* DrawMC(TH3* hsig ,  const string hname, const  int rebin, double xmin, double xmax,double ymin, double ymax,string path , string folder, bool logy, bool usedata, TString channel, TString mass, string dirname) {

  string cname =string("c_") + hsig->GetName() + string(mass)+ "_" + string(channel);

  string label_plot_type = "";
  //Create Canvases
  TCanvas* canvas = new TCanvas((cname+ label_plot_type).c_str(), (cname+label_plot_type).c_str(), 800, 600);
  TCanvas* canvas_log = new TCanvas((cname+ label_plot_type+"log").c_str(), (cname+label_plot_type+"log").c_str(), 800, 600);


  std::string title=canvas->GetName();
  std::string tpdf = "/home/jalmond/WebPlots/HNSignal/histograms/"+ dirname+"/"+title+".png";
  std::string tlogpdf = "/home/jalmond/WebPlots/HNSignal/histograms/"+dirname+"/" + title+"_log.png";

  canvas_log->SetLogy();
  canvas->cd();

  hsig->SetFillColor(kRed-4);
  hsig->SetFillStyle(3004);
  hsig->Draw("lego");

  float mean = hsig->GetMean();
  TLatex label;
  label.SetTextSize(0.045);
  label.SetTextFont(42);
  label.SetNDC();
  label.SetTextColor(1);

  std::ostringstream buff;
  buff<< mean;
  string slabel = "Mean =" + buff.str();
  label.DrawLatex(0.7,0.8,slabel.c_str());

  canvas->Print(tpdf.c_str(), ".png");

  //// %%%%%%%%%% PRINT ON LOG
  canvas_log->cd();

  hsig->Draw("lego");


  canvas_log->Print(tlogpdf.c_str(), ".png");

  return canvas;

}

