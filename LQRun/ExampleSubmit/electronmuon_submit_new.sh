sktree -a ExampleAnalyzerElectronMuon -S MuonEG  -list dilepton_list -s SKTree_DiLepSkim -n 15

# above line is same as the follwing 6 lines together
#sktree -a ExampleAnalyzerElectronMuon -list dy_mcatnlo -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerElectronMuon -list diboson_pythia -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerElectronMuon -list singletop -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerElectronMuon -i TT_MG5  -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerElectronMuon -i WJets_MCatNLO -s SKTree_DiLepSkim -n 15
#sktree -a ExampleAnalyzerElectronMuon  -S MuonEG  -s SKTree_DiLepSkim -n 15