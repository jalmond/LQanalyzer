#include "KEvent.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KEvent)

/**
 *Default constructor.
 */
KEvent::KEvent() :
  TObject(),
  k_EventNumber(0),
  k_RunNumber(0),
  k_nvertices(-999),
  k_lumisec(-999),
  k_ngoodvertices(-999),
  k_pdf_id1(-999),
  k_pdf_id2(-999),
  k_lumi_mask_silver(-999),
  k_lumi_mask_gold(-999),
  k_vertexX(-999.),
  k_vertexY(-999.),
  k_vertexZ(-999.), 
  k_vertexNDOF(-999.), 
  k_mcweight(-999.),
  k_lheweight(-999.),
  k_pdf_q(-999.),
  k_pdf_x1(-999.),
  k_pdf_x2(-999.),

  k_PF_MET(-999.), 
  k_PF_METphi(-999.),
  k_PF_SumET(-999.), 
  k_NoHF_MET(-999.),
  k_NoHF_METphi(-999.),
  k_NoHF_SumET(-999.),
  k_PF_MET_MuonEn_up(-999.),
  k_PF_MET_MuonEn_down(-999.),
  k_PF_MET_ElectronEn_up(-999.),
  k_PF_MET_ElectronEn_down(-999.),
  k_PF_MET_JetEn_up(-999.),
  k_PF_MET_JetEn_down(-999.),
  k_PF_SumET_JetEn_up(-999.),
  k_PF_SumET_JetEn_down(-999.),
  k_PF_MET_JetRes_up(-999.),
  k_PF_MET_JetRes_down(-999.),
  k_PF_SumET_JetRes_up(-999.),
  k_PF_SumET_JetRes_down(-999.),
  k_PF_MET_unclusteredEn_up(-999.),
  k_PF_MET_unclusteredEn_down(-999.),
  k_PF_SumET_unclusteredEn_up(-999.),
  k_PF_SumET_unclusteredEn_down(-999.),

  k_isData(false), 
  k_isgoodevent(false),

  k_passBadEESupercrystalFilter(false),
  k_passCSCHaloFilterTight(false),
  k_passEcalDeadCellTriggerPrimitiveFilter(false),
  k_passHBHENoiseFilter(false),
  k_PileUpInteractionsTrue(-999.),
  k_pu_silver_weight(-999.),
  k_pu_silver_p_weight(-999.),
  k_pu_silver_m_weight(-999.),
  k_pu_gold_weight(-999.),
  k_pu_gold_p_weight(-999.),
  k_pu_gold_m_weight(-999.),
  k_catversion(""),
  k_lumimask(snu::KEvent::missing)

{

}

/**
 * Copy constructor.
 */
