sktree -a SKTreeValidation -S DoubleMuon  -list dilepton_list -s SKTree_DiLepSkim -n 15

# above line is same as the follwing 6 lines together
#sktree -a ExampleAnalyzerDiMuon -list dy_mcatnlo -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerDiMuon -list diboson_pythia -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerDiMuon -list singletop -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerDiMuon -i TT_MG5  -s SKTree_DiLepSkim -n 15 
#sktree -a ExampleAnalyzerDiMuon -i WJets_MCatNLO -s SKTree_DiLepSkim -n 15
#sktree -a ExampleAnalyzerDiMuon  -S DoubleMuon  -s SKTree_DiLepSkim -n 15