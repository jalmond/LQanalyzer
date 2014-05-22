svn co svn+ssh://svn.cern.ch/reps/atlasinst/Institutes/Manchester/Users/John/WRHNCommonLeptonFakes/trunk WRHNCommonLeptonFakes/

Download the rootfile:
cd WRHNCommonLeptonFakes/share
source getfiles.sh



In analysis code you need these lines in the header:

#include "WRHNCommonLeptonFakes/WRHNCommonLeptonFakes.h"

WRHNCommonLeptonFakes* m_fakeobj;


In the source code you need to make the class object in the constructor i.e., (where path = path to WRHNCommonLeptonFakes package)

m_fakeobj = new WRHNCommonLeptonFakes(path+"/WRHNCommonLeptonFakes/share/");


In the event loop:

    
    float mm_weight = m_fakeobj->get_dilepton_mm_eventweight(muons,jets,is_lep1_tight,is_lep2_tight,is_mu1_HF,is_mu2_HF,false);
    float ee_weight = m_fakeobj->get_dilepton_ee_eventweight(electrons,jets,el1_conv,el2_conv,el1_primarytrigpass, el1_secondarytriggerpass, el2_primarytrigpass, el2_secondarytriggerpass, is_lep1_tight,is_lep2_tight,false, usekirill);
    float em_weight = m_fakeobj->get_dilepton_emu_eventweight(muons,electrons,jets,is_mu1_tight,is_el1_tight,is_mu1_HF, ismuontriggermatched, el1_conv, el1_primartytrigpass, el1_secondarytrigpass, false, usekirill);

    where: 
    muons = tlv of muons (ordered in pt)
    electrons = tlv of electrons (ordered in pt)
    jets = tlv of jets
    is_lep1_tight = is lepton 1 tight
    is_lep2_tight = is lepton 1 tight
    is_muX_HF = is muon X HF 
    elX_primarytrigpass = did electron X match to the primary electron trigger 
    elX_secondarytrigpass = did electron X match to the primary electron trigger 
    elX_conv = is electron X from a conversion using d3pd variable()
    usekirill = bool to sepicfy lous/kirills electron rates