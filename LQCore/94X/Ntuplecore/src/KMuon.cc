#include "KMuon.h"

using namespace snu;

ClassImp(KMuon)

/**
 *Default constructor.
 */
KMuon::KMuon() :
  KParticle(),
  k_dz(-999.),
  k_ip2d(-999.),
  k_ip3d(-999.),
  k_sip3d(-999.),

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
  k_muon_isstandalone(0),
  k_muon_istracker(0),

  muon_maod_pt(-999.),
  k_muon_reliso03(-999.),
  k_muon_reliso04(-999.),
  k_muon_relminiiso(-999.),
  k_muon_maod_reliso03(-999.),
  k_muon_maod_reliso04(-999.),

  k_muon_trkiso(-999.),
  k_muon_ecaliso(-999.), 
  k_muon_hcaliso(-999.),
  
  k_roch_pt(-999.),
  k_roch_sf(-999.),
  k_roch_sf_up(-999.),

  k_istight(0),
  k_matched(0),
  k_is_cf(0),
  k_is_conv(0),
  k_is_fromtau(0),
  k_ismedium(0),
  k_issoft(0),
  k_ishighpt(0),
  

  k_mother_pdgid(-1),
  k_mc_pdgid(-1),
  k_mother_index(-1),
  k_mc_index(-1),
  
  k_corrected_rc(false),
  k_mctype(-999),
  k_isprompt(false),
  j_TypeBit (-1),
  j_IDBit (-1)

{
  //Reset();
}

/**
 * Copy constructor.
 */
KMuon::KMuon(const KMuon& muon) :
  KParticle(muon),
  k_dz(muon.k_dz),
  k_ip2d(muon.k_ip2d),
  k_ip3d(muon.k_ip3d),
  k_sip3d(muon.k_sip3d),

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
  k_muon_isstandalone(muon.k_muon_isstandalone),
  k_muon_istracker(muon.k_muon_istracker),

  muon_maod_pt(muon.muon_maod_pt),
  k_muon_reliso03(muon.k_muon_reliso03),
  k_muon_reliso04(muon.k_muon_reliso04),
  k_muon_relminiiso(muon.k_muon_relminiiso),
  k_muon_maod_reliso03(muon.k_muon_maod_reliso03),
  k_muon_maod_reliso04(muon.k_muon_maod_reliso04),

  k_muon_trkiso(muon.k_muon_trkiso),
  k_muon_ecaliso(muon.k_muon_ecaliso),
  k_muon_hcaliso(muon.k_muon_hcaliso),

  k_roch_pt(muon.k_roch_pt),
  k_roch_sf(muon.k_roch_sf),
  k_roch_sf_up(muon.k_roch_sf_up),
  k_istight(muon.k_istight), 
  k_matched(muon.k_matched), 
  k_is_cf(muon.k_is_cf),
  k_is_conv(muon.k_is_conv),
  k_is_fromtau(muon.k_is_fromtau),
  k_ismedium(muon.k_ismedium),
  k_issoft(muon.k_issoft),
  k_ishighpt(muon.k_ishighpt),

  k_mother_pdgid(muon.k_mother_pdgid),
  k_mc_pdgid(muon.k_mc_pdgid),
  k_mother_index(muon.k_mother_index),
  k_mc_index(muon.k_mc_index),

  k_corrected_rc(muon.k_corrected_rc),
  k_mctype(muon.k_mctype),
  k_isprompt(muon.k_isprompt),
  j_TypeBit(muon.j_TypeBit),
  j_IDBit(muon.j_IDBit)
{
}
  


KMuon::~KMuon()
{
}

void KMuon::Reset()
{
  KParticle::Reset();
  k_dz=-999.;
  k_ip2d=-999.;
  k_ip3d=-999.;
  k_sip3d=-999.;

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
  k_muon_isstandalone=false;
  k_muon_istracker=false;
  
  muon_maod_pt=0.;
  k_muon_reliso03=-999.;
  k_muon_reliso04=-999.;
  k_muon_relminiiso=-999.;
  k_muon_maod_reliso03=-999.;
  k_muon_maod_reliso04=-999.;

  k_muon_trkiso = -999;
  k_muon_ecaliso = -999;
  k_muon_hcaliso = -999;

  k_roch_pt=-999.;
  k_roch_sf=-999.;
  k_roch_sf_up=-999.;



  k_istight=false;
  k_matched=false;
  k_is_cf=false;
  k_is_conv=false;
  k_is_fromtau=false;
  k_ismedium=false;
  k_issoft=false; 
  k_ishighpt=false;

  k_mother_pdgid=-1;
  k_mc_pdgid=1;
  k_mother_index=-1;
  k_mc_index=-1;

  k_corrected_rc=false;
  k_mctype=-999;
  k_isprompt=false;
  j_TypeBit=-1;
  j_IDBit=-1;
}



