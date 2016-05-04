float BTagSFUtil::TagEfficiencyB_tt(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=2.2) return 0.431776; // 3312.87 0.865525
    else if (JetEta>=2) return 0.520251; // 3060.58 0.891767
    else if (JetEta>=1.8) return 0.551815; // 3707.54 0.796378
    else if (JetEta>=1.6) return 0.55912; // 4706.23 0.711365
    else if (JetEta>=1.4) return 0.546121; // 5615.71 0.651015
    else if (JetEta>=1.2) return 0.56008; // 6459.96 0.605354
    else if (JetEta>=1) return 0.598579; // 7239.39 0.565266
    else if (JetEta>=0.8) return 0.625751; // 8095.13 0.519877
    else if (JetEta>=0.6) return 0.640859; // 8676.53 0.501602
    else if (JetEta>=0.4) return 0.649037; // 9048.09 0.488122
    else if (JetEta>=0.2) return 0.645236; // 9378.28 0.479128
    else if (JetEta>=0) return 0.630661; // 9619.12 0.480929
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=2.2) return 0.499163; // 2567.98 0.984761
    else if (JetEta>=2) return 0.600383; // 2598.2 0.956594
    else if (JetEta>=1.8) return 0.636589; // 3464.23 0.811176
    else if (JetEta>=1.6) return 0.640132; // 4794.31 0.688093
    else if (JetEta>=1.4) return 0.627509; // 6163.37 0.609197
    else if (JetEta>=1.2) return 0.640176; // 7730.32 0.536055
    else if (JetEta>=1) return 0.678133; // 9031.9 0.485579
    else if (JetEta>=0.8) return 0.703665; // 10456.4 0.439089
    else if (JetEta>=0.6) return 0.714493; // 11673.4 0.407071
    else if (JetEta>=0.4) return 0.723386; // 12383.7 0.393289
    else if (JetEta>=0.2) return 0.718585; // 13135.8 0.386875
    else if (JetEta>=0) return 0.703763; // 13479.1 0.385439
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=1.8) return 0.62739; // 3778.31 0.797011
    else if (JetEta>=1.6) return 0.677977; // 2412.84 0.948194
    else if (JetEta>=1.4) return 0.66756; // 3437.13 0.79508
    else if (JetEta>=1.2) return 0.678499; // 4820.41 0.661916
    else if (JetEta>=1) return 0.715106; // 5947.54 0.575626
    else if (JetEta>=0.8) return 0.739159; // 7018.78 0.518975
    else if (JetEta>=0.6) return 0.748478; // 8107.63 0.463535
    else if (JetEta>=0.4) return 0.755527; // 8724.63 0.453486
    else if (JetEta>=0.2) return 0.750824; // 9481.23 0.434155
    else if (JetEta>=0) return 0.732068; // 9576.16 0.447479
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=1.4) return 0.654704; // 2478.95 0.964551
    else if (JetEta>=1) return 0.702785; // 3629.46 0.759506
    else if (JetEta>=0.8) return 0.744916; // 2451.91 0.864494
    else if (JetEta>=0.6) return 0.755675; // 2855.79 0.811479
    else if (JetEta>=0.4) return 0.759873; // 3139.45 0.739861
    else if (JetEta>=0.2) return 0.757812; // 3397.08 0.73966
    else if (JetEta>=0) return 0.740413; // 3555.59 0.738783
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=0.8) return 0.67152; // 2630.44 0.918414
    else if (JetEta>=0.4) return 0.73819; // 2140.21 0.947752
    else if (JetEta>=0) return 0.728986; // 2579.1 0.864687
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=0.2) return 0.632771; // 2312.74 0.997519
    else if (JetEta>=-0.2) return 0.640115; // 569.568 1.91116
  }
	

  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

  if (TaggerName=="CSVL") return 0.80;
  if (TaggerName=="CSVM") return 0.65;

  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;
}

