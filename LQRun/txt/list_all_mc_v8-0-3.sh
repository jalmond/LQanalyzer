#!/bin/sh

########################
### SAMPLE LIST ########## 
#######################


source ${LQANALYZER_DIR}/LQRun/txt/list_user_mc.sh


declare -a input_samples=('WZ')

declare -a all_mc=('DYJets_10to50' 'DYJets' 'GG_HToMuMu' 'QCD_Pt-120to170_EMEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-50to80_EMEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_MuEnriched' 'SingleTbar_t' 'SingleTbar_tW' 'TTJets_aMC' 'TTLL_powheg' 'TTLJ_powheg' 'TT_powheg' 'VBF_HToMuMu' 'WJets' 'WJets_MG' 'WWW' 'WWZ' 'WW' 'WZTo3LNu_powheg' 'WZZ' 'WZ' 'WpWpEWK' 'WpWpQCD' 'ZZTo4L_powheg' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ') 

declare -a mc_noqcd=('DYJets_10to50' 'DYJets' 'GG_HToMuMu' 'SingleTbar_t' 'SingleTbar_tW' 'TTJets_aMC' 'TTLL_powheg' 'TTLJ_powheg' 'TT_powheg' 'VBF_HToMuMu' 'WJets' 'WJets_MG' 'WWW' 'WWZ' 'WW' 'WZTo3LNu_powheg' 'WZZ' 'WZ' 'WpWpEWK' 'ZZTo4L_powheg' 'ZZZ' 'ZZ' 'ttH_nonbb' 'ttH_bb' 'ttW' 'ttZ') 

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

declare -a dilepton_list=('DYJets_10to50' 'DYJets' 'WJets' 'WpWpEWK' 'WpWpQCD'  'WZ' 'ZZ' 'WW'  'TT_powheg'  'SingleTbar_t'   'SingleTbar_tW' 'WWW' 'ttW' 'ttZ' 'ttH_nonbb' 'ttH_bb' 'ZZZ' 'WZZ'  'VBF_HToMuMu')
declare -a trilepton_list=('DYJets_10to50' 'DYJets' 'WJets' 'WZ' 'ZZ' 'WW'  'TTJets_MG' 'SingleTop_s' 'SingleTbar_t' 'SingleTop_t' 'SingleTbar_tW_noHadron'  'SingleTbar_tW' 'SingleTop_tW_noHadron' 'SingleTop_tW' 'WZZ' 'ZZZ' 'WWW'  'WZTo3LNu_powheg' 'ZZTo4L_powheg' )

declare -a qcd=('QCD_Pt-120to170_EMEnriched' 'QCD_Pt-120to170_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-50to80_EMEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_MuEnriched' 'WpWpQCD') 

declare -a qcd_mu=('QCD_Pt-120to170_MuEnriched' 'QCD_Pt-170to300_MuEnriched' 'QCD_Pt-30to50_MuEnriched' 'QCD_Pt-470to600_MuEnriched' 'QCD_Pt-50to80_MuEnriched' 'QCD_Pt-800to1000_MuEnriched' 'QCD_Pt-80to120_MuEnriched') 

declare -a qcd_eg=('QCD_Pt-120to170_EMEnriched' 'QCD_Pt-20to30_EMEnriched' 'QCD_Pt-30to50_EMEnriched' 'QCD_Pt-50to80_EMEnriched') 


declare -a hn_mm=('WJets' 'WZ' 'ZZ' 'WW'  'TTJets_MG' 'WpWpEWK' 'WpWpQCD'  'WZZ' 'ZZZ' 'WWW'  'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'ttZ' 'ttW'  'ttH_nonbb' 'ttH_bb' 'ttbb' 'ZZZ' 'WZZ'  'VBF_HToMuMu' 'WGtoLNuG' 'WGtoLNuEE' 'WGtoLNuMM' 'ZGto2LG' )  

declare -a hn_ee=('DYJets_10to50' 'DYJets' 'WJets' 'WZ' 'ZZ' 'WW'  'TTJets_MG' 'WpWpEWK' 'WpWpQCD'  'WZZ' 'ZZZ' 'WWW'  'WZTo3LNu_powheg' 'ZZTo4L_powheg' 'ttZ' 'ttW'  'ttH_nonbb' 'ttH_bb' 'ttbb' 'ZZZ' 'WZZ'  'VBF_HToMuMu' 'WGtoLNuG' 'WGtoLNuEE' 'WGtoLNuMM' 'ZGto2LG' )

declare -a hn_fakeee=('DYJets_10to50' 'DYJets' 'WJets'  'TTJets_MG')


declare -a singletop=('') 

