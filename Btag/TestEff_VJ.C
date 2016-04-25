float BTagSFUtil::TagEfficiencyB_VJ(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=2.2) return 0.393517; // 3312.87 0.865525
    else if (JetEta>=2) return 0.473057; // 3060.58 0.891767
    else if (JetEta>=1.8) return 0.500391; // 3707.54 0.796378
    else if (JetEta>=1.6) return 0.499211; // 4706.23 0.711365
    else if (JetEta>=1.4) return 0.461049; // 5615.71 0.651015
    else if (JetEta>=1.2) return 0.496515; // 6459.96 0.605354
    else if (JetEta>=1) return 0.511342; // 7239.39 0.565266
    else if (JetEta>=0.8) return 0.559442; // 8095.13 0.519877
    else if (JetEta>=0.6) return 0.566381; // 8676.53 0.501602
    else if (JetEta>=0.4) return 0.58055; // 9048.09 0.488122
    else if (JetEta>=0.2) return 0.556527; // 9378.28 0.479128
    else if (JetEta>=0) return 0.575089; // 9619.12 0.480929
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=2.2) return 0.439664; // 2567.98 0.984761
    else if (JetEta>=2) return 0.596937; // 2598.2 0.956594
    else if (JetEta>=1.8) return 0.542924; // 3464.23 0.811176
    else if (JetEta>=1.6) return 0.565803; // 4794.31 0.688093
    else if (JetEta>=1.4) return 0.557195; // 6163.37 0.609197
    else if (JetEta>=1.2) return 0.630456; // 7730.32 0.536055
    else if (JetEta>=1) return 0.637703; // 9031.9 0.485579
    else if (JetEta>=0.8) return 0.656166; // 10456.4 0.439089
    else if (JetEta>=0.6) return 0.658847; // 11673.4 0.407071
    else if (JetEta>=0.4) return 0.676817; // 12383.7 0.393289
    else if (JetEta>=0.2) return 0.693585; // 13135.8 0.386875
    else if (JetEta>=0) return 0.669588; // 13479.1 0.385439
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=1.8) return 0.597695; // 3778.31 0.797011
    else if (JetEta>=1.6) return 0.579301; // 2412.84 0.948194
    else if (JetEta>=1.4) return 0.558531; // 3437.13 0.79508
    else if (JetEta>=1.2) return 0.667429; // 4820.41 0.661916
    else if (JetEta>=1) return 0.729936; // 5947.54 0.575626
    else if (JetEta>=0.8) return 0.716257; // 7018.78 0.518975
    else if (JetEta>=0.6) return 0.756758; // 8107.63 0.463535
    else if (JetEta>=0.4) return 0.749028; // 8724.63 0.453486
    else if (JetEta>=0.2) return 0.737463; // 9481.23 0.434155
    else if (JetEta>=0) return 0.748611; // 9576.16 0.447479
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=1.4) return 0.592737; // 2478.95 0.964551
    else if (JetEta>=1) return 0.646143; // 3629.46 0.759506
    else if (JetEta>=0.8) return 0.643144; // 2451.91 0.864494
    else if (JetEta>=0.6) return 0.765952; // 2855.79 0.811479
    else if (JetEta>=0.4) return 0.737985; // 3139.45 0.739861
    else if (JetEta>=0.2) return 0.673536; // 3397.08 0.73966
    else if (JetEta>=0) return 0.71824; // 3555.59 0.738783
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=0.8) return 0.576489; // 2630.44 0.918414
    else if (JetEta>=0.4) return 0.732623; // 2140.21 0.947752
    else if (JetEta>=0) return 0.707676; // 2579.1 0.864687
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=0.2) return 0.621454; // 2312.74 0.997519
    else if (JetEta>=-0.2) return 0.52219; // 569.568 1.91116
  }
	

  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
  if (TaggerName=="CSVL") return 0.80;
  if (TaggerName=="CSVM") return 0.65;
	
  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;
}

