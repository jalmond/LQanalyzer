#!/bin/sh

########################
### SAMPLE LIST ########## 
#######################
declare -a new_list=('ZToEE_NNPDF30_13TeV-powheg_M_120_200'
,'ZToEE_NNPDF30_13TeV-powheg_M_1400_2300'
,'ZToEE_NNPDF30_13TeV-powheg_M_200_400'
,'ZToEE_NNPDF30_13TeV-powheg_M_2300_3500'
,'ZToEE_NNPDF30_13TeV-powheg_M_3500_4500'
,'ZToEE_NNPDF30_13TeV-powheg_M_400_800'
,'ZToEE_NNPDF30_13TeV-powheg_M_4500_6000'
,'ZToEE_NNPDF30_13TeV-powheg_M_50_120'
,'ZToEE_NNPDF30_13TeV-powheg_M_6000_Inf'
,'ZToEE_NNPDF30_13TeV-powheg_M_800_1400'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_120_200'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_1400_2300'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_200_400'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_2300_3500'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_3500_4500'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_400_800'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_4500_6000'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_50_120'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_6000_Inf'
,'ZToMuMu_NNPDF30_13TeV-powheg_M_800_1400')


declare -a tchannel_hn=('HNMoriondLL_Tchannel_EpEp_100' 'HNMoriondLL_Tchannel_EpEp_200' 'HNMoriondLL_Tchannel_EpEp_500' 'HNMoriondLL_Tchannel_EpEp_1100' 'HNMoriondLL_Tchannel_MupMup_100' 'HNMoriondLL_Tchannel_MupMup_200' 'HNMoriondLL_Tchannel_MupMup_500' 'HNMoriondLL_Tchannel_MupMup_1100' 'HNMumMum_40' 'HNMumMum_50' 'HNMumMum_200' 'HNMumMum_500' 'HNMumMum_1500'  'HNEmEm_40' 'HNEmEm_50' 'HNEmEm_200' 'HNEmEm_500' 'HNEmEm_1500'  'HNMupMup_40' 'HNMupMup_50' 'HNMupMup_200' 'HNMupMup_500' 'HNMupMup_1500' 'HNMupMup_100' 'HNMupMup_700' 'HNMupMup_1000' )
declare -a  mc_conv=('ZGto2LG' 'WGtoLNuG' 'TG' 'TTG' 'WZG' 'WWG' )

declare -a trilep_fake_bkg_short=(
'DYJets_10to50'
'SingleTop_s' 'SingleTop_t' 'SingleTbar_t' 'SingleTop_tW' 'SingleTbar_tW'
'WZ' 'ZZ' 'WW'
'ZGto2LG' 'WGtoLNuG'
)

declare -a  DY=('DYJets' 'DYJets_MG' 'DYtoEE')
declare -a trilep_fake_bkg_long=('DYJets' 'WJets' 'TT_powheg')

declare -a  qcd_mu_prompt=('QCD_Pt-1000toInf_MuEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-15to20_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-20to30_MuEnriched' 'QCD_Pt-300to470_MuEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 
'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-600to800_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_MuEnriched' 'TT_powheg' 'WJets'  'DYJets')
declare -a hnfail=('HNMumEp_50' 'HNMumEp_500' 'HNMumEp_60' 'HNMumMum_100' 'HNMumMum_1100' 'HNMumMum_1500' 'HNMumMum_200' 'HNMumMum_40' 'HNMumMum_50' 'HNMumMum_500' 'HNMumMum_60' 'HNMoriondLL_Tchannel_MumMum_100' 'HNMoriondLL_Tchannel_MumMum_1100' 'HNMoriondLL_Tchannel_MumMum_200' 'HNMoriondLL_Tchannel_MumMum_500' 'HNMumMup_100' 'HNMumMup_1100' 'HNMumMup_1500' 'HNMumMup_200' 'HNMumMup_40' 'HNMumMup_50' 'HNMumMup_500' 'HNMumMup_60' 'HNMupEm_100' 'HNMupEm_1100' 'HNMupEm_1500' 'HNMupEm_200' 'HNMupEm_40' 'HNMupEm_50' 'HNMupEm_500' 'HNMupEm_60' 'HNMupEp_100')