KEvent::KEvent(const KEvent& ev) :
  TObject(),
  k_EventNumber(ev.k_EventNumber),
  k_RunNumber(ev.k_RunNumber),
  k_nvertices(ev.k_nvertices),
  k_lumisec(ev.k_lumisec),
  k_ngoodvertices(ev.k_ngoodvertices),
  k_pdf_id1(ev.k_pdf_id1),
  k_pdf_id2(ev.k_pdf_id2),
  k_lumi_mask_silver(ev.k_lumi_mask_silver),
  k_lumi_mask_gold(ev.k_lumi_mask_gold),
  k_vertexX(ev.k_vertexX),
  k_vertexY(ev.k_vertexY),
  k_vertexZ(ev.k_vertexZ),
  k_vertexNDOF(ev.k_vertexNDOF),
  k_mcweight(ev.k_mcweight),
  k_lheweight(ev.k_lheweight),
  k_pdf_q(ev.k_pdf_q),
  k_pdf_x1(ev.k_pdf_x1),
  k_pdf_x2(ev.k_pdf_x2),

  k_PF_MET(ev.k_PF_MET),
  k_PF_METphi(ev.k_PF_METphi),
  k_PF_SumET(ev.k_PF_SumET),
  k_NoHF_MET(ev.k_NoHF_MET),
  k_NoHF_METphi(ev.k_NoHF_METphi),
  k_NoHF_SumET(ev.k_NoHF_SumET),
  k_PF_MET_MuonEn_up(ev.k_PF_MET_MuonEn_up),
  k_PF_MET_MuonEn_down(ev.k_PF_MET_MuonEn_down),
  k_PF_MET_ElectronEn_up(ev.k_PF_MET_ElectronEn_up),
  k_PF_MET_ElectronEn_down(ev.k_PF_MET_ElectronEn_down),
  k_PF_MET_JetEn_up(ev.k_PF_MET_JetEn_up),
  k_PF_MET_JetEn_down(ev.k_PF_MET_JetEn_down),
  k_PF_SumET_JetEn_up(ev.k_PF_SumET_JetEn_up),
  k_PF_SumET_JetEn_down(ev.k_PF_SumET_JetEn_down),
  k_PF_MET_JetRes_up(ev.k_PF_MET_JetRes_up),
  k_PF_MET_JetRes_down(ev.k_PF_MET_JetRes_down),
  k_PF_SumET_JetRes_up(ev.k_PF_SumET_JetRes_up),
  k_PF_SumET_JetRes_down(ev.k_PF_SumET_JetRes_down),
  k_PF_MET_unclusteredEn_up(ev.k_PF_MET_unclusteredEn_up),
  k_PF_MET_unclusteredEn_down(ev.k_PF_MET_unclusteredEn_down),
  k_PF_SumET_unclusteredEn_up(ev.k_PF_SumET_unclusteredEn_up),
  k_PF_SumET_unclusteredEn_down(ev.k_PF_SumET_unclusteredEn_down),
  k_isData(ev.k_isData),
  k_isgoodevent(ev.k_isgoodevent),
  k_passBadEESupercrystalFilter(ev.k_passBadEESupercrystalFilter),
  k_passCSCHaloFilterTight(ev.k_passCSCHaloFilterTight),
  k_passEcalDeadCellTriggerPrimitiveFilter(ev.k_passEcalDeadCellTriggerPrimitiveFilter),
  k_passHBHENoiseFilter(ev.k_passHBHENoiseFilter),
  k_PileUpInteractionsTrue(ev.k_PileUpInteractionsTrue),
  k_pu_silver_weight(ev.k_pu_silver_weight),
  k_pu_silver_p_weight(ev.k_pu_silver_p_weight),
  k_pu_silver_m_weight(ev.k_pu_silver_m_weight),
  k_pu_gold_weight(ev.k_pu_gold_weight),
  k_pu_gold_p_weight(ev.k_pu_gold_p_weight),
  k_pu_gold_m_weight(ev.k_pu_gold_m_weight),
  k_catversion(ev.k_catversion),
  k_lumimask(ev.k_lumimask)

{
}


KEvent::~KEvent()
{
}

void KEvent::Reset()
{
  
  k_EventNumber= -999;
  k_RunNumber= -999;
  k_nvertices= -999;
  k_lumisec=-999; 
  k_ngoodvertices= -999;
  k_pdf_id1=-999;
  k_pdf_id2=-999;
  k_lumi_mask_silver=-999;
  k_lumi_mask_gold=-999;
  k_vertexX= -999.;
  k_vertexY= -999.;
  k_vertexZ= -999.;
  k_vertexNDOF= -999.;
  k_mcweight= -999.;
  k_lheweight= -999.;
  k_pdf_q=-999.;
  k_pdf_x1= -999.;
  k_pdf_x2=-999.;

  k_PF_MET= -999.;
  k_PF_SumET= -999.;
  k_PF_METphi= -999.;
  k_NoHF_MET= -999;
  k_NoHF_METphi= -999;
  k_NoHF_SumET= -999;
  k_PF_MET_MuonEn_up = -999.;
  k_PF_MET_MuonEn_down = -999.;
  k_PF_MET_ElectronEn_up = -999.;
  k_PF_MET_ElectronEn_down = -999.;
  k_PF_MET_JetEn_up = -999.;
  k_PF_MET_JetEn_down = -999.;
  k_PF_SumET_JetEn_up = -999.;
  k_PF_SumET_JetEn_down = -999.;
  k_PF_MET_JetRes_up = -999.;
  k_PF_MET_JetRes_down = -999.;
  k_PF_SumET_JetRes_up = -999.;
  k_PF_SumET_JetRes_down = -999.;
  k_PF_MET_unclusteredEn_up = -999.;
  k_PF_MET_unclusteredEn_down = -999.;
  k_PF_SumET_unclusteredEn_up = -999.;
  k_PF_SumET_unclusteredEn_down = -999.;
  
  k_isData= false;
  k_isgoodevent = false;
  k_passBadEESupercrystalFilter= false;
  k_passCSCHaloFilterTight= false;
  k_passEcalDeadCellTriggerPrimitiveFilter= false;
  k_passHBHENoiseFilter= false;
  k_PileUpInteractionsTrue = -999.;
  k_pu_silver_weight = -999.;
  k_pu_silver_p_weight=-999.;
  k_pu_silver_m_weight = -999.;
  k_pu_gold_weight = -999.;
  k_pu_gold_p_weight=-999.;
  k_pu_gold_m_weight = -999.;
  k_catversion="";
  k_lumimask=missing;

}



