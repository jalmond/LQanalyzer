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


declare -a hn_pair=('DY10to50' 'DY50plus' 'GG_HToMuMu' 'QCD_Pt-1000toInf_MuEnriched' 'QCD_Pt-120to170_EMEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-15to20_MuEnriched' 'QCD_Pt-170to300_EMEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-20to30_MuEnriched' 'QCD_Pt-300to470_MuEnriched' 'QCD_Pt-300toInf_EMEnriched' 'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-50to80_EMEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-600to800_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_EMEnriched' 'QCD_Pt-80to120_MuEnriched' 'SingleTop_s' 'SingleTop_t' 'SingleTbar_t' 'SingleTbar_tW_noHadron' 'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'TT_powheg' 'VBF_HToMuMu' 'WG' 'WJets' 'WWTo2L2Nu_powheg'  'WWW' 'WWZ'  'WZTo2L2Q_mcatnlo' 'WZTo3LNu_powheg' 'WZZ' 'WpWpEWK' 'WpWpQCD' 'ZGto2LG' 'ZZTo2L2Nu_powheg' 'ZZTo2L2Q_powheg' 'ZZTo4L_powheg' 'ZZZ'  'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ' 'DY_pt_100to250' 'DY_pt_250to400' 'DY_pt_400to650' 'DY_pt_50to100' 'DY_pt_650toinf' 'DY_pt_0to50' 'TTLL_powheg')


declare -a hn_tmp=('DY_pt_100to250' 'DY_pt_250to400' 'DY_pt_400to650' 'DY_pt_50to100' 'DY_pt_650toinf' 'DY_pt_0to50' 'TTLL_powheg') 