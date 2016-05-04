float BTagSFUtil::TagEfficiencyB_VV(float JetPt, float JetEta) {

  if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.426525; // 3312.87 0.865525
      else if (JetEta>=2) return 0.522589; // 3060.58 0.891767
      else if (JetEta>=1.8) return 0.561596; // 3707.54 0.796378
      else if (JetEta>=1.6) return 0.553592; // 4706.23 0.711365
      else if (JetEta>=1.4) return 0.523199; // 5615.71 0.651015
      else if (JetEta>=1.2) return 0.535441; // 6459.96 0.605354
      else if (JetEta>=1) return 0.58634; // 7239.39 0.565266
      else if (JetEta>=0.8) return 0.605134; // 8095.13 0.519877
      else if (JetEta>=0.6) return 0.635897; // 8676.53 0.501602
      else if (JetEta>=0.4) return 0.628879; // 9048.09 0.488122
      else if (JetEta>=0.2) return 0.62644; // 9378.28 0.479128
      else if (JetEta>=0) return 0.614815; // 9619.12 0.480929
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.479293; // 2567.98 0.984761
      else if (JetEta>=2) return 0.590808; // 2598.2 0.956594
      else if (JetEta>=1.8) return 0.618576; // 3464.23 0.811176
      else if (JetEta>=1.6) return 0.619114; // 4794.31 0.688093
      else if (JetEta>=1.4) return 0.62065; // 6163.37 0.609197
      else if (JetEta>=1.2) return 0.638358; // 7730.32 0.536055
      else if (JetEta>=1) return 0.664745; // 9031.9 0.485579
      else if (JetEta>=0.8) return 0.704444; // 10456.4 0.439089
      else if (JetEta>=0.6) return 0.706585; // 11673.4 0.407071
      else if (JetEta>=0.4) return 0.719156; // 12383.7 0.393289
      else if (JetEta>=0.2) return 0.710279; // 13135.8 0.386875
      else if (JetEta>=0) return 0.717061; // 13479.1 0.385439
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=1.8) return 0.604839; // 3778.31 0.797011
      else if (JetEta>=1.6) return 0.684911; // 2412.84 0.948194
      else if (JetEta>=1.4) return 0.672679; // 3437.13 0.79508
      else if (JetEta>=1.2) return 0.666124; // 4820.41 0.661916
      else if (JetEta>=1) return 0.707474; // 5947.54 0.575626
      else if (JetEta>=0.8) return 0.717791; // 7018.78 0.518975
      else if (JetEta>=0.6) return 0.739321; // 8107.63 0.463535
      else if (JetEta>=0.4) return 0.721582; // 8724.63 0.453486
      else if (JetEta>=0.2) return 0.756875; // 9481.23 0.434155
      else if (JetEta>=0) return 0.718047; // 9576.16 0.447479
    } else if (120<=JetPt && JetPt<160) {
      if (JetEta>=1.4) return 0.645396; // 2478.95 0.964551
      else if (JetEta>=1) return 0.711283; // 3629.46 0.759506
      else if (JetEta>=0.8) return 0.753596; // 2451.91 0.864494
      else if (JetEta>=0.6) return 0.760168; // 2855.79 0.811479
      else if (JetEta>=0.4) return 0.727069; // 3139.45 0.739861
      else if (JetEta>=0.2) return 0.739904; // 3397.08 0.73966
      else if (JetEta>=0) return 0.726581; // 3555.59 0.738783
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=0.8) return 0.642159; // 2630.44 0.918414
      else if (JetEta>=0.4) return 0.775438; // 2140.21 0.947752
      else if (JetEta>=0) return 0.642159; // 2579.1 0.864687
    } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=0.2) return 0.656774; // 2312.74 0.997519
      else if (JetEta>=-0.2) return 0.639007; // 569.568 1.91116
    }
	

	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

	if (TaggerName=="CSVL") return 0.80;
	if (TaggerName=="CSVM") return 0.65;

	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

	return 0.0;
}

float BTagSFUtil::TagEfficiencyC_VV(float JetPt, float JetEta){

    if (20<=JetPt && JetPt<50) {
		if (JetEta>=1) return 0.13933; // 1367.57 0.93009
		else if (JetEta>=-0.2) return 0.173397; // 1302.01 1.04815
    } else if (50<=JetPt && JetPt<80) {
		if (JetEta>=0.4) return 0.179941; // 1413.84 0.983288
		else if (JetEta>=-0.2) return 0.192383; // 381.629 1.93721
    } else if (80<=JetPt && JetPt<120) {
		if (JetEta>=-0.2) return 0.19684; // 1061.43 1.20318
    } else if (120<=JetPt && JetPt<160) {
		if (JetEta>=-0.2) return 0.196065; // 484.451 1.77873
    } else if (160<=JetPt && JetPt<210) {
		if (JetEta>=-0.2) return 0.187286; // 302.053 2.2911
    } else if (210<=JetPt && JetPt<100000) {
		if (JetEta>=-0.2) return 0.13689; // 276.093 2.42804
    }
	
 	cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;
	
	if (TaggerName=="CSVL") return 0.35;
	if (TaggerName=="CSVM") return 0.16;
	
	cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;
	
	return 0.0;
	
}