KEvent& KEvent::operator= (const KEvent& p)
{
    if (this != &p) {

      k_EventNumber=p.EventNumber();
      k_RunNumber=p.RunNumber();
      k_nvertices= p.nVertices();
      k_lumisec= p.LumiSection();
      k_ngoodvertices = p.nGoodVertices();
      k_pdf_id1 = p.Id1();
      k_pdf_id2 = p.Id2();
      k_lumi_mask_silver = p.LumiMaskSilver();
      k_lumi_mask_gold = p.LumiMaskGold();
      k_vertexX=p.VertexX();
      k_vertexY=p.VertexY();
      k_vertexZ=p.VertexZ();
      k_vertexNDOF=p.VertexNDOF();
      k_mcweight = p.MCWeight();
      k_lheweight = p.LHEWeight();
      k_pdf_q = p.Q();
      k_pdf_x1 = p.x1();
      k_pdf_x2 = p.x2();
            
      k_PF_MET= p.MET(pfmet);
      k_PF_METphi= p.METPhi(pfmet);
      k_PF_SumET = p.SumET(pfmet);
      k_NoHF_MET= p.MET(nohf);
      k_NoHF_METphi= p.METPhi(nohf);
      k_NoHF_SumET = p.SumET(nohf);
      k_PF_MET_MuonEn_up = p.PFMETShifted(MuonEn,up);
      k_PF_MET_MuonEn_down = p.PFMETShifted(MuonEn,down);
      k_PF_MET_ElectronEn_up = p.PFMETShifted(ElectronEn,up);
      k_PF_MET_ElectronEn_down = p.PFMETShifted(ElectronEn,down);
      k_PF_MET_JetEn_up = p.PFMETShifted(JetEn,up);
      k_PF_MET_JetEn_down = p.PFMETShifted(JetEn,down);
      k_PF_SumET_JetEn_up = p.PFSumETShifted(JetEn,up);
      k_PF_SumET_JetEn_down = p.PFSumETShifted(JetEn,down);
      k_PF_MET_JetRes_up = p.PFMETShifted(JetRes,up);
      k_PF_MET_JetRes_down = p.PFMETShifted(JetRes,down);
      k_PF_SumET_JetRes_up = p.PFSumETShifted(JetRes,up);
      k_PF_SumET_JetRes_down = p.PFSumETShifted(JetRes,down);
      k_PF_MET_unclusteredEn_up = p.PFMETShifted(Unclustered,up);
      k_PF_MET_unclusteredEn_down = p.PFMETShifted(Unclustered,down);
      k_PF_SumET_unclusteredEn_up = p.PFSumETShifted(Unclustered,up);
      k_PF_SumET_unclusteredEn_down = p.PFSumETShifted(Unclustered,down);

      k_isData=p.IsData();
      k_isgoodevent= p.HasGoodPrimaryVertex();

      k_passBadEESupercrystalFilter = p.PassBadEESupercrystalFilter();
      k_passCSCHaloFilterTight = p.PassCSCHaloFilterTight();
      k_passEcalDeadCellTriggerPrimitiveFilter = p.PassEcalDeadCellTriggerPrimitiveFilter();
      k_passHBHENoiseFilter = p.PassHBHENoiseFilter();
      k_PileUpInteractionsTrue = p.PileUpInteractionsTrue();
      k_pu_silver_weight = p.PileUpWeight_Silver(central);	
      k_pu_silver_p_weight= p.PileUpWeight_Silver(up);
      k_pu_silver_m_weight= p.PileUpWeight_Silver(down);
      k_pu_gold_weight = p.PileUpWeight_Gold(central);
      k_pu_gold_p_weight= p.PileUpWeight_Gold(up);
      k_pu_gold_m_weight= p.PileUpWeight_Gold(down);

      k_catversion = p.CatVersion();
      k_lumimask = p.GetJSON();
    }
    
    return *this;
}

//// SET CLASS VARIBALES
void KEvent::SetCatVersion(std::string cat){
  k_catversion = cat;
}

