#!/bin/sh

########################
### SAMPLE LIST ########## 
#######################


source ${LQANALYZER_DIR}/LQRun/txt/list_user_mc.sh


 declare -a input_samples=('WZ')

 declare -a all_mc=('HN150_mumumu_VmuN_0p1' 'HN40_mumumu_VmuN_0p1' 'HN60_mumumu_VmuN_0p1' 'HN700_mumumu_VmuN_0p1' 'HN_Tchannel_emem_M-100' 'HN_Tchannel_emem_M-1100' 'HN_Tchannel_emem_M-200' 'HN_Tchannel_emem_M-500' 'HN_Tchannel_epep_M-100' 'HN_Tchannel_epep_M-1100' 'HN_Tchannel_epep_M-200' 'HN_Tchannel_epep_M-500' 'HN_Tchannel_mummum_M-100' 'HN_Tchannel_mummum_M-1100' 'HN_Tchannel_mummum_M-200' 'HN_Tchannel_mummum_M-500' 'HN_Tchannel_mupmup_M-100' 'HN_Tchannel_mupmup_M-1100' 'HN_Tchannel_mupmup_M-200' 'HN_Tchannel_mupmup_M-500' 'DYJets_10to50' 'DYJets_MG_10to50' 'DYJets' 'DYJets_MG' 'DYJets_MG_5to50' 'GG_HToMuMu' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTbar_tW_noHadron' 'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'TTJets_aMC' 'TTJets_MG' 'TTLL_powheg' 'TTLL_powheg_scaledown' 'TTLL_powheg_scaleup' 'TTLJ_powheg' 'TTLJ_powheg_scaledown' 'TTLJ_powheg_scaleup' 'TT_powheg' 'TT_powheg_mtop1695' 'TT_powheg_mtop1755' 'VBF_HToMuMu' 'WJets' 'WJets_MG' 'WWW' 'WWZ' 'WW' 'WZZ' 'WZ' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ' 'ttbb') 

 declare -a mc_noqcd=('HN150_mumumu_VmuN_0p1' 'HN40_mumumu_VmuN_0p1' 'HN60_mumumu_VmuN_0p1' 'HN700_mumumu_VmuN_0p1' 'HN_Tchannel_emem_M-100' 'HN_Tchannel_emem_M-1100' 'HN_Tchannel_emem_M-200' 'HN_Tchannel_emem_M-500' 'HN_Tchannel_epep_M-100' 'HN_Tchannel_epep_M-1100' 'HN_Tchannel_epep_M-200' 'HN_Tchannel_epep_M-500' 'HN_Tchannel_mummum_M-100' 'HN_Tchannel_mummum_M-1100' 'HN_Tchannel_mummum_M-200' 'HN_Tchannel_mummum_M-500' 'HN_Tchannel_mupmup_M-100' 'HN_Tchannel_mupmup_M-1100' 'HN_Tchannel_mupmup_M-200' 'HN_Tchannel_mupmup_M-500' 'DYJets_10to50' 'DYJets_MG_10to50' 'DYJets' 'DYJets_MG' 'DYJets_MG_5to50' 'GG_HToMuMu' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTbar_tW_noHadron' 'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'TTJets_aMC' 'TTJets_MG' 'TTLL_powheg' 'TTLL_powheg_scaledown' 'TTLL_powheg_scaleup' 'TTLJ_powheg' 'TTLJ_powheg_scaledown' 'TTLJ_powheg_scaleup' 'TT_powheg' 'TT_powheg_mtop1695' 'TT_powheg_mtop1755' 'VBF_HToMuMu' 'WJets' 'WJets_MG' 'WWW' 'WWZ' 'WW' 'WZZ' 'WZ' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ' 'ttbb') 

 declare -a ch_wa=('') 


 declare -a ch_wz=('') 

 declare -a hn_ll_ee=('') 

 declare -a hn_ll_mm=('') 

 declare -a hn_ll_em=('') 

 declare -a hn_mmm=('') 

 declare -a hn_ll_tchann_ee=('HN_Tchannel_emem_M-100' 'HN_Tchannel_emem_M-1100' 'HN_Tchannel_emem_M-200' 'HN_Tchannel_emem_M-500' 'HN_Tchannel_epep_M-100' 'HN_Tchannel_epep_M-1100' 'HN_Tchannel_epep_M-200' 'HN_Tchannel_epep_M-500' '') 

 declare -a hn_ll_tchann_mm=('HN_Tchannel_mummum_M-100' 'HN_Tchannel_mummum_M-1100' 'HN_Tchannel_mummum_M-200' 'HN_Tchannel_mummum_M-500' 'HN_Tchannel_mupmup_M-100' 'HN_Tchannel_mupmup_M-1100' 'HN_Tchannel_mupmup_M-200' 'HN_Tchannel_mupmup_M-500' '') 


declare -a diboson_pythia=('WZ' 'ZZ' 'WW')

declare -a dy_mcatnlo=('DY10to50' 'DY50plus') 

declare -a dilepton_list=('DY10to50' 'DY50plus' 'WJets' 'WZ' 'ZZ' 'WW'  'TT' 'singletop_s' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg'  'WWW' 'ttWJets' 'ttZJets' 'ttHnobb_Powheg' 'ttHtobb_Powheg' 'ZZZ' 'WZZ')
declare -a trilepton_list=('DY10to50' 'DY50plus' 'WJets' 'WZ' 'ZZ' 'WW'  'TT' 'singletop_s' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg' 'WZZ' 'ZZZ')

declare -a qcd=('') 

declare -a qcd_mu=('') 

declare -a qcd_eg=('') 


declare -a hn_mm=('WZ' 'ZZ' 'WpWp_madgraph' 'WpWp_qcd_madgraph'  'ttWJetsToLNu' 'ttWJetsToQQ' 'ttZToLLNuNu' 'ttZToQQ' 'ttHtobb_Powheg' 'ttHnobb_Powheg' 'WZZ' 'vhf_Htomm_Powheg' 'ttZToLLNuNu' 'ggHtomm_Powheg') 

declare -a hn_ee=('WZ' 'ZZ' 'WpWp_madgraph' 'WpWp_qcd_madgraph'  'ttWJetsToLNu' 'ttWJetsToQQ' 'ttZToLLNuNu' 'ttZToQQ' 'DY10to50' 'DY50plus' 'ttHtobb_Powheg' 'ttHnobb_Powheg' 'WZZ' 'vhf_Htomm_Powheg' 'ttZToLLNuNu' 'ggHtomm_Powheg') 

declare -a hn_fakeee=('DY10to50' 'DY50plus' 'WJets'  'TT_madgraph')


declare -a singletop=('singletop_s' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg') 
