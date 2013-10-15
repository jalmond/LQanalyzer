#include <vector>

#include "SinglePlot.h"
#include "Single2dPlot.h"

void loadCFO(std::vector<TString>& filename, std::vector<TString>& legendname, std::vector<TString>& plotlabel, std::vector<int>& color, std::vector<int>& linecol, std::vector<std::string>& type, std::vector<SinglePlot>& hist1d, std::vector<Single2dPlot>& hist2d, std::vector<double>& weight, std::vector<bool>& legend) {

//  const double luminosity = 36.09;
  const double luminosity = 80.582679;

  const TString directory = "/Volumes/Documents/Analyses/Majorana_Neutrino/files2012/80/";
  std::vector<TString> classe;
  enum logbool {      nolog,         log };
  enum normbool {     nonorm,        norm };
  enum normfirstbool {nonormToFirst, normToFirst };
  enum stackbool {    nostack,       stack };
  enum overflowbool { nooverflow,    overflow };

  Bool_t FR=false; 
  Bool_t ttbar=false; Bool_t Z_jets=false; Bool_t W_jets=false; Bool_t QCD_mu=false; 
  Bool_t data=true;
  Bool_t signal=true;
  Bool_t Wgamma=false; Bool_t WZ=true; Bool_t ZZ=true;
  Bool_t WmWm=true; Bool_t WpWp=true; Bool_t dpWW=false; Bool_t WWW=true;
  Bool_t ttW=true; Bool_t ttZ=true; Bool_t others=false;
  Bool_t diboson=false;
  Bool_t NR50=false;  Bool_t NR70=false; Bool_t NR90=false; Bool_t NR100=false; Bool_t NR125=false; Bool_t NR150=false; Bool_t NR175=false; Bool_t NR200=false; Bool_t NR300=false; Bool_t NR500=false; Bool_t WR=false;
  
  if(data && signal) {
    
    hist1d.push_back( SinglePlot("h_bTag_", 1,  nolog, nonorm, nonormToFirst, 2.0, nooverflow, stack, "", "b-tag discriminant","Events") );
    hist1d.push_back( SinglePlot("h_dijetsmass_", 1,  nolog, nonorm, nonormToFirst, 300.0, nooverflow, stack, "", "jj invariant mass (GeV)", "Events/10 GeV" ) );
    hist1d.push_back( SinglePlot("h_llmass_", 2,  nolog, nonorm, nonormToFirst, 500.0, nooverflow, stack, "", "#mu#mu invariant mass (GeV)","Events/20 GeV") );
    hist1d.push_back( SinglePlot("h_l1jjmass_", 1,  nolog, nonorm, nonormToFirst, 700.0, nooverflow, stack, "", "#mu_{1}jj invariant mass (GeV)","Events/10 GeV") );
    hist1d.push_back( SinglePlot("h_l2jjmass_", 1,  nolog, nonorm, nonormToFirst, 700.0, nooverflow, stack, "", "#mu_{2}jj invariant mass (GeV)","Events/10 GeV") );
    hist1d.push_back( SinglePlot("h_lljjmass_", 2,  nolog, nonorm, nonormToFirst, 1200.0, nooverflow, stack, "", "#mu#mujj system invarian mass (GeV)","Events/20 GeV") );
    hist1d.push_back( SinglePlot("h_leadingMuonPt_", 2,  nolog, nonorm, nonormToFirst, 1.0, nooverflow, stack, "", "muon p_{T} (GeV)","Events/10 GeV") );
    hist1d.push_back( SinglePlot("h_secondMuonPt_", 1,  nolog, nonorm, nonormToFirst, 200.0, nooverflow, stack, "", "second #mu p_{T} (GeV)","Events/5 GeV") );
    hist1d.push_back( SinglePlot("h_leadingJetPt_", 2,  nolog, nonorm, nonormToFirst, 1.0, nooverflow, stack, "", "leading jet p_{T} (GeV)","Events/10 GeV") );
    hist1d.push_back( SinglePlot("h_secondJetPt_", 1,  nolog, nonorm, nonormToFirst, 200.0, nooverflow, stack, "", "second jet p_{T} (GeV)","Events/5 GeV") );
    hist1d.push_back( SinglePlot("h_leadingMuonIso_", 1,  log, nonorm, nonormToFirst, 1.0, overflow, stack, "leading #mu RelIso", "","Events") );
    hist1d.push_back( SinglePlot("h_secondMuonIso_", 1,  log, nonorm, nonormToFirst, 1.0, overflow, stack, "second #mu RelIso", "","Events") );
    hist1d.push_back( SinglePlot("h_Njets_", 1,  nolog, nonorm, nonormToFirst, 1.0, nooverflow, stack, "", "number of jets","Events") );
    hist1d.push_back( SinglePlot("h_MET_", 1,  nolog, nonorm, nonormToFirst, 300.0, nooverflow, stack, "", "#slash{E}_{T} (GeV)","Events/10 GeV") );  
  
    //hist1d.push_back( SinglePlot("h_nvtx_rw", 1,  nolog, nonorm, nonormToFirst, 30.0, nooverflow, nostack, "", "n Vertexes","Events") );
  }

if (signal && WWW) {
   filename.push_back(directory+"WWW_80.root");
   legendname.push_back("WWW");
   plotlabel.push_back("WWW");
   color.push_back(kSpring+9); linecol.push_back(kSpring+9);
   legend.push_back(true);
   type.push_back("mc");
   weight.push_back(1);
 }

if (signal && ttZ) {
   filename.push_back(directory+"ttZ_80.root");
   legendname.push_back("t#bar{t}Z");
   plotlabel.push_back("t#bar{t}Z");
   color.push_back(kOrange); linecol.push_back(kOrange);
   legend.push_back(true);
   type.push_back("mc");
   weight.push_back(1);
 }

if (signal && ttW) {
   filename.push_back(directory+"ttW_80.root");
   legendname.push_back("t#bar{t}W");
   plotlabel.push_back("t#bar{t}W");
   color.push_back(kOrange-9); linecol.push_back(kOrange-9);
   legend.push_back(true);
   type.push_back("mc");
   weight.push_back(1);
 }

if (signal && dpWW) {
   filename.push_back(directory+"WW_dp_80.root");
   legendname.push_back("dpWW");
   plotlabel.push_back("dpWW");
   color.push_back(kGreen+3); linecol.push_back(kGreen+3);
   legend.push_back(true);
   type.push_back("mc");
   weight.push_back(1);
 }

 if (signal && WmWm) {
    filename.push_back(directory+"WmWm_80.root");
    legendname.push_back("W^{-}W^{-}");
    plotlabel.push_back("W^{-}W^{-}");
    color.push_back(kGreen-9); linecol.push_back(kGreen-9);
    legend.push_back(true);
    type.push_back("mc");
    weight.push_back(1);
 }

 if (signal && WpWp) {
    filename.push_back(directory+"WpWp_80.root");
    legendname.push_back("W^{+}W^{+}");
    plotlabel.push_back("W^{+}W^{+}");
    color.push_back(kGreen-1); linecol.push_back(kGreen-1);
    legend.push_back(true);
    type.push_back("mc");
    weight.push_back(1);
 }

 if (signal && ZZ) {
    filename.push_back(directory+"ZZ_inclusive_80.root");
    legendname.push_back("ZZ");
    plotlabel.push_back("ZZ");
    color.push_back(kYellow); linecol.push_back(kYellow);
    legend.push_back(true);
    type.push_back("mc");
    weight.push_back(1);
 }

 if (signal && WZ) {
    filename.push_back(directory+"WZ_inclusive_80.root");
    legendname.push_back("WZ");
    plotlabel.push_back("WZ");
    color.push_back(kSpring+10); linecol.push_back(kSpring+10);
    legend.push_back(true);
    type.push_back("mc");
    weight.push_back(1);
 }

 if (signal && diboson) {
    filename.push_back(directory+"SM-prompt_METmore50pp_14.80.root");
    legendname.push_back("Prompt-Prompt Background");
    plotlabel.push_back("Prompt-Prompt Background");
    color.push_back(kGreen); linecol.push_back(kGreen);
    legend.push_back(true);
    type.push_back("mc");
    weight.push_back(1);
 }

 if (signal && NR50) {
    filename.push_back(directory+"Majorana50_80.root");
    legendname.push_back("m_{N} = 50 GeV, |V_{#muN}|^{2} = 0.00005");
    plotlabel.push_back("m_{N} = 50 GeV, |V_{#muN}|^{2} = 0.00005");
    color.push_back(kMagenta+3); linecol.push_back(kMagenta+3);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.00005);
 }
    
 if (signal && NR70) {
    filename.push_back(directory+"Majorana70_80.root");
    legendname.push_back("m_{N} = 70 GeV, |V_{#muN}|^{2} = 0.0005");
    plotlabel.push_back("m_{N} = 70 GeV, |V_{#muN}|^{2} = 0.0005");
    color.push_back(kMagenta-7); linecol.push_back(kMagenta-7);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.0005);
 }

 if (signal && NR90) {
    filename.push_back(directory+"Majorana90_80.root");
    legendname.push_back("m_{N} = 90 GeV,  |V_{#muN}|^{2} = 0.005");
    plotlabel.push_back("m_{N} = 90 GeV,  |V_{#muN}|^{2} = 0.005");
    color.push_back(kMagenta); linecol.push_back(kMagenta);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.005);
 }

 if (signal && NR100) {
    filename.push_back(directory+"Majorana100_80.root");
    legendname.push_back("m_{N} = 100 GeV,  |V_{#muN}|^{2} = 0.002");
    plotlabel.push_back("m_{N} = 100 GeV,  |V_{#muN}|^{2} = 0.002");
    color.push_back(kMagenta); linecol.push_back(kMagenta);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.002);
 }

 if (signal && NR125) {
    filename.push_back(directory+"Majorana125_80.root");
    legendname.push_back("m_{N} = 125 GeV, |V_{#muN}|^{2} = 0.0025");
    plotlabel.push_back("m_{N} = 125 GeV, |V_{#muN}|^{2} = 0.0025");
    color.push_back(kPink); linecol.push_back(kPink);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.0025);
 }

 if (signal && NR150) {
    filename.push_back(directory+"Majorana150_80.root");
    legendname.push_back("m_{N} = 150 GeV, |V_{#muN}|^{2} = 0.005");
    plotlabel.push_back("m_{N} = 150 GeV, |V_{#muN}|^{2} = 0.005");
    color.push_back(kPink+2); linecol.push_back(kPink+2);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.005);
 }

 if (signal && NR175) {
    filename.push_back(directory+"Majorana175_80.root");
    legendname.push_back("m_{N} = 175 GeV, |V_{#muN}|^{2} = 0.005");
    plotlabel.push_back("m_{N} = 175 GeV, |V_{#muN}|^{2} = 0.005");
    color.push_back(kPink-2); linecol.push_back(kPink-2);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.005);
 } 

 if (signal && NR200) {
    filename.push_back(directory+"Majorana200_80.root");
    legendname.push_back("m_{N} = 200 GeV, |V_{#muN}|^{2} = 0.01");
    plotlabel.push_back("m_{N} = 200 GeV, |V_{#muN}|^{2} = 0.01");
    color.push_back(kPink-2); linecol.push_back(kPink-2);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.01);
 }

 if (signal && NR300) {
    filename.push_back(directory+"Majorana300_80.root");
    legendname.push_back("m_{N} = 300 GeV, |V_{#muN}|^{2} = 0.05");
    plotlabel.push_back("m_{N} = 300 GeV, |V_{#muN}|^{2} = 0.05");
    color.push_back(kPink-2); linecol.push_back(kPink-2);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.05);
 }

 if (signal && NR500) {
    filename.push_back(directory+"Majorana500_80.root");
    legendname.push_back("m_{N} = 500 GeV, |V_{#muN}|^{2} = 0.5");
    plotlabel.push_back("m_{N} = 500 GeV, |V_{#muN}|^{2} = 0.5");
    color.push_back(kMagenta-10); linecol.push_back(kMagenta-10);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.5);
 }

 if (signal && WR) {
    filename.push_back(directory+"WR700_MNu350_80.root");
    legendname.push_back("m_{W_{R}} = 700 GeV, #sigma/100");
    plotlabel.push_back("m_{W_{R}} = 700 GeV, #sigma/100");
    color.push_back(kBlue+3); linecol.push_back(kBlue+3);
    legend.push_back(true);
    type.push_back("signal");
    weight.push_back(0.01);
 }

 if (signal && data) {
    filename.push_back(directory+"DoubleMu_60_80.root");
    legendname.push_back("Data");
    plotlabel.push_back("Data");
    color.push_back(kBlack); linecol.push_back(kBlack);
    legend.push_back(true);
    type.push_back("data");
    weight.push_back(1);
  }

 if (signal && data && false) {
    filename.push_back(directory+"vuoto.root");
    legendname.push_back("Fake Muon Background");
    plotlabel.push_back("Fake Muon Background");
    color.push_back(kAzure+10); linecol.push_back(kAzure+10);
    legend.push_back(true);
    type.push_back("mc");
    weight.push_back(1);
 }


  /////////////////////
  //   Formatting    //
  /////////////////////

  // SinglePlot(std::string name, unsigned int rebin, bool log, bool normalize, bool normToFirst, double scaleXmax,
  //            bool overflowbin, bool stacked, TString title)

  // Single2dPlot(std::string name, std::string title, std::string drawOption, unsigned int rebinX, unsigned int rebinY)

} 

