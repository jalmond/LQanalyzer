sktree -a HNDiElectron  -S DoubleEG -s SKTree_DiLepSkim  -n 100
sktree -a HNDiElectron -list dilepton_list  -s SKTree_DiLepSkim -n 100
sktree -a HNDiElectron -list qcd_eg -s SKTree_TriLepSkim -n 100
sktree -a HNDiElectron -S DoubleEG -fake True -s SKTree_DiLepSkim  -n 100
sktree -a HNDiElectron  -S DoubleMuon -s SKTree_DiLepSkim  -n 100