#include "KMuon.h"

using namespace snu;

ClassImp(KMuon)

/**
 *Default constructor.
 */
KMuon::KMuon() :
KParticle(),k_pterror(0.),k_etaerror(0.),k_isor03ch(0.),k_isor03n(0.),k_isor03ph(0.),k_isor04ch(0.),k_isor04n(0.),k_isor04ph(0.),k_isoEcalveto(0.),k_isoHcalveto(0.),k_MuonPFIsoR03PU(0.),k_MuonPFIsoR04PU(0.),k_muonVtx(0.),k_muonVty(0.),k_muonVtz(0.),k_muongen_pt(0.),k_muongen_eta(0.),k_muongen_phi(0.),k_dz(0.),k_dxy(0.),k_d0(0.),k_d0err(0.),k_globmuon_chi2(0.),k_dxy_pat(0.),k_dxyerr_pat(0.),k_vtxdistxy(0.),k_muon_valid_hits(-999), k_muon_valid_pixhits(-999), k_muon_valid_stations(-999), k_muon_layer_with_meas(-999),k_muon_ispf(-999), k_muon_isglobal(-999),k_muon_istracker(-999), i_muonVtx(-999),muon_ck_pt(0.),muon_ck_eta(0.), muon_ck_phi(0.), muon_ck_chi2(0.), muon_ck_trkd0(0.),muon_ck_trkdz(0.), muon_ck_charge(0.), k_dimuon_trig_match(-999.), k_muon_trig_match(-999.),k_isomuon_trig_match(-999.), k_muon_trig_match5(-999.),k_muon_trig_match8(-999.),k_muon_trig_match12(-999.),k_muon_trig_match17(-999.),k_muon_trig_match24(-999.),k_emu_trig_match8(-999.),k_emu_trig_match17(-999.), muon_ms_pt(0.), muon_ms_eta(0.), muon_ms_phi(0.), muon_ms_charge(0), muon_ms_e(0.),muon_id_pt(0.), muon_id_eta(0.), muon_id_phi(0.), muon_id_charge(0), muon_pt_up(0.), muon_pt_down(0.)
 {
  //Reset();
}

/**
 * Copy constructor.
 */
KMuon::KMuon(const KMuon& muon) :
  KParticle(muon),
  k_pterror(muon.k_pterror),
  k_etaerror(muon.k_etaerror),
  k_isor03ch(muon.k_isor03ch),
  k_isor03n(muon.k_isor03n),
  k_isor03ph(muon.k_isor03ph),
  k_isor04ch(muon.k_isor04ch),
  k_isor04n(muon.k_isor04n),
  k_isor04ph(muon.k_isor04ph),
  k_isoEcalveto(muon.k_isoEcalveto), 
  k_isoHcalveto(muon.k_isoHcalveto), 
  k_MuonPFIsoR03PU(muon.k_MuonPFIsoR03PU),
  k_MuonPFIsoR04PU(muon.k_MuonPFIsoR04PU),
  k_muonVtx(muon.k_muonVtx), 
  k_muonVty(muon.k_muonVty), 
  k_muonVtz(muon.k_muonVtz), 
  k_muongen_pt(muon.k_muongen_pt),
  k_muongen_eta(muon.k_muongen_eta),
  k_muongen_phi(muon.k_muongen_phi),
  k_dz(muon.k_dz),
  k_dxy(muon.k_dxy),
  k_d0(muon.k_d0),
  k_d0err(muon.k_d0err),
  k_globmuon_chi2(muon.k_globmuon_chi2),
  k_dxy_pat(muon.k_dxy_pat),
  k_dxyerr_pat(muon.k_dxyerr_pat),
  k_vtxdistxy(muon.k_vtxdistxy),
  k_muon_valid_hits(muon.k_muon_valid_hits),
  k_muon_valid_pixhits(muon.k_muon_valid_pixhits),
  k_muon_valid_stations(muon.k_muon_valid_stations),
  k_muon_layer_with_meas(muon.k_muon_layer_with_meas),
  k_muon_ispf(muon.k_muon_ispf),
  k_muon_isglobal(muon.k_muon_isglobal),
  k_muon_istracker(muon.k_muon_istracker),
  i_muonVtx(muon.i_muonVtx),
  muon_ck_pt(muon.muon_ck_pt),
  muon_ck_eta(muon.muon_ck_eta), 
  muon_ck_phi(muon.muon_ck_phi), 
  muon_ck_chi2(muon.muon_ck_chi2),
  muon_ck_trkd0(muon.muon_ck_trkd0),
  muon_ck_trkdz(muon.muon_ck_trkdz),
  muon_ck_charge(muon.muon_ck_charge),
  k_dimuon_trig_match(muon.k_dimuon_trig_match),
  k_muon_trig_match(muon.k_muon_trig_match),
  k_isomuon_trig_match(muon.k_isomuon_trig_match),
  k_muon_trig_match5(muon.k_muon_trig_match5),
  k_muon_trig_match8(muon.k_muon_trig_match8),
  k_muon_trig_match12(muon.k_muon_trig_match12),
  k_muon_trig_match17(muon.k_muon_trig_match17),
  k_muon_trig_match24(muon.k_muon_trig_match24),
  k_emu_trig_match8(muon.k_emu_trig_match8),
  k_emu_trig_match17(muon.k_emu_trig_match17),
  muon_ms_pt(muon.muon_ms_pt),
  muon_ms_eta(muon.muon_ms_eta), 
  muon_ms_phi(muon.muon_ms_phi), 
  muon_ms_charge(muon.muon_ms_charge),
  muon_ms_e(muon.muon_ms_e),
  muon_id_pt(muon.muon_id_pt),
  muon_id_eta(muon.muon_id_eta),
  muon_id_phi(muon.muon_id_phi),
  muon_id_charge(muon.muon_id_charge),
  muon_pt_up(muon.muon_pt_up),
  muon_pt_down(muon.muon_pt_down)
{
}


