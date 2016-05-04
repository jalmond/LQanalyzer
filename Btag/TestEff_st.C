float BTagSFUtil::TagEfficiencyB_st(float JetPt, float JetEta) {

	if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.420526; // 3312.87 0.865525
      else if (JetEta>=2) return 0.503756; // 3060.58 0.891767
      else if (JetEta>=1.8) return 0.54064; // 3707.54 0.796378
      else if (JetEta>=1.6) return 0.556727; // 4706.23 0.711365
      else if (JetEta>=1.4) return 0.5297; // 5615.71 0.651015
      else if (JetEta>=1.2) return 0.54972; // 6459.96 0.605354
      else if (JetEta>=1) return 0.585484; // 7239.39 0.565266
      else if (JetEta>=0.8) return 0.628356; // 8095.13 0.519877
      else if (JetEta>=0.6) return 0.633454; // 8676.53 0.501602
      else if (JetEta>=0.4) return 0.645964; // 9048.09 0.488122
      else if (JetEta>=0.2) return 0.637438; // 9378.28 0.479128
      else if (JetEta>=0) return 0.625187; // 9619.12 0.480929
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.507241; // 2567.98 0.984761
      else if (JetEta>=2) return 0.602404; // 2598.2 0.956594
      else if (JetEta>=1.8) return 0.636437; // 3464.23 0.811176
      else if (JetEta>=1.6) return 0.640536; // 4794.31 0.688093
      else if (JetEta>=1.4) return 0.639063; // 6163.37 0.609197
      else if (JetEta>=1.2) return 0.643311; // 7730.32 0.536055
      else if (JetEta>=1) return 0.688778; // 9031.9 0.485579
      else if (JetEta>=0.8) return 0.710405; // 10456.4 0.439089
      else if (JetEta>=0.6) return 0.722444; // 11673.4 0.407071
      else if (JetEta>=0.4) return 0.729337; // 12383.7 0.393289
      else if (JetEta>=0.2) return 0.720587; // 13135.8 0.386875
      else if (JetEta>=0) return 0.700694; // 13479.1 0.385439
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=1.8) return 0.629768; // 3778.31 0.797011
      else if (JetEta>=1.6) return 0.679451; // 2412.84 0.948194
      else if (JetEta>=1.4) return 0.672162; // 3437.13 0.79508
      else if (JetEta>=1.2) return 0.697962; // 4820.41 0.661916
      else if (JetEta>=1) return 0.722355; // 5947.54 0.575626
      else if (JetEta>=0.8) return 0.75074; // 7018.78 0.518975
      else if (JetEta>=0.6) return 0.758894; // 8107.63 0.463535
      else if (JetEta>=0.4) return 0.765389; // 8724.63 0.453486
      else if (JetEta>=0.2) return 0.758184; // 9481.23 0.434155
      else if (JetEta>=0) return 0.745049; // 9576.16 0.447479
    } else if (120<=JetPt && JetPt<160) {
      if (JetEta>=1.4) return 0.652558; // 2478.95 0.964551
      else if (JetEta>=1) return 0.714873; // 3629.46 0.759506
      else if (JetEta>=0.8) return 0.752755; // 2451.91 0.864494
      else if (JetEta>=0.6) return 0.767841; // 2855.79 0.811479
      else if (JetEta>=0.4) return 0.768426; // 3139.45 0.739861
      else if (JetEta>=0.2) return 0.766357; // 3397.08 0.73966
      else if (JetEta>=0) return 0.742728; // 3555.59 0.738783
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=0.8) return 0.670426; // 2630.44 0.918414
      else if (JetEta>=0.4) return 0.751355; // 2140.21 0.947752
      else if (JetEta>=0) return 0.73405; // 2579.1 0.864687
    } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=0.2) return 0.624594; // 2312.74 0.997519
      else if (JetEta>=-0.2) return 0.622359; // 569.568 1.91116
    }
	

	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

	if (TaggerName=="CSVL") return 0.80;
	if (TaggerName=="CSVM") return 0.65;

	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

	return 0.0;
}

