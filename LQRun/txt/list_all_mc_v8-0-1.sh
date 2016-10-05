#!/bin/sh

########################
### SAMPLE LIST ########## 
#######################


source ${LQANALYZER_DIR}/LQRun/txt/list_user_mc.sh


 declare -a input_samples=('WZ_pythia8')

 declare -a all_mc=('DY10to50_MCatNLO' 'DY10to50_madgraph' 'DY50plus_MCatNLO' 'DY50plus_madgraph' 'DY5to50_madgraph' 'ggHtomm_Powheg' 'singletop_s_MCatNLO' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tW_nofullhad_Powheg' 'singletop_tbarW_Powheg' 'singletop_tbarW_nofullhad_Powheg' 'singletop_tW_Powheg' 'TT_MCatNLO' 'TT_madgraph' 'TT_2l2nu_powheg' 'TT_2l2nu_Sup_powheg' 'TT_2l2nu_Sdownpowheg' 'TT_semilep_powheg' 'TT_semilep_Sup_powheg' 'TT_semilep_Sdown_powheg' 'TT_powheg' 'TT_powheg_m169' 'TT_powheg_m171' 'vhf_Htomm_Powheg' 'WJets_MCatNLO' 'WJets_madgraph' 'WWW_MCatNLO' 'WWZ_MCatNLO' 'WW_pythia8' 'WZZ_MCatNLO' 'WZ_pythia8' 'ZZZ_MCatNLO' 'ZZ_pythia8' 'ttHnobb_Powheg' 'ttHtobb_Powheg' 'ttWJets' 'ttZJets' '') 

 declare -a mc_noqcd=('DY10to50_MCatNLO' 'DY10to50_madgraph' 'DY50plus_MCatNLO' 'DY50plus_madgraph' 'DY5to50_madgraph' 'ggHtomm_Powheg' 'singletop_s_MCatNLO' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tW_nofullhad_Powheg' 'singletop_tbarW_Powheg' 'singletop_tbarW_nofullhad_Powheg' 'singletop_tW_Powheg' 'TT_MCatNLO' 'TT_madgraph' 'TT_2l2nu_powheg' 'TT_2l2nu_Sup_powheg' 'TT_2l2nu_Sdownpowheg' 'TT_semilep_powheg' 'TT_semilep_Sup_powheg' 'TT_semilep_Sdown_powheg' 'TT_powheg' 'TT_powheg_m169' 'TT_powheg_m171' 'vhf_Htomm_Powheg' 'WJets_MCatNLO' 'WJets_madgraph' 'WWW_MCatNLO' 'WWZ_MCatNLO' 'WW_pythia8' 'WZZ_MCatNLO' 'WZ_pythia8' 'ZZZ_MCatNLO' 'ZZ_pythia8' 'ttHnobb_Powheg' 'ttHtobb_Powheg' 'ttWJets' 'ttZJets' '') 

 declare -a ch_wa=('') 


 declare -a ch_wz=('') 

 declare -a hn_ll_ee=('') 

 declare -a hn_ll_mm=('') 

 declare -a hn_ll_em=('') 

 declare -a hn_mmm=('') 

 declare -a hn_ll_tchann_ee=('') 

 declare -a hn_ll_tchann_mm=('') 


declare -a diboson_pythia=('WZ_pythia8' 'ZZ_pythia8' 'WW_pythia8')

declare -a dy_mcatnlo=('DY10to50_MCatNLO' 'DY50plus_MCatNLO') 

declare -a dilepton_list=('DY10to50_MCatNLO' 'DY50plus_MCatNLO' 'WJets_MCatNLO' 'WZ_pythia8' 'ZZ_pythia8' 'WW_pythia8'  'TT_MCatNLO' 'singletop_s_MCatNLO' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg' 'ttWJetsToLNu_MCatNLO' 'WWW_MCatNLO' 'ttWJets' 'ttZJets' 'ttHnobb_Powheg' 'ttHtobb_Powheg' 'ZZZ_MCatNLO' 'WZZ_MCatNLO')
declare -a trilepton_list=('DY10to50_MCatNLO' 'DY50plus_MCatNLO' 'WJets_MCatNLO' 'WZ_pythia8' 'ZZ_pythia8' 'WW_pythia8'  'TT_MCatNLO5' 'singletop_s_MCatNLO' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg' 'ZZ_pythia8' 'WJets_MCatNLO'  'WZZ_MCatNLO' 'ZZZ_MCatNLO')

declare -a qcd=('') 

declare -a qcd_mu=('') 

declare -a qcd_eg=('') 


declare -a hn_mm=('WZ_pythia8' 'ZZ_pythia8' 'WpWp_madgraph' 'WpWp_qcd_madgraph'  'ttWJetsToLNu_MCatNLO' 'ttWJetsToQQ_MCatNLO' 'ttZToLLNuNu_MCatNLO' 'ttZToQQ_MCatNLO' 'ttHtobb_Powheg' 'ttHnobb_Powheg' 'WZZ_MCatNLO' 'vhf_Htomm_Powheg' 'ttZToLLNuNu_MCatNLO' 'ggHtomm_Powheg') 

declare -a hn_ee=('WZ_pythia8' 'ZZ_pythia8' 'WpWp_madgraph' 'WpWp_qcd_madgraph'  'ttWJetsToLNu_MCatNLO' 'ttWJetsToQQ_MCatNLO' 'ttZToLLNuNu_MCatNLO' 'ttZToQQ_MCatNLO' 'DY10to50_MCatNLO' 'DY50plus_MCatNLO' 'ttHtobb_Powheg' 'ttHnobb_Powheg' 'WZZ_MCatNLO' 'vhf_Htomm_Powheg' 'ttZToLLNuNu_MCatNLO' 'ggHtomm_Powheg') 

declare -a hn_fakeee=('DY10to50_MCatNLO' 'DY50plus_MCatNLO' 'WJets_MCatNLO'  'TT_madgraph')


declare -a singletop=('singletop_s_MCatNLO' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg') 