void KEvent::SetPassCSCHaloFilterTight(bool pass){
  k_passCSCHaloFilterTight = pass;
}

void KEvent::SetPassBadEESupercrystalFilter(bool pass){
  k_passBadEESupercrystalFilter = pass;
}

void KEvent::SetPassEcalDeadCellTriggerPrimitiveFilter(bool pass){
  k_passEcalDeadCellTriggerPrimitiveFilter = pass;
}

void KEvent::SetPassHBHENoiseFilter(bool pass){
  k_passHBHENoiseFilter= pass;
}

void KEvent::SetPileUpInteractionsTrue(double npu){
  k_PileUpInteractionsTrue = npu;
}

void KEvent::SetPUWeight(json type, syst_dir sys, double puw){
  if(type==silver){
    if(sys==central)  k_pu_silver_weight = puw;
    if(sys==up)  k_pu_silver_p_weight = puw;
    if(sys==down)  k_pu_silver_m_weight = puw;
  }
  else  if(type==gold){
    if(sys==central)  k_pu_gold_weight = puw;
    if(sys==up)  k_pu_gold_p_weight = puw;
    if(sys==down)  k_pu_gold_m_weight = puw;
  }
  else {std::cout<< "PileUp weight not set correctly" << std::endl; exit(1);}

}


void KEvent::SetWeight(double mcweight){
  k_mcweight = mcweight;
}




void KEvent::SetEventNumber(int ev){
  k_EventNumber = ev;
}

void KEvent::SetRunNumber(int rn){
  k_RunNumber = rn;
}

void KEvent::SetIsData(bool isdata){
  k_isData = isdata;
}



//// Setting Missing ET variables

void KEvent::SetMET(met_type type, double met, double metphi, double sumet){
  if(type == pfmet){
    k_PF_MET = met;
    k_PF_METphi = metphi;
    k_PF_SumET =sumet;
  }

  else if(type== nohf){
    k_NoHF_MET = met;
    k_NoHF_METphi = metphi;
    k_NoHF_SumET =sumet;
  }

  else {cout << "Problem setting MET" << endl; exit(0) ;}
}

void KEvent::SetPFMETShift(syst_dir dir, met_syst type, double val){
  if(dir == up){
    if(type==MuonEn)  k_PF_MET_MuonEn_up = val;
    if(type==ElectronEn)  k_PF_MET_ElectronEn_up= val;
    if(type==JetEn)  k_PF_MET_JetEn_up= val;
    if(type==JetRes)  k_PF_MET_JetRes_up= val;
    if(type==Unclustered)  k_PF_MET_unclusteredEn_up= val;
  }
  else if (dir == down){
    if(type==MuonEn)  k_PF_MET_MuonEn_down= val;
    if(type==ElectronEn)  k_PF_MET_ElectronEn_down= val;
    if(type==JetEn)  k_PF_MET_JetEn_down= val;
    if(type==JetRes)  k_PF_MET_JetRes_down= val;
    if(type==Unclustered)  k_PF_MET_unclusteredEn_down= val;
  }
  else {cout << "Problem setting MET shifted values" << endl ; exit(0);}
}

void KEvent::SetPFSumETShift(syst_dir dir, met_syst type, double val){
  if(dir == up){
    if(type==JetEn)  k_PF_SumET_JetEn_up= val;
    if(type==JetRes)  k_PF_SumET_JetRes_up= val;
    if(type==Unclustered)  k_PF_SumET_unclusteredEn_up= val;
  }
  else if (dir == down){
    if(type==JetEn)  k_PF_SumET_JetEn_down= val;
    if(type==JetRes)  k_PF_SumET_JetRes_down= val;
    if(type==Unclustered)  k_PF_SumET_unclusteredEn_down= val;
  }
 
  else {cout << "Problem setting SumET shifted values" <<endl ; exit(0);}

}




/// Settizang Vertex Variables
void KEvent::SetNVertices(int nvert){
  k_nvertices = nvert;
}


void KEvent::SetLumiSection(int ls){
  k_lumisec = ls;
}


void KEvent::SetLumiMask(json type, int mask){
  if(type==silver) k_lumi_mask_silver=mask;
  else if(type==gold) k_lumi_mask_gold=mask;
  else {std::cout<< "LumiMask not set correctly" << std::endl; exit(1);}
}
void KEvent::SetIsGoodEvent(int nvert){
  if(nvert > 0) k_isgoodevent = true;
  else k_isgoodevent = false;
}