KMuon::~KMuon()
{
}

void KMuon::Reset()
{
  KParticle::Reset();
  k_isor03ch=0.;
  k_isor03n=0.;
  k_isor03ph=0.;
  k_isor04ch=0.;
  k_isor04n=0.;
  k_isor04ph=0.;
  k_muon_ispf=0;
  k_muon_isglobal=0;
  k_muon_istracker=0;
  muon_ck_pt=0.;
  muon_ck_eta=0.;
  muon_ck_phi=0.;
  muon_ck_chi2=0.;
  muon_ck_trkd0=0.;
  muon_ck_trkdz=0.;
  muon_ck_charge=0.;
  k_globmuon_chi2=0;
  k_pterror=0;
  k_etaerror=0;
  k_isoEcalveto=0.; 
  k_isoHcalveto=0.; 
  k_MuonPFIsoR03PU=0.;
  k_MuonPFIsoR04PU=0.;
  k_muonVtx=0.;
  k_muonVty=0.;
  k_muonVtz=0.;
  k_dz=0.;
  k_dxy=0.;
  k_dxy_pat=0.;
  k_dxyerr_pat=0.;
  k_d0=0;
  k_d0err=0;
  k_muon_valid_hits=0;
  k_muon_valid_pixhits=0;
  k_muon_valid_stations=0;
  k_muon_layer_with_meas=0;
  k_muongen_pt=0.;
  k_muongen_eta=0.;
  k_muongen_phi=0.;
  i_muonVtx = 0;
  k_vtxdistxy = 0.;
  k_dimuon_trig_match = -999.;
  k_muon_trig_match = -999.;
  k_muon_trig_match5 = -999.;
  k_muon_trig_match8 = -999.;
  k_muon_trig_match12 = -999.;
  k_muon_trig_match17 = -999.;
  k_muon_trig_match24 = -999.;
  k_isomuon_trig_match = -999.;
  k_emu_trig_match8 = -999.;
  k_emu_trig_match17 = -999.;
  muon_ms_pt = 0.;
  muon_ms_eta = 0.;
  muon_ms_phi= 0.;
  muon_ms_charge= 0.;
  muon_ms_e= 0.;
  muon_id_pt= 0.;
  muon_id_eta= 0.;
  muon_id_phi= 0.;
  muon_id_charge= 0.;
  muon_pt_up=0.;
  muon_pt_down=0.;
}



