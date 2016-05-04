float BTagSFUtil::TagEfficiencyB_Vbb(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=2.2) return 0.389801; // 3312.87 0.865525
    else if (JetEta>=2) return 0.469272; // 3060.58 0.891767
    else if (JetEta>=1.8) return 0.496517; // 3707.54 0.796378
    else if (JetEta>=1.6) return 0.503316; // 4706.23 0.711365
    else if (JetEta>=1.4) return 0.488518; // 5615.71 0.651015
    else if (JetEta>=1.2) return 0.511491; // 6459.96 0.605354
    else if (JetEta>=1) return 0.547858; // 7239.39 0.565266
    else if (JetEta>=0.8) return 0.568411; // 8095.13 0.519877
    else if (JetEta>=0.6) return 0.579014; // 8676.53 0.501602
    else if (JetEta>=0.4) return 0.58771; // 9048.09 0.488122
    else if (JetEta>=0.2) return 0.586337; // 9378.28 0.479128
    else if (JetEta>=0) return 0.580928; // 9619.12 0.480929
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=2.2) return 0.458183; // 2567.98 0.984761
    else if (JetEta>=2) return 0.557934; // 2598.2 0.956594
    else if (JetEta>=1.8) return 0.602878; // 3464.23 0.811176
    else if (JetEta>=1.6) return 0.597553; // 4794.31 0.688093
    else if (JetEta>=1.4) return 0.592893; // 6163.37 0.609197
    else if (JetEta>=1.2) return 0.614187; // 7730.32 0.536055
    else if (JetEta>=1) return 0.643589; // 9031.9 0.485579
    else if (JetEta>=0.8) return 0.666967; // 10456.4 0.439089
    else if (JetEta>=0.6) return 0.677047; // 11673.4 0.407071
    else if (JetEta>=0.4) return 0.684492; // 12383.7 0.393289
    else if (JetEta>=0.2) return 0.674175; // 13135.8 0.386875
    else if (JetEta>=0) return 0.667084; // 13479.1 0.385439
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=1.8) return 0.60163; // 3778.31 0.797011
    else if (JetEta>=1.6) return 0.66042; // 2412.84 0.948194
    else if (JetEta>=1.4) return 0.650379; // 3437.13 0.79508
    else if (JetEta>=1.2) return 0.658081; // 4820.41 0.661916
    else if (JetEta>=1) return 0.693054; // 5947.54 0.575626
    else if (JetEta>=0.8) return 0.720782; // 7018.78 0.518975
    else if (JetEta>=0.6) return 0.727102; // 8107.63 0.463535
    else if (JetEta>=0.4) return 0.739818; // 8724.63 0.453486
    else if (JetEta>=0.2) return 0.731381; // 9481.23 0.434155
    else if (JetEta>=0) return 0.711462; // 9576.16 0.447479
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=1.4) return 0.632006; // 2478.95 0.964551
    else if (JetEta>=1) return 0.685249; // 3629.46 0.759506
    else if (JetEta>=0.8) return 0.730269; // 2451.91 0.864494
    else if (JetEta>=0.6) return 0.736257; // 2855.79 0.811479
    else if (JetEta>=0.4) return 0.747604; // 3139.45 0.739861
    else if (JetEta>=0.2) return 0.737834; // 3397.08 0.73966
    else if (JetEta>=0) return 0.723605; // 3555.59 0.738783
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=0.8) return 0.668194; // 2630.44 0.918414
    else if (JetEta>=0.4) return 0.750485; // 2140.21 0.947752
    else if (JetEta>=0) return 0.72445; // 2579.1 0.864687
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=0.2) return 0.66701; // 2312.74 0.997519
    else if (JetEta>=-0.2) return 0.676196; // 569.568 1.91116
  }
	

  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
  if (TaggerName=="CSVL") return 0.80;
  if (TaggerName=="CSVM") return 0.65;
	
  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;
}

