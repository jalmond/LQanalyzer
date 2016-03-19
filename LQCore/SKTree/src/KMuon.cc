#include "KMuon.h"

using namespace snu;

ClassImp(KMuon)

/**
 *Default constructor.
 */
KMuon::KMuon() :
  KParticle(),
  k_dz(-999.),
  k_dxy(-999.),
  k_globmuon_chi2(-999.),
  k_muonVtx(-999.),
  k_muonVty(-999.),
  k_muonVtz(-999.),
  
  k_muon_valid_hits(-999), 
  k_muon_valid_pixhits(-999),
  k_muon_valid_stations(-999),
  k_muon_layer_with_meas(-999),
  k_muon_ispf(0),
  k_muon_isglobal(0),
  k_muon_istracker(0),

  muon_pt_up(-999.), 
  muon_pt_down(-999.),
  k_muon_reliso03(-999.),
  k_muon_reliso04(-999.),
  
  k_isloose(0),
  k_istight(0),
  k_matched(0),
  k_is_cf(0),
  k_is_fromtau(0),

  k_ismedium(0),
  k_issoft(0),
  
  k_trig_match("")

{
  //Reset();
}

/**
 * Copy constructor.
 */
KMuon::KMuon(const KMuon& muon) :
  KParticle(muon),
  k_dz(muon.k_dz),
  k_dxy(muon.k_dxy),
  k_globmuon_chi2(muon.k_globmuon_chi2),
  k_muonVtx(muon.k_muonVtx),
  k_muonVty(muon.k_muonVty),
  k_muonVtz(muon.k_muonVtz),

  k_muon_valid_hits(muon.k_muon_valid_hits),
  k_muon_valid_pixhits(muon.k_muon_valid_pixhits),
  k_muon_valid_stations(muon.k_muon_valid_stations),
  k_muon_layer_with_meas(muon.k_muon_layer_with_meas),

  k_muon_ispf(muon.k_muon_ispf),
  k_muon_isglobal(muon.k_muon_isglobal),
  k_muon_istracker(muon.k_muon_istracker),

  muon_pt_up(muon.muon_pt_up),
  muon_pt_down(muon.muon_pt_down),
  k_muon_reliso03(muon.k_muon_reliso03),
  k_muon_reliso04(muon.k_muon_reliso04),


  k_isloose(muon.k_isloose),
  k_istight(muon.k_istight), 
  k_matched(muon.k_matched), 
  k_is_cf(muon.k_is_cf),
  k_is_fromtau(muon.k_is_fromtau),
  
  k_ismedium(muon.k_ismedium),
  k_issoft(muon.k_issoft),
  k_trig_match(muon.k_trig_match)
{
}
  


KMuon::~KMuon()
{
}

void KMuon::Reset()
{
  KParticle::Reset();
  k_dz=-999.;
  k_dxy=-999.;
  k_globmuon_chi2=-999;
  k_muonVtx=-999.;
  k_muonVty=-999.;
  k_muonVtz=-999.;
  
  k_muon_valid_hits=-999;
  k_muon_valid_pixhits=-999;
  k_muon_valid_stations=-999;
  k_muon_layer_with_meas=-999;

  
  k_muon_ispf=false;
  k_muon_isglobal=false;
  k_muon_istracker=false;
  
  muon_pt_up=0.;
  muon_pt_down=0.;
  k_muon_reliso03=-999.;
  k_muon_reliso04=-999.;

  k_isloose=false;
  k_istight=false;
  k_matched=false;
  k_is_cf=false;
  k_is_fromtau=false;

  k_ismedium=false;
  k_issoft=false;

  k_trig_match= "";
}



