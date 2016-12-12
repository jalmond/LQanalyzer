#sktree -a HN_pair_di_muon -S DoubleMuon -list dilepton_list -s SKTree_DiLepSkim -q fastq
#sktree_bkg -a HN_pair_di_muon -list dilepton_list -s SKTree_DiLepSkim -q longq
#sktree_bkg -a HN_pair_di_muon -S DoubleMuon -fake True -s SKTree_DiLepSkim -q longq
#sktree_bkg -a HN_pair_di_muon -list hnpair -s SKTree_LeptonSkim -q longq
#sktree -a HN_pair_di_muon -i HNpair_mumu_WR5000_Zp1500_HN700 -s SKTree_LeptonSkim -n 1
sktree -a Truth_HN_pair -i HNpair_mumu_WR5000_Zp1500_HN100 -s SKTree_LeptonSkim -n 1
#sktree -a ExampleAnalyzerDiMuon -S DoubleMuon -list dilepton_list -s SKTree_DiLepSkim -q fastq
#sktree -a ExampleAnalyzerDiMuon -S DoubleMuon -fake True -s SKTree_DiLepSkim -q fastq
#sktree -a ExampleAnalyzerDiMuon -list hnpair -s SKTree_LeptonSkim -q fastq
