#sktree -a ChargeFlip_e -i DYJets -s SKTree_DiLepSkim -n 1
#sktree -a ChargeFlip_e -i DYJets -s SKTree_LeptonSkim -events 10000 -n 1
#sktree -a ChargeFlip_e -i DYJets -s SKTree_LeptonSkim -events 1000000 -q fastq
sktree -a ChargeFlip_e -i DYJets -s SKTree_LeptonSkim -q longq
#sktree -a HN_pair_MM -i DYJets -s SKTree_DiLepSkim -n 1
#sktree -a HN_pair_MM -i TTJets_aMC -s SKTree_DiLepSkim -n 1
#sktree -a Truth_HN_pair -i HNpair_mumu_WR5000_Zp1500_HN100 -s SKTree_LeptonSkim -n 1
#sktree -a HN_pair_MM -i HNpair_mumu_WR5000_Zp1500_HN100 -s SKTree_LeptonSkim -n 1
#sktree -a ChargeFlip_e -i HNpair_mumu_WR5000_Zp1500_HN100 -s SKTree_LeptonSkim -n 1
#sktree -a Closure_cf -S DoubleEG -s SKTree_DiLepSkim -q longq
#sktree_bkg -a Closure_cf -S DoubleEG -s SKTree_DiLepSkim -q longq 
#sktree -a Closure_cf -i DYJets -s SKTree_LeptonSkim -q fastq
#sktree -a Closure_cf -S DoubleEG -s SKTree_DiLepSkim -n 1
