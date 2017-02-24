sktree -a SKTreeValidation -list hn -s SKTree_DiLepSkim -n 100
#sktree -a SKTreeValidation -list qcd_mu -s SKTree_LeptonSkim -n 100
#sktree -a SKTreeValidation -list qcd_eg -s SKTree_LeptonSkim -n 100
#sktree -a SKTreeValidation -S SingleMuon  -s SKTree_LeptonSkim -n 100
#sktree -a SKTreeValidation -S SingleElectron  -s SKTree_LeptonSkim -n 100
#sktree -a SKTreeValidation -S DoubleEG  -s SKTree_DiLepSkim -n 100
sktree -a SKTreeValidation -S DoubleMuon  -s SKTree_DiLepSkim -n 100
#sktree -a SKTreeValidation -S MuonEG  -s SKTree_DiLepSkim -n 100
#sktree -a SKTreeValidation -S DoubleEG -fake True   -s SKTree_DiLepSkim -n 100
#sktree -a SKTreeValidation -S SingleElectron -fake True  -s SKTree_LeptonSkim -n 100
#sktree -a SKTreeValidation -S SingleMuon  -fake True -s SKTree_LeptonSkim -n 100
#sktree -a SKTreeValidation -S DoubleMuon  -fake True -s SKTree_DiLepSkim -n 100
#sktree -a SKTreeValidation -S MuonEG  -fake True  -s SKTree_DiLepSkim -n 100