float BTagSFUtil::TagEfficiencyLight_VV(float JetPt, float JetEta) {

    if (20<=JetPt && JetPt<50) {
      if (JetEta>=2.2) return 0.0172886; // 3926.52 0.233411
      else if (JetEta>=2) return 0.0209367; // 2983.58 0.28737
      else if (JetEta>=1.8) return 0.0191946; // 3171.73 0.24087
      else if (JetEta>=1.6) return 0.016333; // 3493.16 0.241219
      else if (JetEta>=1.4) return 0.0123993; // 3989.68 0.206318
      else if (JetEta>=1.2) return 0.0127333; // 4269.08 0.171403
      else if (JetEta>=1) return 0.0132344; // 4592.34 0.183503
      else if (JetEta>=0.8) return 0.0122703; // 4739.99 0.184979
      else if (JetEta>=0.6) return 0.0124294; // 5046.85 0.161207
      else if (JetEta>=0.4) return 0.0116511; // 5155.2 0.16652
      else if (JetEta>=0.2) return 0.010974; // 4976.4 0.144964
      else if (JetEta>=0) return 0.0107515; // 5197.03 0.159358
    } else if (50<=JetPt && JetPt<80) {
      if (JetEta>=2.2) return 0.015453; // 2480.17 0.219764
      else if (JetEta>=2) return 0.0179924; // 1867.7 0.320375
      else if (JetEta>=1.8) return 0.0177975; // 1896.63 0.288088
      else if (JetEta>=1.6) return 0.0135433; // 2209.89 0.269375
      else if (JetEta>=1.4) return 0.0104403; // 2504.66 0.242567
      else if (JetEta>=1.2) return 0.0121888; // 2764.43 0.171736
      else if (JetEta>=1) return 0.0113719; // 2834.32 0.198252
      else if (JetEta>=0.8) return 0.0119742; // 2960.95 0.21296
      else if (JetEta>=0.6) return 0.0120386; // 2992.92 0.225598
      else if (JetEta>=0.4) return 0.0101976; // 3249.78 0.173804
      else if (JetEta>=0.2) return 0.00990729; // 3148.24 0.194008
      else if (JetEta>=0) return 0.0104937; // 3205.01 0.187751
    } else if (80<=JetPt && JetPt<120) {
      if (JetEta>=2.2) return 0.0162274; // 985.459 0.45524
      else if (JetEta>=2) return 0.0200963; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0184651; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.015179; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0123266; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0111542; // 1533.19 0.248855
      else if (JetEta>=1) return 0.0117191; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.0113167; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0112246; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0103002; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0100859; // 1714.09 0.279147
      else if (JetEta>=0) return 0.00997339; // 1822.07 0.225256
    } else if (120<=JetPt && JetPt<160) {
      if (JetEta>=2.2) return 0.0168296; // 985.459 0.45524
      else if (JetEta>=2) return 0.0257212; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0151989; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.015003; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.01046; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0135304; // 1533.19 0.248855
      else if (JetEta>=1) return 0.0112112; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.0107184; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0124863; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0118367; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.0114207; // 1714.09 0.279147
      else if (JetEta>=0) return 0.0109193; // 1822.07 0.225256
    } else if (160<=JetPt && JetPt<210) {
      if (JetEta>=2.2) return 0.0267263; // 985.459 0.45524
      else if (JetEta>=2) return 0.0372293; // 985.459 0.45524
      else if (JetEta>=1.8) return 0.0248721; // 1190.28 0.276026
      else if (JetEta>=1.6) return 0.0150501; // 1190.28 0.276026
      else if (JetEta>=1.4) return 0.0102861; // 1359.65 0.319322
      else if (JetEta>=1.2) return 0.0145421; // 1533.19 0.248855
      else if (JetEta>=1) return 0.011693; // 1585.36 0.295742
      else if (JetEta>=0.8) return 0.0132063; // 1608.92 0.290273
      else if (JetEta>=0.6) return 0.0110267; // 1712.71 0.259154
      else if (JetEta>=0.4) return 0.0110006; // 1676.9 0.261251
      else if (JetEta>=0.2) return 0.00959434; // 1714.09 0.279147
      else if (JetEta>=0) return 0.00902735; // 1822.07 0.225256
    } else if (210<=JetPt && JetPt<100000) {
      if (JetEta>=2.0) return 0.032936; // 985.459 0.45524
      else if (JetEta>=1.6) return 0.0212628; // 985.459 0.45524
      else if (JetEta>=1.4) return 0.0193343; // 1190.28 0.276026
      else if (JetEta>=1.2) return 0.01975; // 1190.28 0.276026
      else if (JetEta>=1.) return 0.0124663; // 1359.65 0.319322
      else if (JetEta>=0.8) return 0.0112079; // 1533.19 0.248855
      else if (JetEta>=0.6) return 0.0136942; // 1585.36 0.295742
      else if (JetEta>=0.4) return 0.015062; // 1608.92 0.290273
      else if (JetEta>=0.2) return 0.0101757; // 1712.71 0.259154
      else if (JetEta>=0) return 0.010088; // 1676.9 0.261251
    }

  
cout << "BTagSFUtil: Jet pt (" << JetPt << ") or jet eta (" << JetEta << ") out of range!" << endl;

if (TaggerName=="CSVL") return 0.10;
if (TaggerName=="CSVM") return 0.02;

cout << "BTagSFUtil: Tagger (" << TaggerName << ") not valid!" << endl;

return 0.0;

}