KMuon& KMuon::operator= (const KMuon& p)
{
    if (this != &p) {
        KParticle::operator=(p);
	k_muon_ispf = p.IsPF();
	k_muon_isglobal = p.IsGlobal();
	k_muon_isstandalone = p.IsStandAlone();
	k_muon_istracker = p.IsTracker();
	k_dz=p.dZ();
	k_ip2d=p.IP2D();
	k_ip3d=p.IP3D();
	k_sip3d=p.SIP3D();

	k_globmuon_chi2=p.GlobalChi2();
	k_muon_valid_hits=p.validHits();
	k_muon_valid_pixhits=p.validPixHits();
	k_muon_valid_stations=p.validStations();
	k_muon_layer_with_meas=p.ActiveLayer();

	k_istight = p.IsTight();
	k_issoft = p.IsSoft();
	k_ishighpt = p.IsHighPt();
        k_ismedium = p.IsMedium();
	k_matched = p.MCMatched();
	k_is_cf=p.MCIsCF();
	k_is_conv=p.MCIsFromConversion();

	k_is_fromtau=p.MCFromTau();
	k_mother_pdgid=p.MotherPdgId();
	k_mc_pdgid=p.MCMatchedPdgId();
	k_mother_index=p.MotherTruthIndex();
	k_mc_index=p.MCTruthIndex();

	muon_maod_pt = p.MiniAODPt();

	k_muon_reliso03 = p.RelIso03();
	k_muon_reliso04 = p.RelIso04();
	k_muon_relminiiso = p.RelMiniIso();
	
	k_muon_maod_reliso03 = p.RelMiniAODIso03();
        k_muon_maod_reliso04 = p.RelMiniAODIso04();
	
	k_muon_trkiso = p.TrkIso();
	k_muon_ecaliso = p.EcalIso();
	k_muon_hcaliso = p.HcalIso();

	k_roch_pt=p.RochPt();
	k_roch_sf=p.RochSF();
	k_roch_sf_up=p.RochSFUp();
	k_muonVtx=p.muonVtx();
	k_muonVty=p.muonVty();
	k_muonVtz=p.muonVtz();
	k_corrected_rc=p.IsRochesterCorrected();
	k_mctype = p.GetType();
	k_isprompt=p.IsPromptFlag();
	j_TypeBit = p.TypeBit();
	j_IDBit= p.IDBit();
    }
    
    return *this;
}

//// SET CLASS VARIBALES



std::string KMuon::Type() const
{
    return "KMuon";
}

void KMuon::SetIsPromptFlag(bool pflag){

  k_isprompt=pflag;
}


void KMuon::SetTypeBit(unsigned int typebit){
  j_TypeBit = typebit;
}

void KMuon::SetIDBit(unsigned int idbit){
  j_IDBit = idbit;
}

void KMuon::SetType(int type){
  k_mctype= type;
}
void KMuon::SetIsFromTau(bool istau){
  k_is_fromtau=istau;
}

void KMuon::SetIsRochesterCorrected(bool rccorr){
  k_corrected_rc=rccorr;
}

void KMuon::SetIsChargeFlip(bool iscf){
  k_is_cf=iscf;
}

void KMuon::SetIsPhotonConversion(bool isconv){
  k_is_conv=isconv;
}


void KMuon::SetRochPt(double m){

  k_roch_pt=m;
}

void KMuon::SetRochSF(double m){
  
  k_roch_sf=m;
}

void KMuon::SetRochSFUp(double pt){

  k_roch_sf_up=pt;
}


void KMuon::SetMotherPdgId(int type){
  k_mother_pdgid=type;
}

void KMuon::SetMCMatchedPdgId(int type){
  k_mc_pdgid=type;
}

void KMuon::SetMotherTruthIndex(int mindex){
  k_mother_index=mindex;
}

void KMuon::SetMCTruthIndex(int tindex){
  k_mc_index=tindex;
}


//void KMuon::SetMuonVtxIndex(int ivertex){
//  i_muonVtx = ivertex;
//}


void KMuon::Setdz(double dz){

  k_dz = dz;
}

