float BTagSFUtil::TagEfficiencyB_QCD(float JetPt, float JetEta) {

	if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.302047; // 3312.87 0.865525
      else if (JetEta>=2) return 0.427083; // 3060.58 0.891767
      else if (JetEta>=1.8) return 0.493571; // 3707.54 0.796378
      else if (JetEta>=1.6) return 0.592966; // 4706.23 0.711365
      else if (JetEta>=1.4) return 0.496605; // 5615.71 0.651015
      else if (JetEta>=1.2) return 0.472736; // 6459.96 0.605354
      else if (JetEta>=1) return 0.596966; // 7239.39 0.565266
      else if (JetEta>=0.8) return 0.689396; // 8095.13 0.519877
      else if (JetEta>=0.6) return 0.625049; // 8676.53 0.501602
      else if (JetEta>=0.4) return 0.55541; // 9048.09 0.488122
      else if (JetEta>=0.2) return 0.640873; // 9378.28 0.479128
      else if (JetEta>=0) return 0.673889; // 9619.12 0.480929
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.463116; // 2567.98 0.984761
      else if (JetEta>=2) return 0.643139; // 2598.2 0.956594
      else if (JetEta>=1.8) return 0.708404; // 3464.23 0.811176
      else if (JetEta>=1.6) return 0.607901; // 4794.31 0.688093
      else if (JetEta>=1.4) return 0.630003; // 6163.37 0.609197
      else if (JetEta>=1.2) return 0.751017; // 7730.32 0.536055
      else if (JetEta>=1) return 0.65512; // 9031.9 0.485579
      else if (JetEta>=0.8) return 0.689814; // 10456.4 0.439089
      else if (JetEta>=0.6) return 0.740007; // 11673.4 0.407071
      else if (JetEta>=0.4) return 0.652119; // 12383.7 0.393289
      else if (JetEta>=0.2) return 0.715823; // 13135.8 0.386875
      else if (JetEta>=0) return 0.673689; // 13479.1 0.385439
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=1.8) return 0.552086; // 3778.31 0.797011
      else if (JetEta>=1.6) return 0.661759; // 2412.84 0.948194
      else if (JetEta>=1.4) return 0.648447; // 3437.13 0.79508
      else if (JetEta>=1.2) return 0.703093; // 4820.41 0.661916
      else if (JetEta>=1) return 0.656025; // 5947.54 0.575626
      else if (JetEta>=0.8) return 0.832262; // 7018.78 0.518975
      else if (JetEta>=0.6) return 0.707719; // 8107.63 0.463535
      else if (JetEta>=0.4) return 0.812733; // 8724.63 0.453486
      else if (JetEta>=0.2) return 0.6352; // 9481.23 0.434155
      else if (JetEta>=0) return 0.803016; // 9576.16 0.447479
    } else if (120<=JetPt && JetPt<160) {
      if (JetEta>=1.4) return 0.623702; // 2478.95 0.964551
      else if (JetEta>=1) return 0.699399; // 3629.46 0.759506
      else if (JetEta>=0.8) return 0.771226; // 2451.91 0.864494
      else if (JetEta>=0.6) return 0.701947; // 2855.79 0.811479
      else if (JetEta>=0.4) return 0.76553; // 3139.45 0.739861
      else if (JetEta>=0.2) return 0.753079; // 3397.08 0.73966
      else if (JetEta>=0) return 0.758181; // 3555.59 0.738783
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=0.8) return 0.632425; // 2630.44 0.918414
      else if (JetEta>=0.4) return 0.731748; // 2140.21 0.947752
      else if (JetEta>=0) return 0.2637; // 2579.1 0.864687
    } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=0.2) return 0.613352; // 2312.74 0.997519
      else if (JetEta>=-0.2) return 0.640318; // 569.568 1.91116
    }
	

	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

	if (TaggerName=="CSVL") return 0.80;
	if (TaggerName=="CSVM") return 0.65;

	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

	return 0.0;
}