KMuon& KMuon::operator= (const KMuon& p)
{
    if (this != &p) {
        KParticle::operator=(p);
	k_muon_ispf = p.IsPF();
	k_muon_isglobal = p.IsGlobal();
	k_muon_istracker = p.IsTracker();
	k_dz=p.dZ();
	k_dxy=p.dXY();
	k_globmuon_chi2=p.GlobalChi2();
	k_muon_valid_hits=p.validHits();
	k_muon_valid_pixhits=p.validPixHits();
	k_muon_valid_stations=p.validStations();
	k_muon_layer_with_meas=p.ActiveLayer();
	//i_muonVtx = p.MuonVertexIndex();       
	muon_pt_up = p.PtShiftedUp();
	muon_pt_down = p.PtShiftedDown();
	k_isloose = p.IsLoose();
	k_istight = p.IsTight();
	k_issoft = p.IsSoft();
        k_ismedium = p.IsMedium();
	k_matched = p.MCMatched();
	k_is_cf=p.MCIsCF();
	k_is_fromtau=p.MCFromTau();

	k_muon_reliso03 = p.RelIso03();
	k_muon_reliso04 = p.RelIso04();
	k_muonVtx=p.muonVtx();
	k_muonVty=p.muonVty();
	k_muonVtz=p.muonVtz();
	k_trig_match= p.TrigMatch();
    }
    
    return *this;
}

//// SET CLASS VARIBALES



std::string KMuon::Type() const
{
    return "KMuon";
}

bool KMuon::TriggerMatched(TString path){
  TString trig = k_trig_match;
  if(trig.Contains(path)) return true;
  return false;
}

void KMuon::SetIsFromTau(bool istau){
  k_is_fromtau=istau;
}


void KMuon::SetIsChargeFlip(bool iscf){
  k_is_cf=iscf;
}


float KMuon::ScaleFactor(const std::string& name, int sign) const {
  //need to fill errors.
  
  //# Muon SF reference https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonReferenceEffsRun2
  //## Retrieve data from the cmsdoc web page:
  //##   https://cmsdoc.cern.ch/cms/Physics/muon/ReferenceEfficiencies/Run2015/25ns/MuonID_Z_RunCD_Reco76X_Feb15.json
  //##   https://cmsdoc.cern.ch/cms/Physics/muon/ReferenceEfficiencies/Run2015/25ns/MuonIso_Z_RunCD_Reco76X_Feb15.json

  float eta = fabs(this->Eta());
  
  float fsign = 1.;
  if(sign == 0) fsign =0.;
  if(sign == -1) fsign =-1.;
  if (name == "POG_TightID"){
    ///    # Values of "MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_spliteta_bin1 + MC_NUM_TightRelIso_DEN_TightID_PAR_pt_spliteta_bin1"

    if (this->Pt()>20. && this->Pt() <= 25.){
      if      ( eta <=  0.900)    return (0.97535*1.0036)  + fsign*(0.02);
      else if ( eta <=  1.200)    return (0.97775*1.0038)  + fsign*(0.06);
      else if ( eta <=  2.100)    return (0.99295*0.9998)  + fsign*(0.06);
      else if ( eta <=  2.400)    return (0.97845*1.0062)  + fsign*(0.06);
      else return 1.;

    }
    else if (this->Pt()>25. && this->Pt() <= 30.){
      if      ( eta <=  0.900)    return (0.9828099*0.9977)  + fsign*(0.02);
      else if ( eta <=  1.200)    return (0.9761207*0.99956)  + fsign*(0.06);
      else if ( eta <=  2.100)    return (0.989996*1.0020)  + fsign*(0.06);
      else if ( eta <=  2.400)    return (0.976407*0.99873)  + fsign*(0.06);
      else return 1.;

    }
    else if (this->Pt()>30. && this->Pt() <= 40.){
      if      ( eta <=  0.900)    return (0.986640*1.00087)  + fsign*(0.02);
      else if ( eta <=  1.200)    return (0.98037*1.00118)  + fsign*(0.06);
      else if ( eta <=  2.100)    return (0.99230*1.002168)  + fsign*(0.06);
      else if ( eta <=  2.400)    return (0.9783080*0.99957)  + fsign*(0.06);
      else return 1.;

      
    }
    else if (this->Pt()>40. && this->Pt() <= 50.){
      if      ( eta <=  0.900)    return (0.987302*0.99954)  + fsign*(0.02);
      else if ( eta <=  1.200)    return (0.9801*0.9994)  + fsign*(0.06);
      else if ( eta <=  2.100)    return (0.99125*1.000058)  + fsign*(0.06);
      else if ( eta <=  2.400)    return (0.9775*0.999581)  + fsign*(0.06);
      else return 1.;


    }
    else if (this->Pt()>50. && this->Pt() <= 60.){
      if      ( eta <=  0.900)    return (0.98227*1.00027)  + fsign*(0.02);
      else if ( eta <=  1.200)    return (0.97658*0.999814)  + fsign*(0.06);
      else if ( eta <=  2.100)    return (0.989061*1.000066)  + fsign*(0.06);
      else if ( eta <=  2.400)    return (0.97276*1.000374)  + fsign*(0.06);
      else return 1.;


    }
    else if (this->Pt()>60. && this->Pt() <= 120.){
      if      ( eta <=  0.900)    return (0.98566*0.999541)  + fsign*(0.02);
      else if ( eta <=  1.200)    return (0.9777*1.00047)  + fsign*(0.06);
      else if ( eta <=  2.100)    return (0.9929*1.000415)  + fsign*(0.06);
      else if ( eta <=  2.400)    return (0.9784*1.001068)  + fsign*(0.06);
      else return 1.;

    }

  }
  return 1.; 
}


