float BTagSFUtil::TagEfficiencyB_ttx(float JetPt, float JetEta) {

	if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.432907; // 3312.87 0.865525
      else if (JetEta>=2) return 0.527985; // 3060.58 0.891767
      else if (JetEta>=1.8) return 0.536432; // 3707.54 0.796378
      else if (JetEta>=1.6) return 0.560582; // 4706.23 0.711365
      else if (JetEta>=1.4) return 0.53614; // 5615.71 0.651015
      else if (JetEta>=1.2) return 0.559908; // 6459.96 0.605354
      else if (JetEta>=1) return 0.596632; // 7239.39 0.565266
      else if (JetEta>=0.8) return 0.615811; // 8095.13 0.519877
      else if (JetEta>=0.6) return 0.637005; // 8676.53 0.501602
      else if (JetEta>=0.4) return 0.643045; // 9048.09 0.488122
      else if (JetEta>=0.2) return 0.632453; // 9378.28 0.479128
      else if (JetEta>=0) return 0.636904; // 9619.12 0.480929
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.494133; // 2567.98 0.984761
      else if (JetEta>=2) return 0.587395; // 2598.2 0.956594
      else if (JetEta>=1.8) return 0.632899; // 3464.23 0.811176
      else if (JetEta>=1.6) return 0.623411; // 4794.31 0.688093
      else if (JetEta>=1.4) return 0.622257; // 6163.37 0.609197
      else if (JetEta>=1.2) return 0.634968; // 7730.32 0.536055
      else if (JetEta>=1) return 0.669981; // 9031.9 0.485579
      else if (JetEta>=0.8) return 0.701318; // 10456.4 0.439089
      else if (JetEta>=0.6) return 0.713051; // 11673.4 0.407071
      else if (JetEta>=0.4) return 0.715508; // 12383.7 0.393289
      else if (JetEta>=0.2) return 0.708048; // 13135.8 0.386875
      else if (JetEta>=0) return 0.691503; // 13479.1 0.385439
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=1.8) return 0.625905; // 3778.31 0.797011
      else if (JetEta>=1.6) return 0.66999; // 2412.84 0.948194
      else if (JetEta>=1.4) return 0.65686; // 3437.13 0.79508
      else if (JetEta>=1.2) return 0.650279; // 4820.41 0.661916
      else if (JetEta>=1) return 0.692981; // 5947.54 0.575626
      else if (JetEta>=0.8) return 0.72607; // 7018.78 0.518975
      else if (JetEta>=0.6) return 0.730351; // 8107.63 0.463535
      else if (JetEta>=0.4) return 0.746276; // 8724.63 0.453486
      else if (JetEta>=0.2) return 0.734457; // 9481.23 0.434155
      else if (JetEta>=0) return 0.720647; // 9576.16 0.447479
    } else if (120<=JetPt && JetPt<160) {
      if (JetEta>=1.4) return 0.643006; // 2478.95 0.964551
      else if (JetEta>=1) return 0.688498; // 3629.46 0.759506
      else if (JetEta>=0.8) return 0.721837; // 2451.91 0.864494
      else if (JetEta>=0.6) return 0.743423; // 2855.79 0.811479
      else if (JetEta>=0.4) return 0.753182; // 3139.45 0.739861
      else if (JetEta>=0.2) return 0.738482; // 3397.08 0.73966
      else if (JetEta>=0) return 0.733445; // 3555.59 0.738783
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=0.8) return 0.662289; // 2630.44 0.918414
      else if (JetEta>=0.4) return 0.722409; // 2140.21 0.947752
      else if (JetEta>=0) return 0.723762; // 2579.1 0.864687
    } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=0.2) return 0.62493; // 2312.74 0.997519
      else if (JetEta>=-0.2) return 0.609945; // 569.568 1.91116
    }
	

	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

	if (TaggerName=="CSVL") return 0.80;
	if (TaggerName=="CSVM") return 0.65;

	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

	return 0.0;
}