float BTagSFUtil::TagEfficiencyC_tt(float JetPt, float JetEta){

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=1) return 0.145221; // 1367.57 0.93009
    else if (JetEta>=-0.2) return 0.177793; // 1302.01 1.04815
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=0.4) return 0.187499; // 1413.84 0.983288
    else if (JetEta>=-0.2) return 0.196344; // 381.629 1.93721
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=-0.2) return 0.205806; // 1061.43 1.20318
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=-0.2) return 0.204983; // 484.451 1.77873
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=-0.2) return 0.189849; // 302.053 2.2911
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=-0.2) return 0.148689; // 276.093 2.42804
  }
	
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
  if (TaggerName=="CSVL") return 0.35;
  if (TaggerName=="CSVM") return 0.16;
	
  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
  return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_tt(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=2.2) return 0.0185911; // 3926.52 0.233411
    else if (JetEta>=2) return 0.0217914; // 2983.58 0.28737
    else if (JetEta>=1.8) return 0.0192297; // 3171.73 0.24087
    else if (JetEta>=1.6) return 0.0165699; // 3493.16 0.241219
    else if (JetEta>=1.4) return 0.0142654; // 3989.68 0.206318
    else if (JetEta>=1.2) return 0.0131913; // 4269.08 0.171403
    else if (JetEta>=1) return 0.0135599; // 4592.34 0.183503
    else if (JetEta>=0.8) return 0.0140058; // 4739.99 0.184979
    else if (JetEta>=0.6) return 0.0133894; // 5046.85 0.161207
    else if (JetEta>=0.4) return 0.0129162; // 5155.2 0.16652
    else if (JetEta>=0.2) return 0.0119575; // 4976.4 0.144964
    else if (JetEta>=0) return 0.0121921; // 5197.03 0.159358
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=2.2) return 0.0162276; // 2480.17 0.219764
    else if (JetEta>=2) return 0.0194655; // 1867.7 0.320375
    else if (JetEta>=1.8) return 0.0177188; // 1896.63 0.288088
    else if (JetEta>=1.6) return 0.0156277; // 2209.89 0.269375
    else if (JetEta>=1.4) return 0.0127609; // 2504.66 0.242567
    else if (JetEta>=1.2) return 0.0119706; // 2764.43 0.171736
    else if (JetEta>=1) return 0.0128199; // 2834.32 0.198252
    else if (JetEta>=0.8) return 0.0127229; // 2960.95 0.21296
    else if (JetEta>=0.6) return 0.0125573; // 2992.92 0.225598
    else if (JetEta>=0.4) return 0.0122285; // 3249.78 0.173804
    else if (JetEta>=0.2) return 0.0116224; // 3148.24 0.194008
    else if (JetEta>=0) return 0.0113306; // 3205.01 0.187751
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=2.2) return 0.0159678; // 985.459 0.45524
    else if (JetEta>=2) return 0.0214079; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.018388; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0156788; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0142517; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0119638; // 1533.19 0.248855
    else if (JetEta>=1) return 0.013433; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0129238; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0127614; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0129619; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.0122225; // 1714.09 0.279147
    else if (JetEta>=0) return 0.0117059; // 1822.07 0.225256
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=2.2) return 0.0205685; // 985.459 0.45524
    else if (JetEta>=2) return 0.0254834; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0221977; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0162751; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0135774; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0133676; // 1533.19 0.248855
    else if (JetEta>=1) return 0.0133178; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0135385; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0132455; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0132001; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.0120836; // 1714.09 0.279147
    else if (JetEta>=0) return 0.0129638; // 1822.07 0.225256
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=2.2) return 0.0266227; // 985.459 0.45524
    else if (JetEta>=2) return 0.0269851; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0237387; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0202981; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0149218; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0132381; // 1533.19 0.248855
    else if (JetEta>=1) return 0.0128074; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0129379; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0127955; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0124925; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.0117483; // 1714.09 0.279147
    else if (JetEta>=0) return 0.011923; // 1822.07 0.225256
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=2.0) return 0.035999; // 985.459 0.45524
    else if (JetEta>=1.6) return 0.0299099; // 985.459 0.45524
    else if (JetEta>=1.4) return 0.0173835; // 1190.28 0.276026
    else if (JetEta>=1.2) return 0.01481; // 1190.28 0.276026
    else if (JetEta>=1.) return 0.015595; // 1359.65 0.319322
    else if (JetEta>=0.8) return 0.0139058; // 1533.19 0.248855
    else if (JetEta>=0.6) return 0.01411; // 1585.36 0.295742
    else if (JetEta>=0.4) return 0.0136776; // 1608.92 0.290273
    else if (JetEta>=0.2) return 0.0119428; // 1712.71 0.259154
    else if (JetEta>=0) return 0.0124585; // 1676.9 0.261251
  }

  
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

  if (TaggerName=="CSVL") return 0.10;
  if (TaggerName=="CSVM") return 0.02;

  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;

}