void KMuon::SetIP2D(double ip2d){

  k_ip2d = ip2d;
}

void KMuon::SetIP3D(double ip3d){

  k_ip3d = ip3d;
}

void KMuon::SetSIP3D(double sip3d){

  k_sip3d = sip3d;
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




void KMuon::SetMCMatched(bool ismatched){
  k_matched= ismatched;
}


void KMuon::SetRelIso(double cone, double iso){
  if(cone == 0.3) k_muon_reliso03= iso;
  else if(cone ==  0.4) k_muon_reliso04= iso;

}

void KMuon::SetRelMiniIso( double iso){
  k_muon_relminiiso = iso;
}


void KMuon::SetTrkIso( double iso){
  k_muon_trkiso = iso;
}

void KMuon::SetECalIso( double iso){
  k_muon_ecaliso = iso;
}

void KMuon::SetHCalIso( double iso){

  k_muon_hcaliso = iso;
}


void KMuon::SetMiniAODRelIso (double cone, double iso){
  if(cone == 0.3) k_muon_maod_reliso03= iso;
  else if(cone ==  0.4) k_muon_maod_reliso04= iso;

}
void KMuon::SetMiniAODPt(double maodpt){
  muon_maod_pt=maodpt;
}


bool KMuon::PassID(TString ID){

  if(ID=="HNWRTight") return Pass_HNWRTight();
  if(ID=="HNWRLoose") return Pass_HNWRLoose();
  if(ID=="HNWRVeto") return Pass_HNWRVeto();
  if(ID=="HNWRNoIso") return Pass_HNWRNoIso();

  //==== POG
  if(ID=="POGTight") return isPOGTight();
  if(ID=="POGHighPt") return isPOGHighPt();
  if(ID=="POGMedium") return isPOGMedium();
  if(ID=="POGLoose") return isPOGLoose();
  if(ID=="POGTightWithTightIso") return Pass_POGTightWithTightIso();
  if(ID=="POGHighPtWithLooseTrkIso") return Pass_POGHighPtWithLooseTrkIso();
  //==== Customized
  if(ID=="HNPairTight") return Pass_HNPairTight();
  if(ID=="HNPairLoose") return Pass_HNPairLoose();
  if(ID=="HNPairVeto") return Pass_HNPairVeto();
  if(ID=="TEST") return Pass_TESTID();

  exit(EXIT_FAILURE);

  return false;

}
bool KMuon::Pass_POGTightWithTightIso(){
  if(!( isPOGTight() )) return false;
  //if(!( RelIso()<0.15 ))  return false;
  return true;
}
bool KMuon::Pass_POGHighPtWithLooseTrkIso(){
  if(!( isPOGHighPt() )) return false;
  //if(!( TrkIso()/TuneP4().Pt()<0.1 )) return false;
  return true;
}

//==== HN Pair

bool KMuon::Pass_HNPairTight(){
  if(! isPOGMedium() ) return false;
  //if(! (MiniRelIso()<0.2) ) return false;
  //if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<4.) ) return false;
  return true;
}
bool KMuon::Pass_HNPairLoose(){
  if(! isPOGMedium() ) return false;
  //if(! (MiniRelIso()<0.6) ) return false;
  return true;
}
bool KMuon::Pass_HNPairVeto(){
  if(! isPOGLoose() ) return false;
  //if(! (MiniRelIso()<0.6) ) return false;
  return true;
}

//==== HN WR

bool KMuon::Pass_HNWRTight(){

  if(! isPOGHighPt() ) return false;
  //if(! ( (TrkIso()/TuneP4().Pt())<0.1 ) ) return false;

  return true;
}
bool KMuon::Pass_HNWRLoose(){

  if(! isPOGHighPt() ) return false;
  ///if(! ( (TrkIso()/TuneP4().Pt())<0.4 ) ) return false;

  return true;
}
bool KMuon::Pass_HNWRVeto(){

  if(! isPOGHighPt() ) return false;
  //if(! ( (TrkIso()/TuneP4().Pt())<0.4 ) ) return false;

  return true;
}

bool KMuon::Pass_HNWRNoIso(){

  if(! isPOGLoose() ) return false;

  return true;

}

//==== TEST ID

bool KMuon::Pass_TESTID(){
  if(! isPOGLoose() ) return false;
  //if(! (MiniRelIso()<0.6) ) return false;
  //if(! (fabs(dXY())<0.05 && fabs(dZ())<0.1 && fabs(IP3D()/IP3Derr())<4.) ) return false;
  return true;
}