//void KMuon::SetMuonVtxIndex(int ivertex){
//  i_muonVtx = ivertex;
//}


void KMuon::Setdz(double dz){

  k_dz = dz;
}

void KMuon::Setdxy(double dxy){

  k_dxy = dxy;
}


void KMuon::SetTrackVx(double vtx){
  
  k_muonVtx = vtx;
}

void KMuon::SetTrackVy(double vty){

  k_muonVty = vty;
}

void KMuon::SetTrackVz(double vtz){

  k_muonVtz = vtz;
}

void KMuon::SetGlobalchi2(double glob_chi2){

  k_globmuon_chi2 = glob_chi2;
}

void KMuon::SetValidHits(int validhits){

  k_muon_valid_hits = validhits;
}

void KMuon::SetPixelValidHits(int valid_pix_hits){

  k_muon_valid_pixhits = valid_pix_hits;
}

void KMuon::SetValidStations(int validstations){

  k_muon_valid_stations = validstations;
}

void KMuon::SetLayersWithMeasurement(int layer_with_meas){

  k_muon_layer_with_meas = layer_with_meas;
}



void KMuon::SetISPF(bool ispf){

  k_muon_ispf = ispf;
}

void KMuon::SetIsGlobal(bool isglobal){

  k_muon_isglobal =isglobal;
}

void KMuon::SetIsTracker(bool istracker){

  k_muon_istracker =istracker;
}


void KMuon::SetShiftedEUp(double pt_up){
  muon_pt_up= pt_up;
}

void KMuon::SetShiftedEDown(double pt_down){
  muon_pt_down= pt_down;
}


void KMuon::SetIsLoose(bool isloose){
  k_isloose= isloose;
}
void KMuon::SetIsTight(bool istight){
  k_istight= istight;
}

void KMuon::SetIsMedium(bool ismedium){
  k_ismedium= ismedium;
}
void KMuon::SetIsSoft(bool issoft){
  k_issoft= issoft;
}


void KMuon::SetMCMatched(bool ismatched){
  k_matched= ismatched;
}


void KMuon::SetRelIso(double cone, double iso){
  if(cone == 0.3) k_muon_reliso03= iso;
  else if(cone ==  0.4) k_muon_reliso04= iso;

}


void KMuon::SetTrigMatch(TString match){
  k_trig_match= match;
}
