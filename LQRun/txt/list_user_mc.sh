#!/bin/sh

########################
### SAMPLE LIST ########## 
#######################

declare -a example=("" "WW" "" "WZ")

declare -a tmplist=('WpWp_qcd_madgraph' 'ZG_llG_MCatNLO' 'ZZ_llnunu_powheg' 'ZZ_llqq_MCatNLO' 'ZZ_llll_MCatNLO' 'ZZ_llll_powheg' 'ZZ_pythia8' 'ttHnobb_Powheg' 'ttHtobb_Powheg')

declare -a hn=('DYJets_10to50'  'DYJets' 'WW' 'ZZ' 'WZ' 'TTJets_MG')

declare -a hnpair=('HNpair_mumu_WR5000_Zp400_HN100' 'HNpair_mumu_WR5000_Zp750_HN100' 'HNpair_mumu_WR5000_Zp750_HN300' 'HNpair_mumu_WR5000_Zp1500_HN100' 'HNpair_mumu_WR5000_Zp1500_HN300' 'HNpair_mumu_WR5000_Zp1500_HN700' 'HNpair_mumu_WR5000_Zp3000_HN100' 'HNpair_mumu_WR5000_Zp3000_HN300' 'HNpair_mumu_WR5000_Zp3000_HN700')

declare -a crash=('DYJets' 'TTJets_aMC' 'TT_powheg')