float BTagSFUtil::TagEfficiencyC_Vbb(float JetPt, float JetEta){

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=1) return 0.132496; // 1367.57 0.93009
    else if (JetEta>=-0.2) return 0.169212; // 1302.01 1.04815
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=0.4) return 0.178658; // 1413.84 0.983288
    else if (JetEta>=-0.2) return 0.190477; // 381.629 1.93721
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=-0.2) return 0.199316; // 1061.43 1.20318
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=-0.2) return 0.212461; // 484.451 1.77873
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=-0.2) return 0.188104; // 302.053 2.2911
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=-0.2) return 0.170745; // 276.093 2.42804
  }
	
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
  if (TaggerName=="CSVL") return 0.35;
  if (TaggerName=="CSVM") return 0.16;
	
  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
  return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_Vbb(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=2.2) return 0.0193391; // 3926.52 0.233411
    else if (JetEta>=2) return 0.0226011; // 2983.58 0.28737
    else if (JetEta>=1.8) return 0.0206252; // 3171.73 0.24087
    else if (JetEta>=1.6) return 0.017426; // 3493.16 0.241219
    else if (JetEta>=1.4) return 0.0124284; // 3989.68 0.206318
    else if (JetEta>=1.2) return 0.0140644; // 4269.08 0.171403
    else if (JetEta>=1) return 0.0150585; // 4592.34 0.183503
    else if (JetEta>=0.8) return 0.0138728; // 4739.99 0.184979
    else if (JetEta>=0.6) return 0.0146894; // 5046.85 0.161207
    else if (JetEta>=0.4) return 0.0139665; // 5155.2 0.16652
    else if (JetEta>=0.2) return 0.0129343; // 4976.4 0.144964
    else if (JetEta>=0) return 0.0120776; // 5197.03 0.159358
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=2.2) return 0.0151139; // 2480.17 0.219764
    else if (JetEta>=2) return 0.0166174; // 1867.7 0.320375
    else if (JetEta>=1.8) return 0.0167063; // 1896.63 0.288088
    else if (JetEta>=1.6) return 0.0137907; // 2209.89 0.269375
    else if (JetEta>=1.4) return 0.00942718; // 2504.66 0.242567
    else if (JetEta>=1.2) return 0.0110074; // 2764.43 0.171736
    else if (JetEta>=1) return 0.0111269; // 2834.32 0.198252
    else if (JetEta>=0.8) return 0.0118261; // 2960.95 0.21296
    else if (JetEta>=0.6) return 0.0118322; // 2992.92 0.225598
    else if (JetEta>=0.4) return 0.0114219; // 3249.78 0.173804
    else if (JetEta>=0.2) return 0.0103338; // 3148.24 0.194008
    else if (JetEta>=0) return 0.0105485; // 3205.01 0.187751
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=2.2) return 0.0165266; // 985.459 0.45524
    else if (JetEta>=2) return 0.0199412; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0201918; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0154981; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0110714; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0107773; // 1533.19 0.248855
    else if (JetEta>=1) return 0.00979333; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0115059; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0113646; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0120611; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.00903445; // 1714.09 0.279147
    else if (JetEta>=0) return 0.00999671; // 1822.07 0.225256
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=2.2) return 0.0188961; // 985.459 0.45524
    else if (JetEta>=2) return 0.022134; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.025359; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0184453; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0110792; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0120098; // 1533.19 0.248855
    else if (JetEta>=1) return 0.0126322; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0118989; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0134999; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0131877; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.0108676; // 1714.09 0.279147
    else if (JetEta>=0) return 0.01034; // 1822.07 0.225256
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=2.2) return 0.0203755; // 985.459 0.45524
    else if (JetEta>=2) return 0.0294991; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0227884; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0179108; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.014122; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0135005; // 1533.19 0.248855
    else if (JetEta>=1) return 0.0132684; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0144882; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0124878; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0137497; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.00979649; // 1714.09 0.279147
    else if (JetEta>=0) return 0.0111134; // 1822.07 0.225256
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=2.0) return 0.0289092; // 985.459 0.45524
    else if (JetEta>=1.6) return 0.0261211; // 985.459 0.45524
    else if (JetEta>=1.4) return 0.0139931; // 1190.28 0.276026
    else if (JetEta>=1.2) return 0.0128192; // 1190.28 0.276026
    else if (JetEta>=1.) return 0.0176195; // 1359.65 0.319322
    else if (JetEta>=0.8) return 0.0172201; // 1533.19 0.248855
    else if (JetEta>=0.6) return 0.01676; // 1585.36 0.295742
    else if (JetEta>=0.4) return 0.0123744; // 1608.92 0.290273
    else if (JetEta>=0.2) return 0.0134111; // 1712.71 0.259154
    else if (JetEta>=0) return 0.0131456; // 1676.9 0.261251
  }

  
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

  if (TaggerName=="CSVL") return 0.10;
  if (TaggerName=="CSVM") return 0.02;

  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;

}
