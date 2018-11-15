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


#declare -a all_mc=('DY10to50' 'DY50plus' 'DY_pt_0to50' 'DY_pt_100to250' 'DY_pt_250to400' 'DY_pt_400to650' 'DY_pt_50to100' 'DY_pt_650toinf' 'WJets' 'TT_powheg' 'TTLL_powheg' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTop_tW' 'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTbar_tW_noHadron' 'ZZTo4L_powheg' 'ZZTo2L2Nu_powheg' 'ZZTo2L2Q_powheg' 'WZTo1L1Nu2Q_mcatnlo' 'WZTo2L2Q_mcatnlo' 'WWTo2L2Nu_powheg' 'WWToLQQ_powheg' 'WZTo3LNu_powheg' 'WpWp_qcd' 'WpWp_ewk' 'WWW' 'WWZ' 'WZZ' 'ZZZ' 'ttW' 'ttZ' 'WGtoLNuG' 'ZGto2LG' 'ttH_bb' 'ttH_nonbb' 'GG_HToMuMu' 'VBF_HToMuMu' 'QCD_Pt-15to20_MuEnriched' 'QCD_Pt-20to30_MuEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-80to120_MuEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-300to470_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-600to800_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-1000toInf_MuEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-50to80_EMEnriched' 'QCD_Pt-80to120_EMEnriched' 'QCD_Pt-120to170_EMEnriched' 'QCD_Pt-170to300_EMEnriched' 'QCD_Pt-300toInf_EMEnriched' 
declare -a all_user_mc=('SingleTbar_t' 'WG' 'ttH_nonbb' 'ttH_bb' 'ttZ' 'ttW')