float BTagSFUtil::TagEfficiencyC_ttx(float JetPt, float JetEta){

    if (20<=JetPt && JetPt<50) {
		if (JetEta>=1) return 0.144026; // 1367.57 0.93009
		else if (JetEta>=-0.2) return 0.175984; // 1302.01 1.04815
    } else if (50<=JetPt && JetPt<80) {
		if (JetEta>=0.4) return 0.177794; // 1413.84 0.983288
		else if (JetEta>=-0.2) return 0.183257; // 381.629 1.93721
    } else if (80<=JetPt && JetPt<120) {
		if (JetEta>=-0.2) return 0.196269; // 1061.43 1.20318
    } else if (120<=JetPt && JetPt<160) {
		if (JetEta>=-0.2) return 0.202447; // 484.451 1.77873
    } else if (160<=JetPt && JetPt<210) {
		if (JetEta>=-0.2) return 0.178232; // 302.053 2.2911
    } else if (210<=JetPt && JetPt<100000) {
		if (JetEta>=-0.2) return 0.13873; // 276.093 2.42804
    }
	
 	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
	if (TaggerName=="CSVL") return 0.35;
	if (TaggerName=="CSVM") return 0.16;
	
	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
	return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_ttx(float JetPt, float JetEta) {

    if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.0162248; // 3926.52 0.233411
      else if (JetEta>=2) return 0.024004; // 2983.58 0.28737
      else if (JetEta>=1.8) return 0.0221669; // 3171.73 0.24087
      else if (JetEta>=1.6) return 0.0203144; // 3493.16 0.241219
      else if (JetEta>=1.4) return 0.0152591; // 3989.68 0.206318
      else if (JetEta>=1.2) return 0.0161305; // 4269.08 0.171403
      else if (JetEta>=1) return 0.015755; // 4592.34 0.183503
      else if (JetEta>=0.8) return 0.0154993; // 4739.99 0.184979
      else if (JetEta>=0.6) return 0.0151595; // 5046.85 0.161207
      else if (JetEta>=0.4) return 0.016495; // 5155.2 0.16652
      else if (JetEta>=0.2) return 0.0139824; // 4976.4 0.144964
      else if (JetEta>=0) return 0.0124535; // 5197.03 0.159358
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.0153441; // 2480.17 0.219764
      else if (JetEta>=2) return 0.0212857; // 1867.7 0.320375
      else if (JetEta>=1.8) return 0.019674; // 1896.63 0.288088
      else if (JetEta>=1.6) return 0.0200207; // 2209.89 0.269375
      else if (JetEta>=1.4) return 0.015164; // 2504.66 0.242567
      else if (JetEta>=1.2) return 0.0132524; // 2764.43 0.171736
      else if (JetEta>=1) return 0.013342; // 2834.32 0.198252
      else if (JetEta>=0.8) return 0.0159277; // 2960.95 0.21296
      else if (JetEta>=0.6) return 0.015179; // 2992.92 0.225598
      else if (JetEta>=0.4) return 0.0152087; // 3249.78 0.173804
      else if (JetEta>=0.2) return 0.0146771; // 3148.24 0.194008
      else if (JetEta>=0) return 0.0140202; // 3205.01 0.187751
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=2.2) return 0.0160872; // 985.459 0.45524
      else if (JetEta>=2) return 0.0193438; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0198749; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.0189911; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.00933212; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0181355; // 1533.19 0.248855
      else if (JetEta>=1) return 0.0162356; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.0156928; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0172254; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0170841; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0150238; // 1714.09 0.279147
      else if (JetEta>=0) return 0.0130383; // 1822.07 0.225256
    } else if (120<=JetPt && JetPt<160) {
      if (JetEta>=2.2) return 0.0288123; // 985.459 0.45524
      else if (JetEta>=2) return 0.0224554; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0268033; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.0187736; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0147032; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.015338; // 1533.19 0.248855
      else if (JetEta>=1) return 0.0133058; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.0155748; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0167805; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0152456; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0159486; // 1714.09 0.279147
      else if (JetEta>=0) return 0.0147801; // 1822.07 0.225256
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=2.2) return 0.0332691; // 985.459 0.45524
      else if (JetEta>=2) return 0.0263379; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0329962; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.0199457; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0221857; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0148294; // 1533.19 0.248855
      else if (JetEta>=1) return 0.0197798; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.0126753; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0134835; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0119923; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0165475; // 1714.09 0.279147
      else if (JetEta>=0) return 0.00931099; // 1822.07 0.225256
     } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=2.0) return 0.0259802; // 985.459 0.45524
      else if (JetEta>=1.6) return 0.0247818; // 985.459 0.45524
      else if (JetEta>=1.4) return 0.0206844; // 1190.28 0.276026
      else if (JetEta>=1.2) return 0.0193422; // 1190.28 0.276026
      else if (JetEta>=1.) return 0.0178867; // 1359.65 0.319322
      else if (JetEta>=0.8) return 0.0245533; // 1533.19 0.248855
      else if (JetEta>=0.6) return 0.0159508; // 1585.36 0.295742
      else if (JetEta>=0.4) return 0.0166269; // 1608.92 0.290273
      else if (JetEta>=0.2) return 0.0122657; // 1712.71 0.259154
      else if (JetEta>=0) return 0.0199813; // 1676.9 0.261251
    }
  
  
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

  if (TaggerName=="CSVL") return 0.10;
  if (TaggerName=="CSVM") return 0.02;

  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;

}