KMuon& KMuon::operator= (const KMuon& p)
{
    if (this != &p) {
        KParticle::operator=(p);
	k_isor03ch = p.SumIsoCHDR03();
	k_isor04ch = p.SumIsoCHDR04();
	k_muon_ispf = p.IsPF();
	k_muon_isglobal = p.IsGlobal();
	k_muon_istracker = p.IsTracker();
	muon_ck_pt = p.MuonCocktailPt();
	muon_ck_eta=p.MuonCocktailEta();
	muon_ck_phi=p.MuonCocktailPhi();
	muon_ck_chi2=p.MuonCocktailGlobalChi2(); 
	muon_ck_trkd0=p.MuonCocktailTrkD0();
	muon_ck_trkdz=p.MuonCocktailTrkDz();
	muon_ck_charge=p.MuonCocktailCharge();
	k_isor03n=p.SumIsoNHDR03();
	k_isor03ph=p.SumIsoPHDR03();
	k_isor04n=p.SumIsoNHDR04();
	k_isor04ph=p.SumIsoPHDR04();
	k_pterror=p.PtError();
	k_etaerror=p.EtaError();
	k_isoEcalveto=p.IsoEcalVeto(); 
	k_isoHcalveto=p.IsoHcalVeto(); 
	k_MuonPFIsoR03PU=p.SumPUIsoR03();
	k_MuonPFIsoR04PU=p.SumPUIsoR04();
	k_muonVtx=p.muonVtx();
	k_muonVty=p.muonVty();
	k_muonVtz=p.muonVtz();
	k_dz=p.dZ();
	k_dxy=p.dXY();
	k_dxy_pat=p.dXYPat();
	k_dxyerr_pat=p.dXYErrPat();
	k_d0=p.D0();
	k_d0err=p.D0Err();
	k_globmuon_chi2=p.GlobalChi2();
	k_muon_valid_hits=p.validHits();
	k_muon_valid_pixhits=p.validPixHits();
	k_muon_valid_stations=p.validStations();
	k_muon_layer_with_meas=p.ActiveLayer();
	k_muongen_pt=p.MuonMatchedGenParticlePt();
	k_muongen_eta=p.MuonMatchedGenParticleEta();
	k_muongen_phi=p.MuonMatchedGenParticlePhi();
	i_muonVtx = p.MuonVertexIndex();       
	k_vtxdistxy= p.VertexDistXY();
	k_dimuon_trig_match  = p.MatchedDiMuonTrigger();
	k_muon_trig_match  = p.MatchedSingleMuonTrigger();
	k_muon_trig_match5  = p.MatchedSingleMuonTrigger5();
	k_muon_trig_match8  = p.MatchedSingleMuonTrigger8();
	k_muon_trig_match12  = p.MatchedSingleMuonTrigger12();
	k_muon_trig_match17  = p.MatchedSingleMuonTrigger17();
	k_muon_trig_match24  = p.MatchedSingleMuonTrigger24();
	k_isomuon_trig_match  = p.MatchedSingleIsoMuonTrigger();
	k_emu_trig_match8  = p.MatchedElMuonTrigger8();
	k_emu_trig_match17  = p.MatchedElMuonTrigger17();
	muon_ms_pt= p.MuonMSPt();
	muon_ms_eta= p.MuonMSEta();
	muon_ms_phi= p.MuonMSPhi();
	muon_ms_charge= p.MuonMSCharge();
	muon_ms_e= p.MuonMSE();
	muon_id_pt= p.MuonIDPt();
	muon_id_eta= p.MuonIDEta();
	muon_id_phi= p.MuonIDPhi();
	muon_id_charge= p.MuonIDCharge();
	muon_pt_up = p.PtShiftedUp();
	muon_pt_down = p.PtShiftedDown();
    }
    
    return *this;
}

//// SET CLASS VARIBALES

void KMuon::SetHLTDoubleMuMatched(bool match){
  k_dimuon_trig_match = match;
}

void KMuon::SetHLTSingleMuMatched(bool match){
  k_muon_trig_match =match;
}



void KMuon::SetHLTSingleMuMatched5(bool match){
  k_muon_trig_match5 =match;
}


void KMuon::SetHLTSingleMuMatched8(bool match){
  k_muon_trig_match8 =match;
}


void KMuon::SetHLTSingleMuMatched12(bool match){
  k_muon_trig_match12 =match;
}


void KMuon::SetHLTSingleMuMatched17(bool match){
  k_muon_trig_match17 =match;
}


void KMuon::SetHLTSingleMuMatched24(bool match){
  k_muon_trig_match24 =match;
}

void KMuon::SetHLTSingleMuIsoMatched(bool match){
  k_isomuon_trig_match =match;
}

void KMuon::SetHLTEMuMatched8(bool match){
  k_emu_trig_match8 =match;
}
void KMuon::SetHLTEMuMatched17(bool match){
  k_emu_trig_match17 =match;
}

void KMuon::SetMuonMSPt(float pt){
  muon_ms_pt=pt;
}

