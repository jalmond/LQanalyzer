#include "KMuon.h"

using namespace snu;

ClassImp(KMuon)

/**
 *Default constructor.
 */
KMuon::KMuon() :
  KParticle(),
  k_dz(0.),
  k_dxy(0.),
  k_globmuon_chi2(0.),
  k_muonVtx(0.),
  k_muonVty(0.),
  k_muonVtz(0.),
  
  k_muon_valid_hits(-999), 
  k_muon_valid_pixhits(-999),
  k_muon_valid_stations(-999),
  k_muon_layer_with_meas(-999),
  k_muon_ispf(-999),
  k_muon_isglobal(-999),
  k_muon_istracker(-999),

  muon_pt_up(0.), 
  muon_pt_down(0.),
  k_muon_reliso03(-999.),
  k_muon_reliso04(-999.),
  
  k_isloose(0),
  k_istight(0),
  k_matched(0),
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
  k_dz=0.;
  k_dxy=0.;
  k_globmuon_chi2=0;
  k_muonVtx=0.;
  k_muonVty=0.;
  k_muonVtz=0.;
  
  k_muon_valid_hits=0;
  k_muon_valid_pixhits=0;
  k_muon_valid_stations=0;
  k_muon_layer_with_meas=0;

  
  k_muon_ispf=0;
  k_muon_isglobal=0;
  k_muon_istracker=0;
  
  muon_pt_up=0.;
  muon_pt_down=0.;
  k_muon_reliso03=-999.;
  k_muon_reliso04=-999.;

  k_isloose=0;
  k_istight=0;
  k_matched=0;
  k_ismedium=0;
  k_issoft=0;
  k_matched=0;

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


void KMuon::SetRelIso03(double iso03){
  k_muon_reliso03= iso03;
}


void KMuon::SetRelIso04(double iso04){
  k_muon_reliso04= iso04;
}


void KMuon::SetTrigMatch(TString match){
  k_trig_match= match;
}