void KEvent::SetJSON(json js){
  k_lumimask = js;
}

Bool_t KEvent::LumiMask(json js){

  if(js== silver){
    if(k_lumi_mask_silver==1) return true;
    else return false;
  }
  else if(js==gold){
    if(k_lumi_mask_gold==1) return true;
    else return false;
  }
  else if(js==missing) return true;
  else return false;
}


Double_t KEvent::PileUpWeight(json js, syst_dir sys){
  if(k_lumimask==missing) { cout << "No lumimasl " << endl; return -999;}
  if(TString(k_catversion).Contains("v7-4-")) return -999;
  else if(js==silver) return PileUpWeight_Silver(sys);
  else if(js==gold) return PileUpWeight_Gold(sys);
  else return -999;
}

///New forCAT v7-4-5 (MET systematics in one function)
Double_t KEvent::PFMETShifted ( met_syst type, syst_dir dir) const{
  
  if(TString(k_catversion).Contains("v7-4-4")) return k_PF_MET;
  if(dir == up){
    if(type==None) return k_PF_MET;
    else if(type==MuonEn) return k_PF_MET_MuonEn_up;
    else if(type==ElectronEn) return k_PF_MET_ElectronEn_up;
    else if(type==JetEn) return k_PF_MET_JetEn_up;
    else if(type==JetRes) return k_PF_MET_JetRes_up;
    else if(type==Unclustered) return k_PF_MET_unclusteredEn_up;
    else return -999.;
  }
  else  if(dir == down){
    if(type==None) return k_PF_MET;
    else if(type==MuonEn) return k_PF_MET_MuonEn_down;
    else if(type==ElectronEn) return k_PF_MET_ElectronEn_down;
    else if(type==JetEn) return k_PF_MET_JetEn_down;
    else if(type==JetRes) return k_PF_MET_JetRes_down;
    else if(type==Unclustered) return k_PF_MET_unclusteredEn_down;
    else return-999.;

  }
  return k_PF_MET;
}

Double_t KEvent::PFSumETShifted(met_syst type,syst_dir dir) const{
  if(TString(k_catversion).Contains("v7-4-4")) return k_PF_SumET;
 
  if(dir == up){
    if(type==None) return k_PF_SumET;
    if(type==JetEn) return k_PF_SumET_JetEn_up;
    if(type==JetRes) return k_PF_SumET_JetRes_up;
    if(type==Unclustered) return k_PF_SumET_unclusteredEn_up;
  }
  else if(dir == down){
    if(type==None) return k_PF_SumET;
    if(type==JetEn) return k_PF_SumET_JetEn_down;
    if(type==JetRes) return k_PF_SumET_JetRes_down;
    if(type==Unclustered) return k_PF_SumET_unclusteredEn_down;
  }
  return k_PF_SumET;
}


Double_t KEvent::MET(met_type type) const{
  
  if(k_lumimask == silver ) return k_NoHF_MET;

  if (type == pfmet) return k_PF_MET;
  else if(type == nohf) return k_NoHF_MET;
  
  return -999.;
}
 
Double_t KEvent::METPhi(met_type type) const{
  
  if(k_lumimask == silver ) return k_NoHF_METphi;

  if (type == pfmet) return k_PF_METphi;
  else if(type == nohf) return k_NoHF_METphi;

  return -999.;
}

Double_t KEvent::SumET(met_type type) const{
  
  if(k_lumimask == silver ) return k_NoHF_SumET;
 
  if (type == pfmet) return k_PF_SumET;
  else if(type == nohf) return k_NoHF_SumET;
  return -999.;
}



/// Settizang Vertex Variables
void KEvent::SetNGoodVertices(int nvert){
  k_ngoodvertices = nvert;
}


void KEvent::SetVertexInfo(double vX, double vY, double vZ, double NDOF){
  k_vertexX = vX;
  k_vertexY = vY;
  k_vertexZ = vZ;
  k_vertexNDOF = NDOF;
}

void KEvent::SetGenId(int id1, int id2){
  k_pdf_id1 = id1;
  k_pdf_id2 = id2;
}


void KEvent::SetGenQ(double q ){
  k_pdf_q = q;
}


void KEvent::SetGenX(double x1, double x2){
  k_pdf_x1 = x1;
  k_pdf_x2 = x2;
}

void KEvent::SetLHEWeight(double lw){
  k_lheweight = lw;
}





