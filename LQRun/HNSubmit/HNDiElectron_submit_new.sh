sktree -a HNDiElectron  -S DoubleEG -s SKTree_TriLepSkim 
sktree -a HNDiElectron -list hn_ee  -s SKTree_TriLepSkim
#sktree -a HNDiElectron-list qcd_eg -s SKTree_TriLepSkim
sktree -a HNDiElectron -S DoubleEG -fake True -s SKTree_TriLepSkim 
sktree -a HNDiElectron -i HN_EE_M40 -s SKTree_NoSkim
sktree -a HNDiElectron -i HN_EE_M100 -s SKTree_NoSkim
sktree -a HNDiElectron -i HN_EE_M500 -s SKTree_NoSkim
sktree -a HNDiElectron -i HN_EE_M1500 -s SKTree_NoSkim