void KMuon::SetMuonMSEta(float eta){
  muon_ms_eta=eta;
}

void KMuon::SetMuonMSPhi(float phi){
  muon_ms_phi=phi;
}

void KMuon::SetMuonMSCharge(int charge){
  muon_ms_charge=charge;
}

void KMuon::SetMuonMSE(float e){
  muon_ms_e=e;
}

void KMuon::SetMuonIDPt(float pt){
  muon_id_pt=pt;
}

void KMuon::SetMuonIDEta(float eta){
  muon_id_eta=eta;
}

void KMuon::SetMuonIDPhi(float phi){
  muon_id_phi=phi;
}

void KMuon::SetMuonIDCharge(int charge){
  muon_id_charge=charge;
}


std::string KMuon::Type() const
{
    return "KMuon";
}

void KMuon::SetVertexDistXY(double vdistxy) {
  k_vtxdistxy= vdistxy;
}


void KMuon::SetMuonVtxIndex(int ivertex){
  i_muonVtx = ivertex;
}

void KMuon::SetPtErr(double pterror){  
  k_pterror = pterror;
}

void KMuon::SetEtaErr(double etaerror){
  k_etaerror = etaerror;
}

void KMuon::SetISOR03ChargedHad(double isor03ch ){
  k_isor03ch = isor03ch;
}

void KMuon::SetISOR03NeutralHad(double isor03n ){
  k_isor03n = isor03n;
}

void KMuon::SetISOR03Photon(double isor03ph ){
  k_isor03ph = isor03ph;
}


void KMuon::SetISOR04ChargedHad(double isor04ch ){
  k_isor04ch = isor04ch;
}

void KMuon::SetISOR04NeutralHad(double isor04n ){
  k_isor04n = isor04n;
}

void KMuon::SetISOR04Photon(double isor04ph ){
  k_isor04ph = isor04ph;
}

void KMuon::SetIsolationEcalVeto(double isoEcalveto ){
  k_isoEcalveto = isoEcalveto;
}

void KMuon::SetIsolationHcalVeto(double isoHcalveto ){
  k_isoHcalveto = isoHcalveto;
}


void KMuon::SetPileUp_R03(double pileupr03){
  
  k_MuonPFIsoR03PU = pileupr03;
}

void KMuon::SetPileUp_R04(double pileupr04){
  
  k_MuonPFIsoR04PU = pileupr04;
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


void KMuon::Setdz(double dz){

  k_dz = dz;
}

void KMuon::Setdxy(double dxy){

  k_dxy = dxy;
}


void KMuon::Setdxy_pat(double dxypat){

  k_dxy_pat = dxypat;
}

void KMuon::Setdxyerr_pat(double dxyerrpat){

  k_dxyerr_pat = dxyerrpat;
}


void KMuon::SetD0(double kd0){

  k_d0 = kd0;
}

void KMuon::SetD0Error(double d0err){

  k_d0err = d0err;
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



void KMuon::SetISPF(int ispf){

  k_muon_ispf = ispf;
}

void KMuon::SetIsGlobal(int isglobal){

  k_muon_isglobal =isglobal;
}

void KMuon::SetIsTracker(int istracker){

  k_muon_istracker =istracker;
}

void KMuon::SetMuonCocktailPt(double pt){
  muon_ck_pt=pt;
}

void KMuon::SetMuonCocktailEta(double eta){
  muon_ck_eta= eta;
}
void KMuon::SetMuonCocktailPhi(double phi){
  muon_ck_phi=phi;
}
void KMuon::SetMuonCocktailCharge(double charge){
  muon_ck_charge=charge;
}
void KMuon::SetMuonCocktailTrkD0(double d0){
  muon_ck_trkd0 = d0;
}
void KMuon::SetMuonCocktailTrkDz(double dz){
  muon_ck_trkdz=dz;
}
void KMuon::SetMuonCocktailGlobalChi2(double chi2){
  muon_ck_chi2= chi2;
}


void KMuon::SetMuonMatchedGenParticlePt(double genpt){
  k_muongen_pt = genpt;
}

void KMuon::SetMuonMatchedGenParticleEta(double geneta){
  k_muongen_eta = geneta;
}

void KMuon::SetMuonMatchedGenParticlePhi(double genphi){
  k_muongen_phi = genphi;
}


void KMuon::SetShiftedEUp(double pt_up){
  muon_pt_up= pt_up;
}

void KMuon::SetShiftedEDown(double pt_down){
  muon_pt_down= pt_down;
}
