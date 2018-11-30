sktree_80X  -a HN_pair_all -S DoubleEG -s SKTree_DiLepSkim -n 50 -F
sktree_80X  -a HN_pair_all -S SingleMuon -s SKTree_DiLepSkim -n 50 -F
sktree_80X  -a HN_pair_all -list hn_pair -s SKTree_DiLepSkim -n 50 -userflag FakeMC  -F
rm /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/HN_pair_all/periodBtoH/2018-11-26/Fake/*
mv /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/HN_pair_all/periodBtoH/2018-11-26/HN_pair_all_SK* /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/HN_pair_all/periodBtoH/2018-11-26/Fake/
cd /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/HN_pair_all/periodBtoH/2018-11-26/Fake/
hadd HN_pair_all_SKnonprompt_dilep_cat_v8-0-8.root *.root
mv HN_pair_all_SKnonprompt_dilep_cat_v8-0-8.root /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/HN_pair_all/periodBtoH/2018-11-26/
cd -
sktree_80X  -a HN_pair_all -list hn_pair -s SKTree_DiLepSkim -n 50 -F
sktree_80X  -a HN_pair_all -list all_sig  -n 10 -SIG True