float BTagSFUtil::TagEfficiencyC_QCD(float JetPt, float JetEta){

    if (20<=JetPt && JetPt<50) {
		if (JetEta>=1) return 0.143675; // 1367.57 0.93009
		else if (JetEta>=-0.2) return 0.172773; // 1302.01 1.04815
    } else if (50<=JetPt && JetPt<80) {
		if (JetEta>=0.4) return 0.178747; // 1413.84 0.983288
		else if (JetEta>=-0.2) return 0.169377; // 381.629 1.93721
    } else if (80<=JetPt && JetPt<120) {
		if (JetEta>=-0.2) return 0.201998; // 1061.43 1.20318
    } else if (120<=JetPt && JetPt<160) {
		if (JetEta>=-0.2) return 0.193181; // 484.451 1.77873
    } else if (160<=JetPt && JetPt<210) {
		if (JetEta>=-0.2) return 0.173056; // 302.053 2.2911
    } else if (210<=JetPt && JetPt<100000) {
		if (JetEta>=-0.2) return 0.156549; // 276.093 2.42804
    }
	
 	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
	if (TaggerName=="CSVL") return 0.35;
	if (TaggerName=="CSVM") return 0.16;
	
	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
	return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_QCD(float JetPt, float JetEta) {

    if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.0206613; // 3926.52 0.233411
      else if (JetEta>=2) return 0.0220973; // 2983.58 0.28737
      else if (JetEta>=1.8) return 0.0164735; // 3171.73 0.24087
      else if (JetEta>=1.6) return 0.0177523; // 3493.16 0.241219
      else if (JetEta>=1.4) return 0.0150946; // 3989.68 0.206318
      else if (JetEta>=1.2) return 0.0165592; // 4269.08 0.171403
      else if (JetEta>=1) return 0.0158845; // 4592.34 0.183503
      else if (JetEta>=0.8) return 0.0138675; // 4739.99 0.184979
      else if (JetEta>=0.6) return 0.0161535; // 5046.85 0.161207
      else if (JetEta>=0.4) return 0.0124772; // 5155.2 0.16652
      else if (JetEta>=0.2) return 0.0114639; // 4976.4 0.144964
      else if (JetEta>=0) return 0.0169756; // 5197.03 0.159358
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.0177924; // 2480.17 0.219764
      else if (JetEta>=2) return 0.0197297; // 1867.7 0.320375
      else if (JetEta>=1.8) return 0.0174811; // 1896.63 0.288088
      else if (JetEta>=1.6) return 0.0220692; // 2209.89 0.269375
      else if (JetEta>=1.4) return 0.0177503; // 2504.66 0.242567
      else if (JetEta>=1.2) return 0.0173686; // 2764.43 0.171736
      else if (JetEta>=1) return 0.0182831; // 2834.32 0.198252
      else if (JetEta>=0.8) return 0.0154353; // 2960.95 0.21296
      else if (JetEta>=0.6) return 0.0130639; // 2992.92 0.225598
      else if (JetEta>=0.4) return 0.011103; // 3249.78 0.173804
      else if (JetEta>=0.2) return 0.0152541; // 3148.24 0.194008
      else if (JetEta>=0) return 0.0104621; // 3205.01 0.187751
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=2.2) return 0.0214442; // 985.459 0.45524
	 else if (JetEta>=2) return 0.0256707; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0230189; // 1190.28 0.276026
	 else if (JetEta>=1.6) return 0.0208969; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0190427; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0214948; // 1533.19 0.248855
      else if (JetEta>=1) return 0.0146702; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.01481; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0124391; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0113687; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0133238; // 1714.09 0.279147
      else if (JetEta>=0) return 0.0126878; // 1822.07 0.225256
    } else if (120<=JetPt && JetPt<160) {
       if (JetEta>=2.2) return 0.023084; // 985.459 0.45524
	 else if (JetEta>=2) return 0.016952; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0327181; // 1190.28 0.276026
	 else if (JetEta>=1.6) return 0.0245645; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0106971; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0122552; // 1533.19 0.248855
      else if (JetEta>=1) return 0.014475; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.00805432; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0166821; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.00899581; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.016298; // 1714.09 0.279147
      else if (JetEta>=0) return 0.0179229; // 1822.07 0.225256
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=2.2) return 0.0474863; // 985.459 0.45524
      else if (JetEta>=2) return 0.043756; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0310331; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.0144322; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0176023; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0147836; // 1533.19 0.248855
      else if (JetEta>=1) return 0.00959243; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.014169; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0147626; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0144743; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0115901; // 1714.09 0.279147
      else if (JetEta>=0) return 0.00956428; // 1822.07 0.225256
     } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=2.0) return 0.052016; // 985.459 0.45524
      else if (JetEta>=1.6) return 0.0395036; // 985.459 0.45524
      else if (JetEta>=1.4) return 0.0238317; // 1190.28 0.276026
      else if (JetEta>=1.2) return 0.0218824; // 1190.28 0.276026
      else if (JetEta>=1.) return 0.0175882; // 1359.65 0.319322
      else if (JetEta>=0.8) return 0.0165491; // 1533.19 0.248855
      else if (JetEta>=0.6) return 0.0152407; // 1585.36 0.295742
      else if (JetEta>=0.4) return 0.0135213; // 1608.92 0.290273
      else if (JetEta>=0.2) return 0.0136219; // 1712.71 0.259154
      else if (JetEta>=0) return 0.0141163; // 1676.9 0.261251
    }
  
  
  cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

  if (TaggerName=="CSVL") return 0.10;
  if (TaggerName=="CSVM") return 0.02;

  cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

  return 0.0;

}