declare -a dilepton_list2=('DYJets_10to50' 'DYJets' 'WJets' 'WpWpEWK' 'WpWpQCD' 'TT_powheg'  'SingleTop_s' 'SingleTbar_t' 'SingleTop_t'  'SingleTbar_tW' 'SingleTop_tW' 'WWW' 'ttW' 'ttZ' 'ttH_nonbb' 'ttH_bb' 'ZZZ' 'WZZ' 'WWZ' 'VBF_HToMuMu' 'WGtoLNuG'  'ZGto2LG' 'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'WWTo2L2Nu' 'WWToLNuQQ' 'TG' 'TTG' 'ggHtoWW' 'ggHtoZZ' 'vbfHtoWW' 'tZq'  'ttZToLL_M-1to10' 'WZG' 'WWG' 'ggZZto4e' 'ttWToLNu' 'ttZToLL_M-10'  'WZto2L2Q_amcatnlo' 'ZZTo2L2Nu_Powheg' 'ZZTo2L2Q_Powheg' 'ggZZto2e2mu' 'ggZZto2mu2nu' 'ggZZto2mu2tau'  'ggZZto4mu' 'ggWWto2L2Nu' 'ww_ds' 'ZZTo4L_amcatnlo' 'WZ' 'WW' 'ZZ' 'TTJets_aMC') 

declare -a dilepton_list3=('DYJets_10to50' 'DYJets' 'WJets' 'TT_powheg' 'WpWpEWK' 'WpWpQCD' 'WWW' 'ttW' 'ttZ' 'ttH_nonbb' 'ttH_bb' 'ZZZ' 'WZZ' 'WWZ' 'VBF_HToMuMu' 'WGtoLNuG'  'ZGto2LG' 'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'TG' 'TTG' 'ggHtoWW' 'ggHtoZZ' 'vbfHtoWW' 'tZq'  'ttZToLL_M-1to10' 'WZG' 'WWG'  'ttWToLNu' 'ttZToLL_M-10'  'WZto2L2Q_amcatnlo'  'ww_ds' 'ZZTo4L_amcatnlo')

declare -a qcd_mm=('QCD_Pt-1000toInf_MuEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-15to20_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-20to30_MuEnriched' 'QCD_Pt-300to470_MuEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-600to800_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_MuEnriched' )



declare -a qcd_ee=('qcd_15to20_bctoe' 'qcd_170to250_bctoe' 'qcd_20to30_bctoe' 'qcd_250toinf_bctoe' 'qcd_30to80_bctoe' 'qcd_80to170_bctoe' 'QCD_Pt-120to170_EMEnriched' 'QCD_Pt-170to300_EMEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-300toInf_EMEnriched'  'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-50to80_EMEnriched' 'QCD_Pt-80to120_EMEnriched')
declare -a qcd_eemm=('qcd_15to20_bctoe' 'qcd_170to250_bctoe' 'qcd_20to30_bctoe' 'qcd_250toinf_bctoe' 'qcd_30to80_bctoe' 'qcd_80to170_bctoe' 'QCD_Pt-120to170_EMEnriched' 'QCD_Pt-170to300_EMEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-300toInf_EMEnriched'  'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-50to80_EMEnriched' 'QCD_Pt-80to120_EMEnriched' 'WJets' 'TTJets_aMC' 'QCD_Pt-1000toInf_MuEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-15to20_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-20to30_MuEnriched' 'QCD_Pt-300to470_MuEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-600to800_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_MuEnriched' 'TT_powheg')

declare -a hn_ll_mm_lm=( 'HNMupMup_40' 'HNMupMup_50' 'HNMupMup_60' 'HNMupMup_70' 'HNMupMup_80'  'HNMumMum_40' 'HNMumMum_50' 'HNMumMum_60' 'HNMumMum_70' 'HNMumMum_80')
declare -a hn_ll_mm_hm=( 'HNMumMum_100' 'HNMumMum_1000' 'HNMumMum_1100' 'HNMumMum_1200' 'HNMumMum_125' 'HNMumMum_1300' 'HNMumMum_1400' 'HNMumMum_150' 'HNMumMum_1500' 'HNMumMum_200' 'HNMumMum_250' 'HNMumMum_300' 'HNMumMum_400' 'HNMumMum_500' 'HNMumMum_600' 'HNMumMum_700'  'HNMumMum_800' 'HNMumMum_90' 'HNMumMum_900' 'HNDilepton_MuMu_Tchannel_M300'  'HNDilepton_MuMu_Tchannel_M600'  'HNDilepton_MuMu_Tchannel_M800'  'HNDilepton_MuMu_Tchannel_M1000'  'HNDilepton_MuMu_Tchannel_M1200' 'HNMupMup_100' 'HNMupMup_1000' 'HNMupMup_1100' 'HNMupMup_1200' 'HNMupMup_125' 'HNMupMup_1300' 'HNMupMup_1400' 'HNMupMup_150' 'HNMupMup_1500' 'HNMupMup_200' 'HNMupMup_250' 'HNMupMup_300' 'HNMupMup_400' 'HNMupMup_500' 'HNMupMup_600' 'HNMupMup_700'  'HNMupMup_800' 'HNMupMup_90'   'HNMupMup_900' )



declare -a hn_ll_ee_lm=( 'HNEpEp_40' 'HNEpEp_50' 'HNEpEp_60' 'HNEpEp_70' 'HNEpEp_80'  'HNEmEm_40' 'HNEmEm_50' 'HNEmEm_60' 'HNEmEm_70' 'HNEmEm_80')
declare -a hn_ll_ee_hm=( 'HNEmEm_100' 'HNEmEm_1000' 'HNEmEm_1100' 'HNEmEm_1200' 'HNEmEm_125' 'HNEmEm_1300' 'HNEmEm_1400' 'HNEmEm_150' 'HNEmEm_1500' 'HNEmEm_200' 'HNEmEm_250' 'HNEmEm_300' 'HNEmEm_400' 'HNEmEm_500' 'HNEmEm_600' 'HNEmEm_700'  'HNEmEm_800' 'HNEmEm_90' 'HNEmEm_900' 'HNDilepton_EE_Tchannel_M300'  'HNDilepton_EE_Tchannel_M600'  'HNDilepton_EE_Tchannel_M800'  'HNDilepton_EE_Tchannel_M1000'  'HNDilepton_EE_Tchannel_M1200' 'HNEpEp_100' 'HNEpEp_1000' 'HNEpEp_1100' 'HNEpEp_1200' 'HNEpEp_125' 'HNEpEp_1300' 'HNEpEp_1400' 'HNEpEp_150' 'HNEpEp_1500' 'HNEpEp_200' 'HNEpEp_250' 'HNEpEp_300' 'HNEpEp_400' 'HNEpEp_500' 'HNEpEp_600' 'HNEpEp_700'  'HNEpEp_800' 'HNEpEp_90'   )

declare -a hn_ll_ee_tchan=( 'HNDilepton_EE_Tchannel_M300'   'HNDilepton_EE_Tchannel_M600' 'HNDilepton_EE_Tchannel_M800' 'HNDilepton_EE_Tchannel_M1000' 'HNDilepton_EE_Tchannel_M1200' 'HNDilepton_EE_Tchannel_M1500')
declare -a hn_ll_mm_tchan=( 'HNDilepton_MuMu_Tchannel_M300'   'HNDilepton_MuMu_Tchannel_M600' 'HNDilepton_MuMu_Tchannel_M800' 'HNDilepton_MuMu_Tchannel_M1000' 'HNDilepton_MuMu_Tchannel_M1200' 'HNDilepton_MuMu_Tchannel_M1500')


declare -a tmplist=('DYJets_MG_10to50_TrigInfoSample' 'DYJets_MG_TrigInfoSample' 'TT_powheg_TrigInfoSample')



declare -a tmpall_mc=('TTJets_aMC' 'LowStat_WJets' 'WW'  'WZ' 'ZZ' 'LowStat_DYJets' 'DYJets_10to50' )

declare -a hn=('DYJets_10to50'  'DYJets' 'TT_powheg' 'WJets' 'WGtoLNuG'  'ZGto2LG' 'qcd_15to20_bctoe' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-20to30_MuEnriched')
declare -a hn_fake=('DYJets' 'TT_powheg' 'WJets' 'qcd_15to20_bctoe' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-20to30_MuEnriched' 'QCD_DoubleEMEnriched_30-40_mgg80toinf' 'QCD_DoubleEMEnriched_30-inf_mgg40to80' 'QCD_DoubleEMEnriched_40-inf_mgg80toinf')

declare -a pu_dilepton_list=('DYJets_10to50' 'DYJets' 'WJets' 'TT_powheg'  'SingleTop_s' 'SingleTbar_t' 'SingleTop_t'  'SingleTbar_tW' 'SingleTop_tW' 'WGtoLNuG'  'ZGto2LG' 'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'DYJets_MG_10to50' 'DYJets_MG' 'TTJets_aMC' )

declare -a hntmp=('TTTT' 'TG' 'TTG' 'ttWToLNu' 'ttZToLL_M-1to10' 'ttZToLL_M-10'  'tZq' 'ggHtoWW' 'ggHtoZZ' 'WWG' 'WZG' 'WZto2L2Q_amcatnlo' 'ZZTo2L2Nu_Powheg' 'ZZTo2L2Q_Powheg' 'ggZZto2e2mu' 'ggZZto2e2nu' 'ggZZto2e2tau'  'ggZZto4e' 'ggWWto2L2Nu' 'ww_ds'  )

declare -a hn_eetmp=('DYJets_10to50' 'DYJets' 'WJets' 'WpWpEWK' 'WpWpQCD' 'TT_powheg'  'SingleTop_s' 'SingleTbar_t' 'SingleTop_t'  'SingleTbar_tW' 'SingleTop_tW' 'WWW' 'ttW' 'ttZ' 'ttH_nonbb' 'ttH_bb' 'ZZZ' 'WZZ'  'VBF_HToMuMu' 'WGtoLNuG'  'ZGto2LG' 'WZTo3LNu_powheg' 'ZZTo4L_powheg'  'WWTo2L2Nu' 'WWToLNuQQ' 'QCD_DoubleEMEnriched_30-40_mgg80toinf' 'QCD_DoubleEMEnriched_30-inf_mgg40to80' 'QCD_DoubleEMEnriched_40-inf_mgg80toinf' 'TG' 'TTG' 'ttWToLNu' 'ttZToLL_M-1to10' 'ttZToLL_M-10'  'tZq' 'ggHtoWW' 'ggHtoZZ' 'WWG' 'WZG' 'WZto2L2Q_amcatnlo' 'ZZTo2L2Nu_Powheg' 'ZZTo2L2Q_Powheg' 'ggZZto2e2mu' 'ggZZto2e2nu' 'ggZZto2e2tau'  'ggZZto4e' 'ggWWto2L2Nu' 'ww_ds'  )

declare -a hn_mm_all=('DYJets_10to50' 'DYJets' 'WJets' 'WpWpEWK' 'WpWpQCD' 'TT_powheg'  'SingleTop_s' 'SingleTbar_t' 'SingleTop_t'  'SingleTbar_tW' 'SingleTop_tW' 'WWW' 'ttW' 'ttZ' 'ttH_nonbb' 'ttH_bb' 'ZZZ' 'WZZ'  'VBF_HToMuMu' 'WGtoLNuG'  'ZGto2LG' 'WZTo3LNu_powheg' 'ZZTo4L_powheg'  'WWTo2L2Nu' 'WWToLNuQQ' 'TG' 'TTG' 'ttWToLNu' 'ttZToLL_M-1to10' 'ttZToLL_M-10'  'tZq' 'ggHtoWW' 'ggHtoZZ' 'WWG' 'WZG' 'WZto2L2Q_amcatnlo' 'ZZTo2L2Nu_Powheg' 'ZZTo2L2Q_Powheg' 'ggZZto2e2mu' 'ggZZto2mu2nu' 'ggZZto2mu2tau'  'ggZZto4mu' 'ggWWto2L2Nu' 'ww_ds'  )


declare -a sktmp=('WJets' 'TT_powheg')
declare -a vv=('WZTo3LNu_powheg' 'ZZTo4L_powheg' 'WGtoLNuG'  'ZGto2LG' 'ZZTo2L2Nu_Powheg' 'ZZTo2L2Q_Powheg' 'ggZZto2e2mu' 'ggZZto2e2nu' 'ggZZto2e2tau'  'ggZZto4e' 'ggWWto2L2Nu' 'ww_ds' 'TG' 'TTG' 'ttWToLNu')

declare -a hn_ee_sig=('WpWpEWK' 'WpWpQCD'  'ZZZ' 'WZZ'  'ww_ds'  'ggZZto4e' 'WZTo3LNu_powheg' 'ZZTo4L_powheg'  'ggHtoZZ'  'WWG' 'WZG'    'ttWToLNu' 'ttZToLL_M-1to10' 'ttZToLL_M-10'  'tZq' 'ggHtoWW' )
declare -a hn_ee_sigcf=('DYJets' 'TT_powheg' 'WWTo2L2Nu' )

declare -a hn_ee_type=('DYJets' 'TT_powheg' 'WJets' 'ZGto2LG' 'QCD_Pt-30to50_EMEnriched')


declare -a tmp=(
'DYJets_MG'
'GG_HToMuMu' 
'SingleTop_t'
'TTJets_aMC'
'TTLL_powheg'
'ttZToLL_M-10'
'WWTo2L2Nu_DS'
'ZGto2LG' )

declare -a tmp2=(
'HNEpMup_100' 
'HNEpMup_1100' 
'HNEpMup_1500' 
'HNEpMup_200' 
'HNEpMup_40' 
'HNEpMup_500' 
'HNEpMup_50' 
'HNEpMup_60' 
'HNMoriondLL_Tchannel_EpMup_100' 
'HNMoriondLL_Tchannel_EpMup_1100' 
'HNMoriondLL_Tchannel_EpMup_200' 
'HNMoriondLL_Tchannel_EpMup_500' 
'HN_MuMuMu_1000'
'HN_MuMuMu_10'
'HN_MuMuMu_150'
'HN_MuMuMu_20'
'HN_MuMuMu_200'
 )

declare -a new_list=('SingleTop_t' )
