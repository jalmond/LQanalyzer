#!/bin/sh

########################
### SAMPLE LIST ########## 
#######################


source ${LQANALYZER_DIR}/LQRun/txt/list_user_mc.sh


declare -a input_samples=('WZ')

declare -a all_mc=('DYJets_10to50' 'DYJets' 'HNEmEm_100' 'HNEmEm_1100' 'HNEmEm_1500' 'HNEmEm_200' 'HNEmEm_40' 'HNEmEm_50' 'HNEmEm_500' 'HNEmEm_60' 'HNEmEp_100' 'HNEmEp_1100' 'HNEmEp_1500' 'HNEmEp_200' 'HNEmEp_40' 'HNEmEp_50' 'HNEmEp_500' 'HNEmEp_60' 'HNEmMum_100' 'HNEmMum_1100' 'HNEmMum_1500' 'HNEmMum_200' 'HNEmMum_40' 'HNEmMum_50' 'HNEmMum_500' 'HNEmMum_60' 'HNEmMup_100' 'HNEmMup_1100' 'HNEmMup_1500' 'HNEmMup_200' 'HNEmMup_40' 'HNEmMup_50' 'HNEmMup_500' 'HNEmMup_60' 'HNEpEm_100' 'HNEpEm_1100' 'HNEpEm_1500' 'HNEpEm_200' 'HNEpEm_40' 'HNEpEm_50' 'HNEpEm_500' 'HNEpEm_60' 'HNEpEp_100' 'HNEpEp_1100' 'HNEpEp_1500' 'HNEpEp_200' 'HNEpEp_40' 'HNEpEp_50' 'HNEpEp_500' 'HNEpEp_60' 'HNEpMum_100' 'HNEpMum_1100' 'HNEpMum_1500' 'HNEpMum_200' 'HNEpMum_40' 'HNEpMum_50' 'HNEpMum_500' 'HNEpMum_60' 'HNEpMup_100' 'HNEpMup_1100' 'HNEpMup_1500' 'HNEpMup_200' 'HNEpMup_40' 'HNEpMup_50' 'HNEpMup_500' 'HNEpMup_60' 'HNMumEm_100' 'HNMumEm_1100' 'HNMumEm_1500' 'HNMumEm_200' 'HNMumEm_40' 'HNMumEm_50' 'HNMumEm_500' 'HNMumEm_60' 'HNMumEp_100' 'HNMumEp_1100' 'HNMumEp_1500' 'HNMumEp_200' 'HNMumEp_40' 'HNMumEp_50' 'HNMumEp_500' 'HNMumEp_60' 'HNMumMum_100' 'HNMumMum_1100' 'HNMumMum_1500' 'HNMumMum_200' 'HNMumMum_40' 'HNMumMum_50' 'HNMumMum_500' 'HNMumMum_60' 'HNMumMup_100' 'HNMumMup_1100' 'HNMumMup_1500' 'HNMumMup_200' 'HNMumMup_40' 'HNMumMup_50' 'HNMumMup_500' 'HNMumMup_60' 'HNMupEm_100' 'HNMupEm_1100' 'HNMupEm_1500' 'HNMupEm_200' 'HNMupEm_40' 'HNMupEm_50' 'HNMupEm_500' 'HNMupEp_100' 'HNMupEp_1100' 'HNMupEp_1500' 'HNMupEp_200' 'HNMupEp_40' 'HNMupEp_50' 'HNMupEp_500' 'HNMupEp_60' 'HNMupMum_100' 'HNMupMum_1100' 'HNMupMum_1500' 'HNMupMum_200' 'HNMupMum_40' 'HNMupMum_50' 'HNMupMum_500' 'HNMupMum_60' 'HNMupMup_100' 'HNMupMup_1100' 'HNMupMup_1500' 'HNMupMup_200' 'HNMupMup_40' 'HNMupMup_50' 'HNMupMup_500' 'HNMupMup_60' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTbar_tW_noHadron' 'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'TTJets_aMC' 'ttWToLNu' 'ttZToLL_M-1to10' 'WGtoLNuG' 'WgstarToLNuEE' 'WJets'  'WWW' 'WWZ' 'WW' 'WZTo3LNu_amcatnlo' 'WZTo3LNu_powheg' 'WZZ' 'WZ' 'WpWpEWKQCD' 'ZZTo4L_powheg' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ') 

declare -a mc_noqcd=('DYJets_10to50' 'DYJets' 'HNEmEm_100' 'HNEmEm_1100' 'HNEmEm_1500' 'HNEmEm_200' 'HNEmEm_40' 'HNEmEm_50' 'HNEmEm_500' 'HNEmEm_60' 'HNEmEp_100' 'HNEmEp_1100' 'HNEmEp_1500' 'HNEmEp_200' 'HNEmEp_40' 'HNEmEp_50' 'HNEmEp_500' 'HNEmEp_60' 'HNEmMum_100' 'HNEmMum_1100' 'HNEmMum_1500' 'HNEmMum_200' 'HNEmMum_40' 'HNEmMum_50' 'HNEmMum_500' 'HNEmMum_60' 'HNEmMup_100' 'HNEmMup_1100' 'HNEmMup_1500' 'HNEmMup_200' 'HNEmMup_40' 'HNEmMup_50' 'HNEmMup_500' 'HNEmMup_60' 'HNEpEm_100' 'HNEpEm_1100' 'HNEpEm_1500' 'HNEpEm_200' 'HNEpEm_40' 'HNEpEm_50' 'HNEpEm_500' 'HNEpEm_60' 'HNEpEp_100' 'HNEpEp_1100' 'HNEpEp_1500' 'HNEpEp_200' 'HNEpEp_40' 'HNEpEp_50' 'HNEpEp_500' 'HNEpEp_60' 'HNEpMum_100' 'HNEpMum_1100' 'HNEpMum_1500' 'HNEpMum_200' 'HNEpMum_40' 'HNEpMum_50' 'HNEpMum_500' 'HNEpMum_60' 'HNEpMup_100' 'HNEpMup_1100' 'HNEpMup_1500' 'HNEpMup_200' 'HNEpMup_40' 'HNEpMup_50' 'HNEpMup_500' 'HNEpMup_60' 'HNMumEm_100' 'HNMumEm_1100' 'HNMumEm_1500' 'HNMumEm_200' 'HNMumEm_40' 'HNMumEm_50' 'HNMumEm_500' 'HNMumEm_60' 'HNMumEp_100' 'HNMumEp_1100' 'HNMumEp_1500' 'HNMumEp_200' 'HNMumEp_40' 'HNMumEp_50' 'HNMumEp_500' 'HNMumEp_60' 'HNMumMum_100' 'HNMumMum_1100' 'HNMumMum_1500' 'HNMumMum_200' 'HNMumMum_40' 'HNMumMum_50' 'HNMumMum_500' 'HNMumMum_60' 'HNMumMup_100' 'HNMumMup_1100' 'HNMumMup_1500' 'HNMumMup_200' 'HNMumMup_40' 'HNMumMup_50' 'HNMumMup_500' 'HNMumMup_60' 'HNMupEm_100' 'HNMupEm_1100' 'HNMupEm_1500' 'HNMupEm_200' 'HNMupEm_40' 'HNMupEm_50' 'HNMupEm_500' 'HNMupEp_100' 'HNMupEp_1100' 'HNMupEp_1500' 'HNMupEp_200' 'HNMupEp_40' 'HNMupEp_50' 'HNMupEp_500' 'HNMupEp_60' 'HNMupMum_100' 'HNMupMum_1100' 'HNMupMum_1500' 'HNMupMum_200' 'HNMupMum_40' 'HNMupMum_50' 'HNMupMum_500' 'HNMupMum_60' 'HNMupMup_100' 'HNMupMup_1100' 'HNMupMup_1500' 'HNMupMup_200' 'HNMupMup_40' 'HNMupMup_50' 'HNMupMup_500' 'HNMupMup_60' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTbar_tW_noHadron' 'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'TTJets_aMC' 'ttWToLNu' 'ttZToLL_M-1to10' 'WGtoLNuG' 'WgstarToLNuEE' 'WJets' 'WWTo2L2Nu' 'WWToLNuQQ' 'WWW' 'WWZ' 'WW' 'WZTo3LNu_amcatnlo' 'WZTo3LNu_powheg' 'WZZ' 'WZ' 'ZZTo4L_powheg' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ') 

declare -a ch_wa=('') 


declare -a ch_wz=('') 

declare -a hn_ll_ee=('') 
declare -a hn_ll_mm=('') 

declare -a hn_ll_em=('') 

declare -a hn_mmm=('') 

declare -a hn_ll_tchann_ee=('') 

declare -a hn_ll_tchann_mm=('') 


declare -a diboson_pythia=('WZ' 'ZZ' 'WW' 'WZTo3LNu_powheg' 'ZZTo4L_powheg' )

declare -a dy_mcatnlo=('DYJets_10to50' 'DYJets') 

declare -a dilepton_list=('DYJets_10to50' 'DYJets' 'TTJets_aMC' 'ttWToLNu' 'ttZToLL_M-1to10' 'WGtoLNuG' 'WgstarToLNuEE' 'WJets' 'WWW' 'WWZ' 'WW' 'WZTo3LNu_amcatnlo' 'WZTo3LNu_powheg' 'WZZ' 'WZ' 'ZZTo4L_powheg' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ')

declare -a trilepton_list=('DYJets_10to50' 'DYJets' 'WJets' 'WZ' 'ZZ' 'WW'  'TTJets_MG' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTbar_tW_noHadron'  'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'WZZ' 'ZZZ' 'WWW'  'WZTo3LNu_powheg' 'ZZTo4L_powheg' )

declare -a qcd=('WpWpEWKQCD') 

declare -a qcd_mu=('') 

declare -a qcd_eg=('') 


declare -a hn_mm=('WJets' 'WZ' 'ZZ' 'WW'  'TTJets_MG' 'WpWpEWK' 'WpWpQCD'  'WZZ' 'ZZZ' 'WWW'  'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'ttZ' 'ttW'  'ttH_nonbb' 'ttH_bb' 'ttbb' 'ZZZ' 'WZZ'  'VBF_HToMuMu' 'WGtoLNuG' 'WGtoLNuEE' 'WGtoLNuMM' 'ZGto2LG' )  

declare -a hn_ee=('DYJets_10to50' 'DYJets' 'WJets' 'WZ' 'ZZ' 'WW'  'TTJets_MG' 'WpWpEWK' 'WpWpQCD'  'WZZ' 'ZZZ' 'WWW'  'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'ttZ' 'ttW'  'ttH_nonbb' 'ttH_bb' 'ttbb' 'ZZZ' 'WZZ'  'VBF_HToMuMu' 'WGtoLNuG' 'WGtoLNuEE' 'WGtoLNuMM' 'ZGto2LG' )

declare -a hn_fakeee=('DYJets_10to50' 'DYJets' 'WJets'  'TTJets_MG')


declare -a singletop=('SingleTop_s' 'SingleTop_t' 'SingleTop_tW_noHadron' 'SingleTop_tW') 