float BTagSFUtil::TagEfficiencyC_VJ(float JetPt, float JetEta){

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=1) return 0.130409; // 1367.57 0.93009
    else if (JetEta>=-0.2) return 0.163561; // 1302.01 1.04815
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=0.4) return 0.177409; // 1413.84 0.983288
    else if (JetEta>=-0.2) return 0.195478; // 381.629 1.93721
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=-0.2) return 0.198101; // 1061.43 1.20318
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=-0.2) return 0.19401; // 484.451 1.77873
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=-0.2) return 0.181797; // 302.053 2.2911
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=-0.2) return 0.155478; // 276.093 2.42804
  }
	
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
  if (TaggerName=="CSVL") return 0.35;
  if (TaggerName=="CSVM") return 0.16;
	
  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
  return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_VJ(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
    if (JetEta>=2.2) return 0.0171079; // 3926.52 0.233411
    else if (JetEta>=2) return 0.0214181; // 2983.58 0.28737
    else if (JetEta>=1.8) return 0.0206121; // 3171.73 0.24087
    else if (JetEta>=1.6) return 0.0169728; // 3493.16 0.241219
    else if (JetEta>=1.4) return 0.0105877; // 3989.68 0.206318
    else if (JetEta>=1.2) return 0.0129092; // 4269.08 0.171403
    else if (JetEta>=1) return 0.0131639; // 4592.34 0.183503
    else if (JetEta>=0.8) return 0.0130093; // 4739.99 0.184979
    else if (JetEta>=0.6) return 0.0119475; // 5046.85 0.161207
    else if (JetEta>=0.4) return 0.011873; // 5155.2 0.16652
    else if (JetEta>=0.2) return 0.0107918; // 4976.4 0.144964
    else if (JetEta>=0) return 0.0100366; // 5197.03 0.159358
  } else if (50<=JetPt && JetPt<80) {
    if (JetEta>=2.2) return 0.0137067; // 2480.17 0.219764
    else if (JetEta>=2) return 0.0173486; // 1867.7 0.320375
    else if (JetEta>=1.8) return 0.0167777; // 1896.63 0.288088
    else if (JetEta>=1.6) return 0.0135934; // 2209.89 0.269375
    else if (JetEta>=1.4) return 0.00801126; // 2504.66 0.242567
    else if (JetEta>=1.2) return 0.010093; // 2764.43 0.171736
    else if (JetEta>=1) return 0.010704; // 2834.32 0.198252
    else if (JetEta>=0.8) return 0.0106953; // 2960.95 0.21296
    else if (JetEta>=0.6) return 0.0101367; // 2992.92 0.225598
    else if (JetEta>=0.4) return 0.00976804; // 3249.78 0.173804
    else if (JetEta>=0.2) return 0.00935602; // 3148.24 0.194008
    else if (JetEta>=0) return 0.00879571; // 3205.01 0.187751
  } else if (80<=JetPt && JetPt<120) {
    if (JetEta>=2.2) return 0.0129702; // 985.459 0.45524
    else if (JetEta>=2) return 0.0195447; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0187154; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.014821; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0108399; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.010348; // 1533.19 0.248855
    else if (JetEta>=1) return 0.0110243; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0101485; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.00837254; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.00946029; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.00866376; // 1714.09 0.279147
    else if (JetEta>=0) return 0.00872727; // 1822.07 0.225256
  } else if (120<=JetPt && JetPt<160) {
    if (JetEta>=2.2) return 0.0167331; // 985.459 0.45524
    else if (JetEta>=2) return 0.0300645; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0213519; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0155741; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0117756; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0104727; // 1533.19 0.248855
    else if (JetEta>=1) return 0.00958556; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0121174; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.013209; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.0122699; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.0092179; // 1714.09 0.279147
    else if (JetEta>=0) return 0.010638; // 1822.07 0.225256
  } else if (160<=JetPt && JetPt<210) {
    if (JetEta>=2.2) return 0.0337587; // 985.459 0.45524
    else if (JetEta>=2) return 0.018266; // 985.459 0.45524
    else if (JetEta>=1.8) return 0.0181895; // 1190.28 0.276026
    else if (JetEta>=1.6) return 0.0160131; // 1190.28 0.276026
    else if (JetEta>=1.4) return 0.0170575; // 1359.65 0.319322
    else if (JetEta>=1.2) return 0.0144286; // 1533.19 0.248855
    else if (JetEta>=1) return 0.0115932; // 1585.36 0.295742
    else if (JetEta>=0.8) return 0.0108183; // 1608.92 0.290273
    else if (JetEta>=0.6) return 0.0095317; // 1712.71 0.259154
    else if (JetEta>=0.4) return 0.00975015; // 1676.9 0.261251
    else if (JetEta>=0.2) return 0.0137586; // 1714.09 0.279147
    else if (JetEta>=0) return 0.010583; // 1822.07 0.225256
  } else if (210<=JetPt && JetPt<100000) {
    if (JetEta>=2.0) return 0.0424889; // 985.459 0.45524
    else if (JetEta>=1.6) return 0.0223253; // 985.459 0.45524
    else if (JetEta>=1.4) return 0.019886; // 1190.28 0.276026
    else if (JetEta>=1.2) return 0.02124; // 1190.28 0.276026
    else if (JetEta>=1.) return 0.0159239; // 1359.65 0.319322
    else if (JetEta>=0.8) return 0.0161597; // 1533.19 0.248855
    else if (JetEta>=0.6) return 0.0145932; // 1585.36 0.295742
    else if (JetEta>=0.4) return 0.0103849; // 1608.92 0.290273
    else if (JetEta>=0.2) return 0.00938496; // 1712.71 0.259154
    else if (JetEta>=0) return 0.0114453; // 1676.9 0.261251
  }

  
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

  if (TaggerName=="CSVL") return 0.10;
  if (TaggerName=="CSVM") return 0.02;

  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;

}