float BTagSFUtil::TagEfficiencyC_st(float JetPt, float JetEta){

    if (20<=JetPt && JetPt<50) {
		if (JetEta>=1) return 0.129; // 1367.57 0.93009
		else if (JetEta>=-0.2) return 0.175724; // 1302.01 1.04815
    } else if (50<=JetPt && JetPt<80) {
		if (JetEta>=0.4) return 0.184146; // 1413.84 0.983288
		else if (JetEta>=-0.2) return 0.20813; // 381.629 1.93721
    } else if (80<=JetPt && JetPt<120) {
		if (JetEta>=-0.2) return 0.199663; // 1061.43 1.20318
    } else if (120<=JetPt && JetPt<160) {
		if (JetEta>=-0.2) return 0.201577; // 484.451 1.77873
    } else if (160<=JetPt && JetPt<210) {
		if (JetEta>=-0.2) return 0.189963; // 302.053 2.2911
    } else if (210<=JetPt && JetPt<100000) {
		if (JetEta>=-0.2) return 0.145756; // 276.093 2.42804
    }
	
 	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
	if (TaggerName=="CSVL") return 0.35;
	if (TaggerName=="CSVM") return 0.16;
	
	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
	return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_st(float JetPt, float JetEta) {

    if (20<=JetPt && JetPt<50) {
		if (JetEta>=2.2) return 0.0168947; // 3926.52 0.233411
		else if (JetEta>=2) return 0.0216315; // 2983.58 0.28737
		else if (JetEta>=1.8) return 0.020548; // 3171.73 0.24087
		else if (JetEta>=1.6) return 0.0186308; // 3493.16 0.241219
		else if (JetEta>=1.4) return 0.0140933; // 3989.68 0.206318
		else if (JetEta>=1.2) return 0.0128979; // 4269.08 0.171403
		else if (JetEta>=1) return 0.0139725; // 4592.34 0.183503
		else if (JetEta>=0.8) return 0.0141467; // 4739.99 0.184979
		else if (JetEta>=0.6) return 0.0148472; // 5046.85 0.161207
		else if (JetEta>=0.4) return 0.0133154; // 5155.2 0.16652
		else if (JetEta>=0.2) return 0.0127749; // 4976.4 0.144964
		else if (JetEta>=0) return 0.0115631; // 5197.03 0.159358
    } else if (50<=JetPt && JetPt<80) {
		if (JetEta>=2.2) return 0.0170112; // 2480.17 0.219764
		else if (JetEta>=2) return 0.0189454; // 1867.7 0.320375
		else if (JetEta>=1.8) return 0.0179771; // 1896.63 0.288088
		else if (JetEta>=1.6) return 0.0153559; // 2209.89 0.269375
		else if (JetEta>=1.4) return 0.0122019; // 2504.66 0.242567
		else if (JetEta>=1.2) return 0.0134714; // 2764.43 0.171736
		else if (JetEta>=1) return 0.00982815; // 2834.32 0.198252
		else if (JetEta>=0.8) return 0.0119605; // 2960.95 0.21296
		else if (JetEta>=0.6) return 0.0113064; // 2992.92 0.225598
		else if (JetEta>=0.4) return 0.0106466; // 3249.78 0.173804
		else if (JetEta>=0.2) return 0.00945686; // 3148.24 0.194008
		else if (JetEta>=0) return 0.0107928; // 3205.01 0.187751
    } else if (80<=JetPt && JetPt<120) {
		if (JetEta>=2.2) return 0.0226253; // 985.459 0.45524
		else if (JetEta>=2) return 0.0193255; // 985.459 0.45524
		else if (JetEta>=1.8) return 0.0206964; // 1190.28 0.276026
		else if (JetEta>=1.6) return 0.0161495; // 1190.28 0.276026
		else if (JetEta>=1.4) return 0.0111715; // 1359.65 0.319322
		else if (JetEta>=1.2) return 0.0112597; // 1533.19 0.248855
		else if (JetEta>=1) return 0.0101117; // 1585.36 0.295742
		else if (JetEta>=0.8) return 0.0165754; // 1608.92 0.290273
		else if (JetEta>=0.6) return 0.00896783; // 1712.71 0.259154
		else if (JetEta>=0.4) return 0.00841042; // 1676.9 0.261251
		else if (JetEta>=0.2) return 0.0111454; // 1714.09 0.279147
		else if (JetEta>=0) return 0.0153943; // 1822.07 0.225256
    } else if (120<=JetPt && JetPt<160) {
		if (JetEta>=2.2) return 0.0219286; // 985.459 0.45524
		else if (JetEta>=2) return 0.018868; // 985.459 0.45524
		else if (JetEta>=1.8) return 0.0248819; // 1190.28 0.276026
		else if (JetEta>=1.6) return 0.0113104; // 1190.28 0.276026
		else if (JetEta>=1.4) return 0.00843451; // 1359.65 0.319322
		else if (JetEta>=1.2) return 0.00889174; // 1533.19 0.248855
		else if (JetEta>=1) return 0.00898219; // 1585.36 0.295742
		else if (JetEta>=0.8) return 0.00814773; // 1608.92 0.290273
		else if (JetEta>=0.6) return 0.0134928; // 1712.71 0.259154
		else if (JetEta>=0.4) return 0.0117304; // 1676.9 0.261251
		else if (JetEta>=0.2) return 0.00832048; // 1714.09 0.279147
		else if (JetEta>=0) return 0.0103036; // 1822.07 0.225256
    } else if (160<=JetPt && JetPt<210) {
		if (JetEta>=2.2) return 0.0178908; // 985.459 0.45524
		else if (JetEta>=2) return 0.0225278; // 985.459 0.45524
		else if (JetEta>=1.8) return 0.0202075; // 1190.28 0.276026
		else if (JetEta>=1.6) return 0.0215157; // 1190.28 0.276026
		else if (JetEta>=1.4) return 0.0125829; // 1359.65 0.319322
		else if (JetEta>=1.2) return 0.0162924; // 1533.19 0.248855
		else if (JetEta>=1) return 0.00855293; // 1585.36 0.295742
		else if (JetEta>=0.8) return 0.0200824; // 1608.92 0.290273
		else if (JetEta>=0.6) return 0.0113676; // 1712.71 0.259154
		else if (JetEta>=0.4) return 0.0104205; // 1676.9 0.261251
		else if (JetEta>=0.2) return 0.00567785; // 1714.09 0.279147
		else if (JetEta>=0) return 0.00965227; // 1822.07 0.225256
	} else if (210<=JetPt && JetPt<100000) {
		if (JetEta>=2.0) return 0.0302392; // 985.459 0.45524
		else if (JetEta>=1.6) return 0.0220656; // 985.459 0.45524
		else if (JetEta>=1.4) return 0.0166822; // 1190.28 0.276026
		else if (JetEta>=1.2) return 0.0202309; // 1190.28 0.276026
		else if (JetEta>=1.) return 0.0150406; // 1359.65 0.319322
		else if (JetEta>=0.8) return 0.0176859; // 1533.19 0.248855
		else if (JetEta>=0.6) return 0.0109523; // 1585.36 0.295742
		else if (JetEta>=0.4) return 0.013663; // 1608.92 0.290273
		else if (JetEta>=0.2) return 0.0210432; // 1712.71 0.259154
		else if (JetEta>=0) return 0.0121793; // 1676.9 0.261251
    }

  
	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

	if (TaggerName=="CSVL") return 0.10;
	if (TaggerName=="CSVM") return 0.02;

	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

	return 0.0;

}
