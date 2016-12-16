#sktree -a HN_pair_di_muon -S DoubleMuon -list dilepton_list -s SKTree_DiLepSkim -q fastq

#sktree -a HN_pair_di_muon -list dilepton_list -s SKTree_DiLepSkim -q fastq
#sktree -a HN_pair_di_muon -S DoubleMuon -fake True -s SKTree_DiLepSkim -q fastq

#sktree_bkg -a HN_pair_di_muon -list hnpair -s SKTree_LeptonSkim -q longq
#sktree -a HN_pair_di_muon -list hnpair -s SKTree_LeptonSkim -q fastq
sktree -a HN_pair_MM -list hnpair -s SKTree_LeptonSkim -q fastq  

#sktree -a Truth_HN_pair -list hnpair -s SKTree_LeptonSkim -q fastq
#sktree -a Truth_HN_pair -list hnpair -s SKTree_LeptonSkim -q longq
