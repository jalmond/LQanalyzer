#include "TTFitter.h"

#include "TMinuit.h"
#include "TMath.h"

#include <iostream>
#include <algorithm>
#include <math.h>


TTFitter::~TTFitter(){
}


TTFitter::TTFitter(){
}


//Things I send back from the fitter
Double_t TTFitter::Mass[48]; //48 combinations. only one Mtop from the fitter for each event
Double_t TTFitter::HMass[48]; //48 combinations. only one Mtop from the fitter for each event
Double_t TTFitter::Chi2[48];
Double_t TTFitter::Error[48][9]; //one error for each parameter for each combination
Double_t TTFitter::mtop_error_p[48];
Double_t TTFitter::mtop_error_m[48];
Double_t TTFitter::bestchi2;
Double_t TTFitter::bestmass;
Double_t TTFitter::bestHmass;
Double_t TTFitter::neupzin[48]; //neutrino pz solution used by the fitter for each of the 48 combinations
Int_t TTFitter::sol;
Int_t TTFitter::combos[48][4];
bool TTFitter::tagconsistent[48];
TLorentzVector TTFitter::rawJets[48][4];
TLorentzVector TTFitter::jetsIN[48][4];

bool TTFitter::imaginary[48];

TLorentzVector TTFitter::FittedJets[48][4];
TLorentzVector TTFitter::FittedLep[48];
TLorentzVector TTFitter::FittedNeu[48];
Double_t TTFitter::JetSigma[48][4];

//extra things i've added

//TLorentzVector TTFitter::unclustered;

Double_t TTFitter::LeptonSigma;
Double_t TTFitter::LeptonChi[48];
Double_t TTFitter::UnclXChi[48];
Double_t TTFitter::UnclYChi[48];
Double_t TTFitter::LepWChi[48];
Double_t TTFitter::HadWChi[48];
Double_t TTFitter::HadTopChi[48];
Double_t TTFitter::LepTopChi[48];
Double_t TTFitter::JetChi[4][48];

Double_t TTFitter::Scale[48][7];
Double_t TTFitter::Out[48][9];

Double_t TTFitter::tleptonchi;
Double_t TTFitter::tunclxchi;
Double_t TTFitter::tunclychi;
Double_t TTFitter::tlepwchi;
Double_t TTFitter::tleptopchi;
Double_t TTFitter::thadtopchi;
Double_t TTFitter::thadwchi;
Double_t TTFitter::tjet0chi;
Double_t TTFitter::tjet1chi;
Double_t TTFitter::tjet2chi;
Double_t TTFitter::tjet3chi;

//internal to the class
TLorentzVector TTFitter::tjets[4];
Double_t TTFitter::tsigmajets[4];

TLorentzVector TTFitter::tlepton;
Double_t TTFitter::sigmalep;

TLorentzVector TTFitter::uncl;
Double_t TTFitter::sigmauncl;

//Internal to the fitter function
TLorentzVector TTFitter::fitneu;
TLorentzVector TTFitter::fitlep;
TLorentzVector TTFitter::fitjets[4];
TLorentzVector TTFitter::Wjj;
TLorentzVector TTFitter::hTop;
TLorentzVector TTFitter::Wlv;
TLorentzVector TTFitter::lTop;
TLorentzVector TTFitter::addjet;

using namespace std;

Double_t TTFitter::tsjetCorr[3][4]; //[0] is a b, [1] is a c, [2] is light quark
Double_t TTFitter::sigmajets[3][4];


//ClassImp (TTFitter);

void TTFitter::Fit(TLorentzVector Lepton, float Lepsigma, TLorentzVector jets[], int btag[], TLorentzVector sumjets, TLorentzVector met, TLorentzVector metraw,  TLorentzVector addjets, Int_t tstype, bool debug, bool highpt){
	//	void TTFitter::Fit(TLorentzVector Lepton, float Lepsigma, TLorentzVector jets[], TLorentzVector jetraw[], bool btag[], TLorentzVector sumjets, TLorentzVector met, int ntupletype,  Int_t tstype, bool debug, bool highpt){

	/////////////////////////////////////////////////////////////////////////////////////////////
	// VARIABLES KEY::
	//
	// lepton:        uncorrected lepton
	//
	// rawlepton:     For electrons, should be the EM cluster energy. For muons, should be before Larry's invpt corrections
	//                Currently set equal to lepton - needs to be changed later
	//
	// leptype:       1 for electrons, 2 for muons
	//
	// charge:        -1 or 1 (don't have this at the moment)
	//
	// jets[4]:       whatever 4 jets are assumed to be matched with the two b's
	//                and jets from W in ttbar event
	//                The jets are ordered in pt, regardless of whether they are b tagged.
	//
	// jetCorr[4][4]: first index of array define level of jet corrections (Level4, Level5, Level6, Level7)
	//                and second index of array defines which of jet these corrections match to in jets[4]
	//                Currently all set to 1 
	//
	// btag[4]:       does jet i have a btag
	//
	// detEta[4]      Detector Eta
	//
	// sumjets[2]:    [0] is the sum of all loose jets in a 4-vector no corrections.  [1] is the
	//                same thing only the jets are corrected to Level 5.  NOTE:  I define loose 
	//                jets as any jets that pass loose cuts so 'tight' jets are part of this sample.
	//                
	//
	// met[3]:        [0] is vertex corrected MET, [1] is muon corrected, [2] is Level4 jet 
	//                corrected
	//                Currently all levels are just the basic MET from the ntuple
	//
	// ntupletype:    0 for Monte Carlo, 1 for Data
	//
	// constrained:   true to force top mass to a particular value
	//
	//
	// tstype==-1:    Generic L6,7 correction (instead of top-specific correction) by UKYANG
	//
	// PEM leptype=3 included by YJLEE and UKYANG
	//
	/////////////////////////////////////////////////////////////////////////////////////////////

	// Debuggsing

	//	bool debug = false;
	//	bool rescale_ts = false;

	//   WmassMod = 80.42;
	//   WwidthMod = 2.12;
	//   TopwidthMod = 1.5;
	//   TopmassMod = 175.0;

	// std::cout << "topmass = " << TopmassMod << std::endl;

	// First, set outputs

	for (int i=0; i<48; i++) {
		Mass[i]=0;
		Chi2[i]=9999;
		mtop_error_p[i]=9999;
		mtop_error_m[i]=-9999;

		LeptonChi[i]=9999;
		UnclXChi[i]=9999;
		UnclYChi[i]=9999;
		LepWChi[i]=9999;
		HadWChi[i]=9999;
		HadTopChi[i]=9999;
		LepTopChi[i]=9999;
		JetChi[0][i]=9999;
		JetChi[1][i]=9999;
		JetChi[2][i]=9999;
		JetChi[3][i]=9999;

		for (int j=0; j<9; j++) {
			Error[i][j]=9999;
		}
	}

	sol=-1; // will be used to label the array index of the best combination
	bestchi2=999999;
	bestmass=0;
	bestHmass=0;


	//////FIRST SECTION IS PREPARING OBJECTS FOR THE FIT

	//leptons

	tlepton=Lepton;
	sigmalep = Lepsigma;
	
	if (debug)
		std::cout << "Lepton Pt = " << Lepton.Pt() << std::endl;

	////Unclustered Energy

	//Preparing The Vector Sum Of All Loose Jets Except Above 4
	//For Both Uncorrected And Level5 Corrected
	//NOTE: sumjets[].E() is actually scalar sum of Et (no Pz component)


	// Extra Jets only other than leading four jets

	TLorentzVector cljets(0,0,0,0);

	//sumjets[0] is the sum of uncorrected loose jets in the event. not in topview - calculated in main analysis code
	//loose jets are any jets that pass loose cuts, so includes tight jets too.
	Double_t cljetsEx=sumjets.Px(),cljetsEy=sumjets.Py(),cljetsEt=sumjets.Pt();
	addjet = addjets;
	if (debug){
		cout << " Clustered Raw JEts Ex = " << cljetsEx << ", Ey = " << cljetsEy << endl;
		cout << " Additional Jets Pt = " << addjets.Pt() << endl;
	}
		
	// //subtract off the leading 4 jets
	// for(int i=0;i<4;i++){

	// 	//uncorrected
	// 	addljetsEx-=jetraw[i].Px();
	// 	addljetsEy-=jetraw[i].Py();
	// 	addljetsEt-=jetraw[i].Pt();
	// 	//std::cout << "Sub Jets Ex " << addljetsEx << " Ey " << addljetsEy << " Et " << addljetsEt << std::endl;

	// }

	// //these are the sum of all jets minus the four leading jets
	// sum of clustered raw jets
	cljets.SetPxPyPzE(cljetsEx,cljetsEy,0,cljetsEt);

	//Putting together raw unclustered energy, i.e. must balance jets, lepton and met
	Double_t unclrawEx=0.0,unclrawEy=0.0;

	// //subtract 4 leading jets
	// for(int i=0;i<4;i++){
	// 	unclrawEx -= jetraw[i].Px(); //uncorrected jet energy
	// 	unclrawEy -= jetraw[i].Py();
	// 	//std::cout << "Take Jets Uncl Ex " << unclrawEx << " Ey  " << unclrawEy <<  std::endl;
	// }

	//subtract uncorrected loose jets, lepton and met. met is muon corrected met.
	// unclrawEx = 0 - 4leadingjetsPx - extrajetPx - leptonPx - METPx
	// i.e. everything left over after primary lepton and jets with pt > 15 GeV
	unclrawEx -= cljets.Px();
	unclrawEy -= cljets.Py();
	//std::cout << "Take ljets Uncl Ex " << unclrawEx << " Ey  " << unclrawEy <<  std::endl;
	unclrawEx -= Lepton.Px();
	unclrawEy -= Lepton.Py();
	//std::cout << "Take lepton Uncl Ex " << unclrawEx << " Ey  " << unclrawEy <<  std::endl;
	unclrawEx -= metraw.Px();
	unclrawEy -= metraw.Py();
	//std::cout << "Take met Uncl Ex " << unclrawEx << " Ey  " << unclrawEy <<  std::endl;

	//Now preparing the 'full' unclustered energy

	uncl.SetPxPyPzE(unclrawEx,unclrawEy,0,sqrt(unclrawEx*unclrawEx+unclrawEy*unclrawEy));
	//std::cout << "Uncl Ex " << uncl.Px() << " Ey  " << uncl.Py() <<  std::endl;
  
	//	unclustered = uncl;

	//Sigma of Unclustered Energy

	//	Double_t sumet= uncl.Et();
	//std::cout << "Uncl Et " << uncl.Et() <<  std::endl;


	//Now calculate the error
	//   sigmauncl = 1.0*.;  // MeV Unit( blame ATLAS)
	//   if(sumet > 6.25*.) sigmauncl=0.4*sqrt(sumet);
	//   //std::cout << "Uncl sigma " << sigmauncl <<  std::endl;

	//uncertainty  of sum jets pT > 10 GeV is only 10 % according to the MET study
	sigmauncl=0.5*( uncl.Et() );
   
	////Jets

	int ntags=0;
	for(int i=0;i<4;i++){
		ntags+= btag[i];
	}
	//std::cout << "ntags " << ntags <<  std::endl;

   
	//Top-Specific corrections and sigmas calculated
	//MPV CORR. EXTRACTED FROM LEVEL 5 CORR

	//filling tsjetCorr and sigma jets for different top specific corrections
	//not generic - different for W and b jets 

	if (debug) std::cout << " TSType : " << tstype << std::endl;
	GetTSCorr(jets, tstype, debug);


	if (debug)	   std::cout << "About to run fitter" << std::endl;
	//////PREPARING TO RUN THE FITTER

	////Initilizing Minuit and variables

	//nfit is number of parameters
	const int nfit=10;
	//std::cout << "About to make new TMinuit" << std::endl;
	TMinuit *minuit=new TMinuit(nfit);

	//std::cout << "Made new TMinuit" << std::endl;

	//tells minuit to minimise fcn, i.e. the chisquared function
	minuit->SetFCN(fcn);

	//	if (debug)
	//	minuit->SetPrintLevel(3);
	//else
	minuit->SetPrintLevel(-1);
	
	Double_t arglist[10]; //used in the minuit commands - one element for the number of times the function is called. the other 9 are used 
	//to refer to the parameters
	Int_t ierflg=0;
	minuit->mnexcm("SET NOW",arglist,0,ierflg); // (command, arglist, how many of the elements of arglist to look at, ierflg should be <5)

	////Setting up minuit parameters
	//not putting them into minuit yet.

	//starting values of the parameters
	//  Double_t vstart[nfit]={1.0,1.0,1.0,1.0,175*1000.,1.0,1.0,1.0,0.0};
	//  Double_t vstart[nfit]={1.0,1.0,1.0,1.0,80*1000.,1.0,1.0,1.0,0.0}; // old version

	Double_t vstart[nfit]={1.0,1.0,1.0,1.0,Topmass,1.0,1.0,1.0,0.0,0.0}; //modified version

	//step size of thep arameters
	//  Double_t step[nfit]  ={0.03, 0.03, 0.03, 0.03, 20*1000., 0.01, 0.1, 0.1, 1.0*1000.}; //old version
	//  Double_t step[nfit]  ={0.0, 0.0, 0.0, 0.0, 20*1000., 0., 0., 0., 0.};

	Double_t step[nfit]  ={0.03, 0.03, 0.03, 0.03, 0.01, 0.01, 0.1, 0.1, 1.0, 0.1};//modified version


	//Limits.....
	//Double_t high[nfit]={10.0,10.0,10.0,10.0,0.,10.0,0.,0.,0.,0.};

	// parameter names

	TString name[nfit]={"b1","b2","j1","j2","TopMass","lep","unclx","uncly","Pzneu",""};

	//INFO ON JET ORDERING

	//jets passed from TutorialCycle are ordered in pT, not based on b tagging information.
	//combinations assume that the first 2 jets in the array are the b jets, even if not tagged, and that [0] is from the leptonic
	//side, [1] is from the hadronic side, [2] and [3] are the light jets.


	////RUNNING IT

	//Things i want to keep after fit
	Double_t lowchi2=1000000; //Max value for chi2 cut. high value means we keep all the combinations
	Double_t value[nfit]; // the fitter gives an output for each of the 9 parameters for each combination

	//Some things the fitter needs

	int combo[4]={0,1,2,3};
	int bestcombo[4]={0,0,0,0};
	bool oddnumber=false;

	//Start the fit
	//loop over all 48 combinations
	for(int i=0;i<48;i++){

		//Increment the permutation after first run through (first combination is already defined as {0,1,2,3} )
		//next_permutation changes the order of the elements in in the array
		//onl need to do it for odd numbers, since each permutation has 2 neutrino solutions. there are 12 possible permutations
    
		if(i>0){
			oddnumber=!oddnumber;
			if (i%2 == 0) std::next_permutation(combo,combo+4);
		}

		//fill combos[i][j] with each permutation of the jets (eg [0][j] = [1][j] since the combinations only differ due to neutrino 
		//solutions

		for (int j=0; j<4; j++) {
			combos[i][j]=combo[j];
		}

		//Use MET based on THIS combination!
		//define the MET and set to zero
		//		TLorentzVector thismet;
		//thismet.SetPxPyPzE(0.,0.,0.,0.);

		//loop over 4 leading jets
		//assign quark mass = 5 to the first 2 jets (i.e. b jets) and 0.5 to the light jets
		//qcorr makes sure we apply the right top specific correction i.e. 0 for a b jet, 1 for a light jet
		if (debug){
			std::cout << " ======================== " << std::endl;
			std::cout << " Fit Runs for Set " << i  <<  " AND COMBO : " << combos[i][0] << " " << combos[i][1] << " " << combos[i][2] << " " << combos[i][3] << std::endl;
		}

		float ratio[4];
		for(int j=0;j<4;j++){
			int qcorr=0;
			Double_t quark_mass=b_mass;
			if(j>2){
				qcorr=1; quark_mass=c_mass;
			}
			TLorentzVector tempjet;

			//apply top specific jet correction to the jets that have already been level 5 corrected
			tempjet.SetPtEtaPhiM(tsjetCorr[qcorr][combo[j]]*jets[combo[j]].Pt(),jets[combo[j]].Eta(),jets[combo[j]].Phi(),quark_mass);

			// finding the missing Et: first subtract the top specific corrected jet energies

			//	thismet -= tempjet;

			//set out different levels of jet corrections incase we need them later
			rawJets[i][j]=jets[combo[j]];
			ratio[j] = sigmajets[qcorr][combo[j]]/tempjet.Pt();
			
		}

		Double_t low[nfit]={1.0-2.0*ratio[0],1.0-2.0*ratio[1],1.0-2.0*ratio[2],1.0-2.0*ratio[3],0.,0.99,0.5,0.5,0.};
		Double_t high[nfit]={1.0+2.0*ratio[0],1.0+2.0*ratio[1],1.0+2.0*ratio[2],1.0+2.0*ratio[3],0.,1.01,1.5,1.5,0.};

		
		// then subtract the lepton energy

		//thismet-=Lepton;

		// Pz Solutions
		// Need to do this inside the fitter since rescaling jets will affect neutrino solutions, due to missing Et.

		Double_t PzSol[2] = {0,0};

		Double_t d = ((Wmass)*(Wmass))/2+Lepton.Px()*met.Px()+Lepton.Py()*met.Py();
		Double_t a = Lepton.E()*Lepton.E() - Lepton.Pz()*Lepton.Pz();
		Double_t b = -2*d*Lepton.Pz();
		Double_t c = Lepton.E()*Lepton.E()*met.Pt()*met.Pt()-d*d;

		//std::cout << "Is this negative? " << b*b-4*a*c << std::endl;
		//std::cout << "For solution " << i << " Met " << thismet.Pt() << " Lep Px " << Lepton.Px() << " Lep Py " << Lepton.Px() << " Lep Pz " << Lepton.Pz() 
		//<< " Met Pt " << met.Pt() << std::endl;
		//std::cout << " a " << a << " b " << b << " c " << c << " d " << d << std::endl;

		if(b*b-4*a*c>=0){
			PzSol[0] = (-b+sqrt(b*b-4*a*c))/(2*a);
			PzSol[1] = (-b-sqrt(b*b-4*a*c))/(2*a);
			imaginary[i] = false;
		}

		//taking real part for complex solution.
		if(b*b-4*a*c<0){
			PzSol[0] = (-b)/(2*a);
			PzSol[1] = (-b)/(2*a);
			imaginary[i] = true;
		}

		//std::cout << "i " << i << " PZSol0 " << PzSol[0] << " PzSol[1] " << PzSol[1] << " odd  " << oddnumber << std::endl;


		//Sets which Pz Solution to use efficiently

		if(imaginary[i] && oddnumber) continue;
		Double_t neupz=PzSol[0];
		if(oddnumber) neupz=PzSol[1];

		if(debug) {
			std::cout << "Neutrino pz Solution " << neupz << std::endl;
		}
   
		//use one neutrino pz solution for each combination 
		neupzin[i]=neupz;

		//set the starting value for neutrino pz in the fitter to this value
		vstart[8]=neupz;

		//(parameter number, parameter name, starting value, step size, parameter limits, ierflg)
		for(int j=0;j<nfit;j++){
			//			minuit->mnparm(j, name[j], vstart[j], step[j], low[j] , high[j],ierflg);
			minuit->mnparm(j, name[j], vstart[j], step[j], 0, 0, ierflg);
		}

		// Set error definition
		//minuit->SetErrorDef(1.0) // for Chi2 minimization

		arglist[0]=2;
		minuit->mnexcm("SET STR",arglist,1,ierflg);

		
		//Constrained Fit - if you want to constrain the top mass to a particular value, eg. to look at how well the fitter is working

		//    if( i==0){

		// Fix top quark mass
		arglist[0]=5;
		minuit->mnexcm("FIX",arglist,1,ierflg); //will fix parameter [4] i.e. topmass,in further minimizations 

		// Fix lepton pt
		//		arglist[0]=6;
		//minuit->mnexcm("FIX",arglist,1,ierflg);
		
		//}

		//Want to check that the combination has any b tagged jets in one of the first two elements of the jet array.
		//required because of the jet ordering assumed for the combinations

		bool b0=false,b1=false,b2=false;
		if(btag[combo[0]]>0) b0=true; // leptonic side b-quark
		if(btag[combo[1]]>0) b1=true; // hadronic side b-quark
		if(btag[combo[2]]>0) b2=true; // one for charged Higgs
   

		//gives us a flag if the b tagged jets aren't in the right place so we can ignore these combinations later.
		//the fitter will still fit them for now though

		//		if( ntags==1 && (!b0 && !b1) ) tagconsistent[i]=false;
		//if( ntags==2 && (!b0 && (!b1 && !b2)
		//else tagconsistent[i]=true;


		for(int j=0;j<4;j++){
			int qcorr=0;
			Double_t quark_mass=b_mass;

			//assign the particle jets a different mass to the b jets
			if(j==3){qcorr=1; quark_mass=c_mass;}

			//std::cout << "Jet before TS " << j << " " << jets[j].Pt() <<  std::endl; 
			//apply top specific corrections to the level 5 corrected jets
			tjets[j].SetPtEtaPhiM(tsjetCorr[qcorr][combo[j]]*jets[combo[j]].Pt(),jets[combo[j]].Eta(),jets[combo[j]].Phi(),quark_mass);
			jetsIN[i][j]=tjets[j]; // fully corrected jets

			if(debug) {
				std::cout << "top specific jet corrections for quark : " << qcorr << " = pt "
						  << jets[combo[j]].Pt() << " tscorr "  
						  << tsjetCorr[qcorr][combo[j]] << " eta " << jets[combo[j]].Eta() << std::endl;
			}

			tsigmajets[j]=sigmajets[qcorr][combo[j]];
			JetSigma[i][j]=tsigmajets[j]; // error on fully corrected jets
		}

		tagconsistent[i] = false;
	
		if (ntags == 1){
			if (b0 || b1) tagconsistent[i] = true;
		}
		else if (ntags == 2){
			if (b0 && b1){
				tagconsistent[i] = true; // free b
			}
			//if (b0 && b1) tagconsistent[i] = true;			// b to b
		}
		else if (ntags >=3){
			if (b0 && b1 && b2){
				if (highpt){
					if (tjets[2].Pt()>tjets[1].Pt()) tagconsistent[i] = true;
				}
				else tagconsistent[i] = true;
			} 
		}
		if(debug) std::cout << "1" << std::endl;

		//RUNNING THE MINIMIZATION
		//If you don't want to use errors comment out lines with a // --
		//after them.

		if(debug) {
			std::cout << " **************** Print all inputs ***************" << std::endl;
			std::cout << "Jets : " << jets[0].Pt() << " " << jets[1].Pt() 
					  << " " << jets[2].Pt() << " " << jets[3].Pt() << std::endl;
			std::cout << "TS Jets : " << tjets[0].Pt() << " " << tjets[1].Pt() 
					  << " " << tjets[2].Pt() << " " << tjets[3].Pt() << std::endl;
			std::cout << "TS Jets Sigma : " << tsigmajets[0] << " " << tsigmajets[1] 
					  << " " << tsigmajets[2] << " " << tsigmajets[3] << std::endl;
			std::cout << "lepton : " << Lepton.Pt() << " METx " << met.Px() << " METy " << met.Py() << std::endl;
		}

		arglist[0]=1; // --
		Double_t tchi2,edm,errdef;
		Int_t npari=1,nparx=10,minuit_status=-1;
		
		minuit->mnexcm("CAL",arglist,1,ierflg);  // to call the minuit with FCN
		if(debug)    std::cout << "2" << std::endl;
		minuit->mnexcm("SET NOG",arglist,1,ierflg); // -- no user inputted first derivative
		if(debug)    std::cout << "3" << std::endl;

                arglist[0] = 1;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 2;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 3;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 4;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 6;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 7;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 8;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg);                                                                 
                arglist[0] = 9;                                                                                          
                minuit->mnexcm("SCAN",arglist,1,ierflg); 

		arglist[0]=5000; arglist[1] = 0.1;
		minuit->mnexcm("MINIMIZE",arglist,2,ierflg); // calls simplex, then migrad if this fails                          
		if(debug)    std::cout << "4" << std::endl;                                                                       
		/*
		arglist[0] = 5000;                                                                                                
		minuit->mnexcm("MIGRAD",arglist,1,ierflg); // --                                                                  */
                                                                                                                          
                                                                                                                          
                                                                                                                          
		//      minuit->mnexcm("MINIMIZE",arglist,0,ierflg); // calls simplex, then migrad if this fails                  
		//minuit->mnexcm("MIGRAD",arglist,0,ierflg); // --                                                                
		//minuit->mnexcm("MINOS",arglist,0,ierflg); // --                                                                 
		minuit->mnstat(tchi2,edm,errdef,npari,nparx,minuit_status); // returns current status of the fitting              
		if(debug)    std::cout << "5" << std::endl;                                                                       
		arglist[0]=10000; // --                                                                                           
		arglist[1]=5.; // --                                                                                              
		minuit->mnexcm("HESSE",arglist,1,ierflg);  // -- calculates the error matrix. calls the function 10000 times      
		if(debug)    std::cout << "6" << std::endl;                                                                       
		//    if(!constrained) minuit->mnexcm("MINOS",arglist,2,ierflg); // -- if unconstrained, calculates the MINOS err\
ors on parameter [4]                                                                                                      
  if(debug)    std::cout << "7" << std::endl;                                                            //i.e. top\
mass. calls the function 10000 times                                                                                      
  arglist[0]=1; // --                                                                                               
 if(debug)    std::cout << "8" << std::endl;                                                                       
 minuit->mnexcm("CAL",arglist,1,ierflg); // --                                                                     
 if(debug)    std::cout << "9" << std::endl;       




		//		arglist[0] = 10; arglist[1] = 160; arglist[2] = 0.; arglist[3] = 160.;
		/*
		arglist[0] = 1;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 2;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 3;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 4;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 6;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 7;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 8;
		minuit->mnexcm("SCAN",arglist,1,ierflg);
		arglist[0] = 9;
		minuit->mnexcm("SCAN",arglist,1,ierflg);


		arglist[0] = 5000; arglist[1] = 0.1;
		minuit->mnexcm("MINIMIZE",arglist,2,ierflg); // calls simplex, then migrad if this fails
		if(debug)    std::cout << "4" << std::endl;

		//		arglist[0] = 5000;
		//minuit->mnexcm("MIGRAD",arglist,2,ierflg); // --
		

		//		minuit->mnexcm("MINIMIZE",arglist,0,ierflg); // calls simplex, then migrad if this fails
		//arglist[0] = 1000;
		//minuit->mnexcm("MINOS",arglist,1,ierflg); // --

		minuit->mnstat(tchi2,edm,errdef,npari,nparx,minuit_status); // returns current status of the fitting
		if(debug)    std::cout << "5" << std::endl;

		arglist[0]=1000; // --
		arglist[1]=5.; // --
		minuit->mnexcm("HESSE",arglist,1,ierflg);  // -- calculates the error matrix. calls the function 10000 times
		if(debug)    std::cout << "6" << std::endl;

		minuit->mnexcm("MINOS",arglist,0,ierflg); // -- if unconstrained, calculates the MINOS errors on parameter [4]

		if(debug)    std::cout << "7" << std::endl;                                                            //i.e. topmass. calls the function 10000 times
		arglist[0]=1; // --
		if(debug)    std::cout << "8" << std::endl;

		//	minuit->mnexcm("CAL",arglist,1,ierflg); // --
		if(debug)    std::cout << "9" << std::endl;

		*/
		//Grab the parameters for this fit
		//returns parameter value and error

		for (int j=0;j<nfit;j++) {
			minuit->GetParameter(j,value[j],Error[i][j]);
		}
    

		//Grab the Chi2 for each combination
		Chi2[i]=tchi2;
		LeptonChi[i]=tleptonchi;
		UnclXChi[i]=tunclxchi;
		UnclYChi[i]=tunclychi;
		LepWChi[i]=tlepwchi;
		HadWChi[i]=thadwchi;
		HadTopChi[i]=thadtopchi;
		LepTopChi[i]=tleptopchi;
		JetChi[0][i]=tjet0chi;
		JetChi[1][i]=tjet1chi;
		JetChi[2][i]=tjet2chi;
		JetChi[3][i]=tjet3chi;

		if (debug){

			std::cout << " All chi2 combination : " << JetChi[0][i] << ", " << JetChi[1][i] << ", " << JetChi[2][i] << ", " << JetChi[3][i] << ", " << LeptonChi[i] << ", TopChi2 = " << HadTopChi[i] << ", " << LepTopChi[i] << ", uncl = " << UnclXChi[i] << ", " << UnclYChi[i] << ", W chi = " << LepWChi[i] << ", " << HadWChi[i] << std::endl;

		}

		//topmass for each combination is the 5th parameter in the array
		Mass[i]=value[4];
		HMass[i] = value[9];
							   
		//gets best chisquared and mass values for the event
		//Commented out to test tag consistency
		if( (Chi2[i] < bestchi2) && tagconsistent[i] ){
			bestchi2 = Chi2[i];
			bestmass = Mass[i];
			bestHmass = HMass[i];
			sol = i;
		}


		//Dummy vars that we don't use
		Double_t temp1, temp2;
		if(debug)    std::cout << "10" << std::endl;
		//Get asymm. minos error for each top mass combination
		//(parameter number, +ve error, -ve error, some other things we don't need) 
		minuit->mnerrs(4,mtop_error_p[i],mtop_error_m[i], temp1, temp2);


		//Set jets for this fit
		//jets are altered by the fitting process
		for(int j=0;j<4;j++){
			
			//b jets
			int qcorr=0;
			Double_t quarkmass=b_mass;
			
			//particle jets
			if(j==3){
				qcorr=1; 
				quarkmass=c_mass;
			}
			
		
			//jets are the first 4 entries in the array value[nfit]
			//each jet pt is scaled by a different amount
			//eta, phi, mass remain the same - same as level 5 corrected, since ts corrections also don't affect these
			
			Double_t fitjetpt=value[j]*tsjetCorr[qcorr][combo[j]]*jets[combo[j]].Pt();
			
			FittedJets[i][j].SetPtEtaPhiM(fitjetpt,jets[combo[j]].Eta(),jets[combo[j]].Phi(),quarkmass);
			if (debug) std::cout << FittedJets[i][j].Pt() << std::endl;
		}
		
		if(debug)    std::cout << "11" << std::endl;
		
		//Set leptons for this fit
		//lepton is scaled by value[5]
		FittedLep[i].SetPtEtaPhiM(value[5]*Lepton.Pt(),Lepton.Eta(),Lepton.Phi(),Lepton.M());
		if(debug)    std::cout << "12 lep pt " << FittedLep[i].Pt() << std::endl;
		//find total px and py of the jets
		
		Double_t FitSumJetPx=FittedJets[i][0].Px()+FittedJets[i][1].Px()+FittedJets[i][2].Px()+FittedJets[i][3].Px();
		Double_t FitSumJetPy=FittedJets[i][0].Py()+FittedJets[i][1].Py()+FittedJets[i][2].Py()+FittedJets[i][3].Py();
		if(debug)    std::cout << "13 SumJet = " << FitSumJetPx << " & " << FitSumJetPy << std::endl;
		// fitted neutrino px and py must balance the jet, unclustered and electron momenta
		
		Double_t FitneuPx = -FitSumJetPx - FittedLep[i].Px() - value[6]*uncl.Px();
		Double_t FitneuPy = -FitSumJetPy - FittedLep[i].Py() - value[7]*uncl.Py();
		if(debug)    std::cout << "14" << std::endl;
		//set neutrino 4 vector for each combination (px, py, pz, E)
		if (debug) std::cout << " Fit Neu = " << FitneuPx << ", " << FitneuPy << ", " << value[8] << ", " << std::endl;
		
		FittedNeu[i].SetPxPyPzE(FitneuPx,FitneuPy,value[8],sqrt(FitneuPx*FitneuPx+FitneuPy*FitneuPy+value[8]*value[8]));
		
		if(debug)    std::cout << "15 :  "  << i << "  "<<  FittedJets[i][0].Eta() << " "  << FittedJets[i][1].Eta() << " " << FittedJets[i][2].Eta() << " " << FittedJets[i][3].Eta() << " "<<std::endl;

		for(int j = 0;j<4;j++){
			Scale[i][j] = (FittedJets[i][j].Pt()-jetsIN[i][j].Pt())/JetSigma[i][j];
		}
		Scale[i][4] = (FittedLep[i].Pt()-Lepton.Pt())/LeptonSigma;
		Scale[i][5] = (value[6]*uncl.Px()-uncl.Px())/sigmauncl;
		Scale[i][6] = (value[7]*uncl.Py()-uncl.Py())/sigmauncl;

		Out[i][0] = value[0];
		Out[i][1] = value[1];
		Out[i][2] = value[2];
		Out[i][3] = value[3];
		Out[i][4] = value[4];
		Out[i][5] = value[5];
		Out[i][6] = value[6];
		Out[i][7] = value[7];
		Out[i][8] = value[8];
		//		Out[i][9] = value[9];



		//Clear par[] values for next combo
		minuit->Clear();
		if(debug)    std::cout << "16" << std::endl;
	}


	if(debug)  std::cout << "17 " <<  std::endl;
	//Delete it after looping over all combinations
	minuit->Delete();
}



//////The Chi2 Function
void TTFitter::fcn(Int_t &npar,Double_t *gin,Double_t &f, Double_t *par,Int_t iflag){

	//this is the chi squared value
	f=0.0;
	bool debug = false;

	if(debug)  std::cout << "f initial = " << f << std::endl;
  
	// EMB changed these from SetPtEtaPhiM to SetXYZM to save CPU time.

	if(debug)  std::cout << "all parameters " << par[0] << " " << par[1] << " " << par[4] << std::endl;

	Double_t ap = 0;
	if(debug)  std::cout << "ap = " << ap << std::endl;
	//loop over jets. fit gives a scaling value for each jet parameter. scale the original top specific corrected jets by this amount

	if(debug)  std::cout << "jets" << std::endl;
	for (int i=0;i<4;i++) {
		if(debug)    std::cout << "jet px " << i << "= " << tjets[i].Px() << std::endl; 
		ap = TMath::Abs(par[i]);
		if(debug)    std::cout << "ap = " << ap << std::endl;
		//		fitjets[i].SetXYZM(ap*tjets[i].Px(),ap*tjets[i].Py(), ap*tjets[i].Pz(),tjets[i].M());
		fitjets[i].SetPtEtaPhiM(ap*tjets[i].Pt(),tjets[i].Eta(),tjets[i].Phi(),tjets[i].M());
		if(debug)    std::cout << "fitted jets " << i << "Pt = " << fitjets[i].Pt() << std::endl;
	}


	//do the samething for the electron
	if(debug)  std::cout << "electron" << std::endl;
	ap = TMath::Abs(par[5]);
	if(debug)  std::cout << "ap = " << ap << std::endl;
	//	fitlep.SetXYZM(ap*tlepton.Px(),ap*tlepton.Py(), ap*tlepton.Pz(),tlepton.M());
	fitlep.SetPtEtaPhiM(ap*tlepton.Pt(),tlepton.Eta(),tlepton.Phi(),tlepton.M());
	if(debug)  std::cout << "fitted lepton pt = " << fitlep.Pt() << std::endl;
  

	//the chi squared definitions...
	//sum over all jets part
	for (int i=0;i<4;i++){

		f += (tjets[i].Pt()-fitjets[i].Pt())*(tjets[i].Pt()-fitjets[i].Pt())/(tsigmajets[i]*tsigmajets[i]);

		if(i==0)tjet0chi = (tjets[i].Pt()-fitjets[i].Pt())*(tjets[i].Pt()-fitjets[i].Pt())/(tsigmajets[i]*tsigmajets[i]);
		if(i==1)tjet1chi = (tjets[i].Pt()-fitjets[i].Pt())*(tjets[i].Pt()-fitjets[i].Pt())/(tsigmajets[i]*tsigmajets[i]);
 		if(i==2)tjet2chi = (tjets[i].Pt()-fitjets[i].Pt())*(tjets[i].Pt()-fitjets[i].Pt())/(tsigmajets[i]*tsigmajets[i]);
		if(i==3)tjet3chi = (tjets[i].Pt()-fitjets[i].Pt())*(tjets[i].Pt()-fitjets[i].Pt())/(tsigmajets[i]*tsigmajets[i]);
		if (debug) std::cout << " Jet f " << fitjets[i].Pt() << "(" << tsigmajets[i] << ") = " << (tjets[i].Pt()-fitjets[i].Pt())*(tjets[i].Pt()-fitjets[i].Pt())/(tsigmajets[i]*tsigmajets[i]) << endl;
	}
	

	// lepton
	// LeptonChi = pow(tlepton.Pt()-fitlep.Pt(),2)/pow(sigmalep,2);

	f += (tlepton.Pt()-fitlep.Pt())*(tlepton.Pt()-fitlep.Pt())/(sigmalep*sigmalep);
	tleptonchi = (tlepton.Pt()-fitlep.Pt())*(tlepton.Pt()-fitlep.Pt())/(sigmalep*sigmalep);

	if(debug) std::cout << "Sigmalep = " << tlepton.Pt() << "(" << sigmalep << "): leptonchi2 = " << tleptonchi << std::endl;
	if(debug)  std::cout << "f = "<< f << std::endl;
	if(debug)  std::cout << "end of event" << std::endl;

	// UnclXChi =  pow(uncl.Px()*(1-par[6]),2)/pow(sigmauncl,2);
	// UnclYChi = pow(uncl.Py()*(1-par[7]),2)/pow(sigmauncl,2);
	f += (uncl.Px()*(1-par[6]))*(uncl.Px()*(1-par[6]))/(sigmauncl*sigmauncl);
	tunclxchi = (uncl.Px()*(1-par[6]))*(uncl.Px()*(1-par[6]))/(sigmauncl*sigmauncl);
	f += (uncl.Py()*(1-par[7]))*(uncl.Py()*(1-par[7]))/(sigmauncl*sigmauncl);
	tunclychi = (uncl.Py()*(1-par[7]))*(uncl.Py()*(1-par[7]))/(sigmauncl*sigmauncl);

	//WmassMod on hadronic side - add together the two light jets
	Wjj=fitjets[2]+fitjets[3];

	// hadronic W part of the chi squared
	//	HadWChi = pow(par[9]-Wjj.M(),2)/pow(Wwidth,2);

	// Constrain hadtop mass for ttbar resonance check
	f+=(par[9]-Wjj.M())*(par[9]-Wjj.M())/(Wwidth*Wwidth); 
	thadwchi = (par[9]-Wjj.M())*(par[9]-Wjj.M())/(Wwidth*Wwidth); 
	//thadwchi = Wjj.M();
 	
	//Top on hadronic side

	hTop=fitjets[1]+fitjets[2]+fitjets[3];
	//  f+=pow(par[4]-hTop.M(),2)/pow(TopwidthMod*1000.,2);
	//	HadTopChi = pow(par[4]-hTop.M(),2)/pow(Topwidth,2);
	f+=(par[4]-hTop.M())*(par[4]-hTop.M())/(Topwidth*Topwidth); // in previous code. commeneted out
	thadtopchi = (par[4]-hTop.M())*(par[4]-hTop.M())/(Topwidth*Topwidth); // not seen in previous code

	//Recalculate MET based on new jets and unclustered energy
	Double_t SumJetPx=fitjets[0].Px()+fitjets[1].Px()+fitjets[2].Px()+fitjets[3].Px();
	Double_t SumJetPy=fitjets[0].Py()+fitjets[1].Py()+fitjets[2].Py()+fitjets[3].Py();
	Double_t neuPx = -SumJetPx - fitlep.Px() - par[6]*uncl.Px() - addjet.Px();
	Double_t neuPy = -SumJetPy - fitlep.Py() - par[7]*uncl.Py() - addjet.Py();

	fitneu.SetPxPyPzE(neuPx,neuPy,par[8],sqrt(neuPx*neuPx+neuPy*neuPy+par[8]*par[8]));

	//get unclustered energy scale factors
	//ap = TMath::Abs(par[6]);
	//ap = TMath::Abs(par[7]);
  
	//WmassMod on leptonic side
	//should be zero due to constraining this side to = wmass to work out neutrino pz
	Wlv=fitneu+fitlep;
	//	LepWChi = pow(Wmass-Wlv.M(),2)/pow(Wwidth,2);
	f+=(Wmass-Wlv.M())*(Wmass-Wlv.M())/(Wwidth*Wwidth);
	tlepwchi = (Wmass-Wlv.M())*(Wmass-Wlv.M())/(Wwidth*Wwidth);

	//Top on leptonic side 
	lTop=fitjets[0]+fitlep+fitneu;
	//	LepTopChi = pow(par[4]-lTop.M(),2)/pow(Topwidth,2); 
	f+=(par[4]-lTop.M())*(par[4]-lTop.M())/(Topwidth*Topwidth); 
	tleptopchi=(par[4]-lTop.M())*(par[4]-lTop.M())/(Topwidth*Topwidth); 

	if (debug) std::cout << " Chi2 = " << tleptonchi << ", " << tunclxchi << ", " << tunclychi << ", " << thadwchi << ", " << thadtopchi << ", " << tlepwchi << ", " << tleptopchi << endl;

	//Double_t deltaM = 0.5*( lTop.M() - hTop.M() );

	//OLD METHOD

	//   f+=pow( ( ( lTop.M() - (172.5*1000 - deltaM))/1500. ), 2);
	//    f+=pow( ( ( hTop.M() - (172.5*1000 + deltaM))/1500. ), 2);

	//   thadtopchi = pow( ( ( hTop.M() - (172.5*1000 + deltaM))/1500. ), 2);
	//   tleptopchi = pow( ( ( lTop.M() - (172.5*1000 - deltaM))/1500. ), 2);


	// NEW METHOD

	//	f+=pow( ( ( lTop.M() - (172.5*1000 - 0.5*par[4]))/1500. ), 2);
	//f+=pow( ( ( hTop.M() - (172.5*1000 + 0.5*par[4]))/1500. ), 2);

	//	tleptopchi = pow( ( ( lTop.M() - (172.5*1000 - 0.5*par[4]))/1500. ), 2);
	//thadtopchi = pow( ( ( hTop.M() - (172.5*1000 + 0.5*par[4]))/1500. ), 2);

	//  par4=value[4];


	//pow((lTop.M()+hTop.M())/2-(175*1000),2)/pow(1500,2);

}

void TTFitter::GetTSCorr(TLorentzVector jets_f[4], Int_t tstype, Bool_t debug){

	switch(tstype){
		
	case 1:	// CDF function on CMS 8TeV data	
		
		if (debug)
			cout << " Called CDF type function " << endl;
		
		for (int i=0; i<4; i++){
			float jetPt = jets_f[i].Pt();
			float jetEta = fabs(jets_f[i].Eta());
			
			// b quarks correction
			Double_t par0_b = exp(-0.4028 -0.001353*jetEta*jetEta) -0.6932;
			Double_t par1_b = exp(-0.6897-0.02032*jetEta*jetEta)-0.9896;
			Double_t par2_b = exp(-0.5035 + 0.002973*jetEta*jetEta)-0.6469;
			Double_t meanb = exp(par1_b+par0_b*jetPt) + par2_b;
			tsjetCorr[0][i]=1+meanb;
			// c quarks correction
			Double_t par0_c = exp(-0.4883 -0.00196*jetEta*jetEta) -0.6378;
			Double_t par1_c = exp(-0.9743-0.0359*jetEta*jetEta) - 1.272;
			Double_t par2_c = exp(0.2394 +0.001948*jetEta*jetEta)-1.304;
			Double_t meanc = exp(par1_c+par0_c*jetPt) + par2_c;
			tsjetCorr[1][i]=1+meanc;
			// l quarks correctiion			
			Double_t par0_l = exp(0.2427 -0.001001*jetEta*jetEta) - 1.3;
			Double_t par1_l = exp(1.694 -0.00577*jetEta*jetEta) - 6.539;
			Double_t par2_l = exp(1.801 + 0.0003077*jetEta*jetEta) - 6.109;
			Double_t meanl = exp(par1_l+par0_l*jetPt) + par2_l;
			tsjetCorr[2][i]=1+meanl;

			// b quarks correction error
			Double_t par0_b_sigma = exp(-0.4002 -0.003295*jetEta*jetEta) -0.6893;
			Double_t par1_b_sigma = exp(-1.85 +0.2643*jetEta*jetEta) -1.458;
			Double_t par2_b_sigma = exp(-0.5496+0.002501*jetEta*jetEta) - 0.4477;
			Double_t meanb_sigma = exp(par1_b_sigma+par0_b_sigma*jetPt) + par2_b_sigma;
			sigmajets[0][i]=jetPt*meanb_sigma;
			// c quarks correction error
			Double_t par0_c_sigma = exp(-0.6681 -0.005062*jetEta*jetEta) - 0.5315;
			Double_t par1_c_sigma = exp(0.2011 +0.06194*jetEta*jetEta) -2.624;
			Double_t par2_c_sigma = exp(1.033 +0.000853*jetEta*jetEta) - 2.691;
			Double_t meanc_sigma = exp(par1_c_sigma+par0_c_sigma*jetPt) + par2_c_sigma;
			sigmajets[1][i]=jetPt*meanc_sigma;
			// l quarks correction error
			Double_t par0_l_sigma = exp(1.009 - 0.001183*jetEta*jetEta) -2.764;
			Double_t par1_l_sigma = exp(0.7738 +0.04549*jetEta*jetEta) -3.607;
			Double_t par2_l_sigma = exp(1.258 +0.0004952*jetEta*jetEta) -3.397;
			Double_t meanl_sigma = exp(par1_l_sigma+par0_l_sigma*jetPt) + par2_l_sigma;
			sigmajets[2][i]=jetPt*meanl_sigma;

			if (debug){
				cout << " = = for jets " << i << ": cor_b " << tsjetCorr[0][i] << "(" << sigmajets[0][i]
					 << ") , cor_c " << tsjetCorr[1][i] << "(" << sigmajets[1][i] << "), cor_l " << tsjetCorr[2][i]
					 << "(" << sigmajets[2][i] << ")" << endl;
			}

		}

		if (debug)
			cout << " CDF type TS-fit is called!!!! " << endl;
		break;
		
	case 2: // ATLAS function on CMS 8TeV data
		
		for (int i=0; i<4; i++){

			float jetPt = jets_f[i].Pt();
			float jetEta = fabs(jets_f[i].Eta());
				
			// b quarks correction
			Double_t par0_b = -0.5297 +1.258*TMath::Abs(jetEta) -0.2728*jetEta*jetEta;
			Double_t par1_b = -0.0001426 + 6.235e-5*TMath::Abs(jetEta) -4.857e-7*jetEta*jetEta;
			Double_t par2_b = 12.75 -7.423*TMath::Abs(jetEta) + 1.431*jetEta*jetEta;
			Double_t par3_b = -0.3475 -1.919*TMath::Abs(jetEta) + 1.431*jetEta*jetEta;
			Double_t meanb = exp(par0_b+par1_b*jetPt+par2_b/jetPt) + par3_b;
			tsjetCorr[0][i]=1+meanb;
			// c quarks correction
			Double_t par0_c = -0.06705 -0.4741*TMath::Abs(jetEta) + 0.3737*jetEta*jetEta;
			Double_t par1_c = -0.0001284 -0.0001415*TMath::Abs(jetEta) - 0.0001047*jetEta*jetEta;
			Double_t par2_c = 6.844+3.85*TMath::Abs(jetEta)-2.733*jetEta*jetEta;
			Double_t par3_c = -1.043 + 0.3737*TMath::Abs(jetEta)-0.3408*jetEta*jetEta;
			Double_t meanc = exp(par0_c+par1_c*jetPt+par2_c/jetPt) + par3_c;
			tsjetCorr[1][i]=1+meanc;
			// l quarks correctiion			
			Double_t par0_l = 0.2559 -2.209*TMath::Abs(jetEta)+0.5559*jetEta*jetEta;
			Double_t par1_l = -0.0003863 -0.0002383*TMath::Abs(jetEta) - 0.0003858*jetEta*jetEta;
			Double_t par2_l = 4.868+25.25*jetEta-6.878*jetEta*jetEta;
			Double_t par3_l = -0.8366 +0.9677*jetEta -0.3037*jetEta*jetEta;
			Double_t meanl = exp(par0_l+par1_l*jetPt+par2_l/jetPt) + par3_l;
			tsjetCorr[2][i]=1+meanl;

			if (debug)
				cout << "Bcorr = " << tsjetCorr[0][i] << ", Ccorr = " << tsjetCorr[1][i] << ", Lcorr = " << tsjetCorr[2][i] << endl;

			
			// b quarks correction error
			Double_t par0_b_sigma = 0.0613 + 0.01513*TMath::Abs(jetEta) -0.01097*jetEta*jetEta;
			Double_t par1_b_sigma = 6.118e-6 -0.0001551*TMath::Abs(jetEta) + 0.0001114*jetEta*jetEta;
			Double_t par2_b_sigma = 5.064 -0.4467*TMath::Abs(jetEta) + 0.5232*jetEta*jetEta;
			Double_t par3_b_sigma = -0.9565 +0.01925*TMath::Abs(jetEta) -0.01413*jetEta*jetEta;				
			Double_t meanb_sigma = exp(par0_b_sigma+par1_b_sigma*jetPt+par2_b_sigma/jetPt) + par3_b_sigma;
			sigmajets[0][i]=jetPt*meanb_sigma;
			// c quarks correction error
			Double_t par0_c_sigma = 0.0613 +0.001511*TMath::Abs(jetEta) - 0.004356*jetEta*jetEta;
			Double_t par1_c_sigma = 0.001418 -0.03816*TMath::Abs(jetEta) +0.001632*jetEta*jetEta;
			Double_t par2_c_sigma = 4.325+0.6216*TMath::Abs(jetEta)-0.007*jetEta*jetEta;
			Double_t par3_c_sigma = -0.9526 +0.002823*TMath::Abs(jetEta) -0.005781*jetEta*jetEta;
			Double_t meanc_sigma = exp(par0_c_sigma+par1_c_sigma*jetPt+par2_c_sigma/jetPt) + par3_c_sigma;
			sigmajets[1][i]=jetPt*meanc_sigma;
			// l quarks correction error
			Double_t par0_l_sigma = 0.05333+0.003006*TMath::Abs(jetEta) - 0.005037*jetEta*jetEta;
			Double_t par1_l_sigma = 2.073e-5 - 3.305e-5*TMath::Abs(jetEta) +5.587e-5*jetEta*jetEta;
			Double_t par2_l_sigma = 4.023 +0.7825*TMath::Abs(jetEta) -0.07408*jetEta*jetEta;
			Double_t par3_l_sigma = -0.9598 +0.004307*TMath::Abs(jetEta) - 0.006502*jetEta*jetEta;
			Double_t meanl_sigma = exp(par0_l_sigma+par1_l_sigma*jetPt+par2_l_sigma/jetPt) + par3_l_sigma;
			sigmajets[2][i]=jetPt*meanl_sigma;
		}

		if (debug)
			cout << " ATLAS type TS-fit is called!!!! " << endl;				

		break;

	case 3: // ATLAS&CDF modified version on CMS 8TeV ttbar MC
		
		for (int i=0; i<4; i++){

			float jetPt = jets_f[i].Pt();
			float jetEta = fabs(jets_f[i].Eta());

			Double_t par0_b = 0, par1_b = 0, par2_b = 0, meanb = 0;
			Double_t par0_c = 0, par1_c = 0, par2_c = 0, meanc = 0;
			Double_t par0_l = 0, par1_l = 0, par2_l = 0, meanl = 0;

			if (jetPt<150){
				// b quarks correction
				par0_b = exp(-0.4028 - 0.001353*jetEta*jetEta) - 0.6932;
				par1_b = exp(-0.6897 - 0.02032*jetEta*jetEta) - 0.9896;
				par2_b = exp(-0.5035 + 0.002973*jetEta*jetEta) - 0.6469;
				meanb = exp(jetPt*par0_b+par1_b)+par2_b;
				tsjetCorr[0][i]=1+meanb;

				// c quarks correction
				par0_c = exp(-0.1836-0.001579*jetEta*jetEta) - 0.8564;
				par1_c = exp(-0.5802-0.02413*jetEta*jetEta) - 1.454;
				par2_c = exp(0.4341+0.001634*jetEta*jetEta) - 1.577;
				meanc = exp(par0_c*jetPt+par1_c)+par2_c;
				tsjetCorr[1][i]=1+meanc;

				// l quarks correctiion			
				par0_l = exp(0.2427-0.001001*jetEta*jetEta) - 1.3;
				par1_l = exp(1.53-0.006814*jetEta*jetEta) - 5.714;
				par2_l = exp(1.659+0.0003559*jetEta*jetEta) - 1.577;
				meanl = exp(par0_l*jetPt+par1_l)+par2_l;
				tsjetCorr[2][i]=1+meanl;
			}
			else{
				Double_t q0_b = 0, q1_b = 0;
				Double_t q0_c = 0, q1_c = 0;
				Double_t q0_l = 0, q1_l = 0;

				// b quarks correction
				q0_b = exp(-3.914+0.5794*jetEta*jetEta)+0.0863;
				q1_b = exp(-5.789-0.001735*jetEta*jetEta)+0.002668;
				par0_b = exp(-0.4028 - 0.001353*jetEta*jetEta) - 0.6932;
				par1_b = exp(-0.6897 - 0.02032*jetEta*jetEta) - 0.9896;
				par2_b = exp(-0.5035 + 0.002973*jetEta*jetEta) - 0.6469;
				meanb = (q0_b+q1_b*jetPt)*(exp(jetPt*par0_b+par1_b)+par2_b);
				tsjetCorr[0][i]=1+meanb;

				// c quarks correction
				q0_c = exp(0.4618+0.06592*jetEta*jetEta) - 1.552;
				q1_c = exp(0.4387-0.0003031*jetEta*jetEta)-1.544;
				par0_c = exp(-0.1836-0.001579*jetEta*jetEta) - 0.8564;
				par1_c = exp(-0.5802-0.02413*jetEta*jetEta) - 1.454;
				par2_c = exp(0.4341+0.001634*jetEta*jetEta) - 1.577;
				meanc = (q0_c+q1_c*jetPt)*(exp(par0_c*jetPt+par1_c)+par2_c);
				tsjetCorr[1][i]=1+meanc;

				// l quarks correctiion			
				q0_l = exp(1.713+0.004909*jetEta*jetEta) - 5.061;
				q1_l = exp(1.671-2.21e-6*jetEta*jetEta)-5.314;
				par0_l = exp(0.2427-0.001001*jetEta*jetEta) - 1.3;
				par1_l = exp(1.53-0.006814*jetEta*jetEta) - 5.714;
				par2_l = exp(1.659+0.0003559*jetEta*jetEta) - 1.577;
				meanl = (q0_l+q1_l*jetPt)*(exp(par0_l*jetPt+par1_l)+par2_l);
				tsjetCorr[2][i]=1+meanl;				
			}			
			
			if (debug)
				cout << "Bcorr = " << tsjetCorr[0][i] << ", Ccorr = " << tsjetCorr[1][i] << ", Lcorr = " << tsjetCorr[2][i] << endl;

			// b quarks correction error
			Double_t par0_b_sigma = 0.0613 + 0.01513*TMath::Abs(jetEta) -0.01097*jetEta*jetEta;
			Double_t par1_b_sigma = 6.118e-6 -0.0001551*TMath::Abs(jetEta) + 0.0001114*jetEta*jetEta;
			Double_t par2_b_sigma = 5.064 -0.4467*TMath::Abs(jetEta) + 0.5232*jetEta*jetEta;
			Double_t par3_b_sigma = -0.9565 +0.01925*TMath::Abs(jetEta) -0.01413*jetEta*jetEta;				
			Double_t meanb_sigma = exp(par0_b_sigma+par1_b_sigma*jetPt+par2_b_sigma/jetPt) + par3_b_sigma;
			sigmajets[0][i]=jetPt*meanb_sigma;
			// c quarks correction error
			Double_t par0_c_sigma = 0.0613 +0.001511*TMath::Abs(jetEta) - 0.004356*jetEta*jetEta;
			Double_t par1_c_sigma = -5e-5 -4.196e-6*TMath::Abs(jetEta) +4.189e-5*jetEta*jetEta;
			Double_t par2_c_sigma = 4.325+0.6216*TMath::Abs(jetEta)-0.007*jetEta*jetEta;
			Double_t par3_c_sigma = -0.9526 +0.002823*TMath::Abs(jetEta) -0.005781*jetEta*jetEta;
			Double_t meanc_sigma = exp(par0_c_sigma+par1_c_sigma*jetPt+par2_c_sigma/jetPt) + par3_c_sigma;
			sigmajets[1][i]=jetPt*meanc_sigma;
			// l quarks correction error
			Double_t par0_l_sigma = 0.05333+0.003006*TMath::Abs(jetEta) - 0.005037*jetEta*jetEta;
			Double_t par1_l_sigma = 2.073e-5 - 3.305e-5*TMath::Abs(jetEta) +5.587e-5*jetEta*jetEta;
			Double_t par2_l_sigma = 4.023 +0.7825*TMath::Abs(jetEta) -0.07408*jetEta*jetEta;
			Double_t par3_l_sigma = -0.9598 +0.004307*TMath::Abs(jetEta) - 0.006502*jetEta*jetEta;
			Double_t meanl_sigma = exp(par0_l_sigma+par1_l_sigma*jetPt+par2_l_sigma/jetPt) + par3_l_sigma;
			sigmajets[2][i]=jetPt*meanl_sigma;

			if (debug)
				cout << "BcorrSig = " << sigmajets[0][i] << ", CcorrSig = " << sigmajets[1][i] << ", LcorrSig = " << sigmajets[2][i] << endl;

		}

		if (debug)
			cout << " tstype 3: ATLAS type TS-fit is called!!!! " << endl;				

		break;
		
	case 4: // New matching with dR<0.3

		for (int i=0; i<4; i++){

			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());
			
			Double_t par0_b = 1.54+0.01749*eta+0.02179*eta*eta;
			Double_t par1_b = -3.564e-05-2.479e-05*eta-8.877e-07*eta*eta;
			Double_t par2_b = 2.379+0.0118*eta-0.1908*eta*eta;
			Double_t par3_b = -4.759-0.05273*eta-0.1138*eta*eta;
			Double_t meanb = exp(par0_b+par1_b*pt+par2_b/pt)+par3_b;
			
			tsjetCorr[0][i] = (1+meanb);
       
			Double_t par0_c = 1.706-0.0009564*eta+0.0009618*eta*eta;
			Double_t par1_c = -6.538e-05+5.621e-06*eta-1.088e-05*eta*eta;
			Double_t par2_c = 1.153+0.1856*eta-0.1559*eta*eta;
			Double_t par3_c = -5.548-0.005825*eta+0.005751*eta*eta;
			Double_t meanc = exp(par0_c+par1_c*pt+par2_c/pt)+par3_c;       
	
			tsjetCorr[1][i] = (1+meanc);
   
			Double_t par0_l = 1.705-0.003095*eta+0.001912*eta*eta;
			Double_t par1_l = -6.81e-05+2.803e-05*eta-2.11e-05*eta*eta;
			Double_t par2_l = 0.9185+0.2402*eta-0.1851*eta*eta;
			Double_t par3_l = -5.556-0.01773*eta+0.01099*eta*eta;
			Double_t meanl = exp(par0_l+par1_l*pt+par2_l/pt)+par3_l;
   
			tsjetCorr[2][i] = (1+meanl);
    
			Double_t sig_par0_b  =  0.05908+0.01142*eta-0.01194*eta*eta;
			Double_t sig_par1_b = 0.0002182-0.0001932*eta+0.0001922*eta*eta;
			Double_t sig_par2_b =  5.618-0.216*eta+0.581*eta*eta;
			Double_t sig_par3_b =  -0.9634+0.01872*eta-0.01872*eta*eta;
			Double_t meanb_sigma = exp(sig_par0_b+sig_par1_b*pt+sig_par2_b/pt)+sig_par3_b;
				
			sigmajets[0][i]=pt*meanb_sigma;

			double sig_par0_c = 0.05394-0.0003886*eta-0.003976*eta*eta;
			double sig_par1_c = 0.0002935-0.00008158*eta+0.0001157*eta*eta;
			double sig_par2_c = 5.036+0.7538*eta-0.05933*eta*eta;
			double sig_par3_c = -0.9593+0.001623*eta-0.00681*eta*eta;
			double meanc_sigma = exp(sig_par0_c+sig_par1_c*pt+sig_par2_c/pt)+sig_par3_c;

			sigmajets[1][i] = pt*meanc_sigma;

			double sig_par0_l = 0.04953+0.004158*eta-0.00693*eta*eta;
			double sig_par1_l = 0.0003372-0.0001478*eta+0.0001603*eta*eta;
			double sig_par2_l = 4.629+0.5326*eta+0.1178*eta*eta;
			double sig_par3_l = -0.9589+0.007753*eta-0.01115*eta*eta;
			double meanl_sigma = exp(sig_par0_l+sig_par1_l*pt+sig_par2_l/pt)+sig_par3_l;

			sigmajets[2][i] = pt*meanl_sigma;
				
		}
		
		if (debug)
			cout << " tstype 4: Test version TS-fit is called!!!! " << endl;				

		break;


	case 5: // new matching dR<0.3 && Follow the method from Idiogram top mass analysis  AN-13-037

		for (int i=0; i<4; i++){

			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());
			
			Double_t par0_b, par1_b, par2_b, par3_b;
			Double_t par0_c, par1_c, par2_c, par3_c;
			Double_t par0_l, par1_l, par2_l, par3_l;

			Double_t sig_par0_b, sig_par1_b, sig_par2_b;
			Double_t sig_par0_c, sig_par1_c, sig_par2_c;
			Double_t sig_par0_l, sig_par1_l, sig_par2_l;
 
			if(eta<0.174){
				par0_b=0.5462; par1_b=-0.05533; par2_b=-15.74; par3_b=0.001753;
				par0_c=0.3651; par1_c=-0.04316; par2_c=-9.044; par3_c=0.001648;
				par0_l=0.2564; par1_l=-0.02857; par2_l=-6.072; par3_l=0.001157;

				sig_par0_b=0.359; sig_par1_b=-0.03733;  sig_par2_b=0.001297;
				sig_par0_c=0.3755;  sig_par1_c=-0.03945;  sig_par2_c=0.001398;				
				sig_par0_l=0.3769;  sig_par1_l=-0.04058;  sig_par2_l=0.001455;
				
			}
			else if(eta<0.348){
				par0_b=0.5462; par1_b=-0.05534; par2_b=-15.74; par3_b=0.001753;
				par0_c=0.2208; par1_c=-0.02248; par2_c=-7.222; par3_c=0.0008414;
				par0_l=0.2566; par1_l=-0.0286; par2_l=-6.012; par3_l=0.00115;

				sig_par0_b=0.3758;  sig_par1_b=-0.04093;  sig_par2_b=0.001472;
				sig_par0_c=0.3929;  sig_par1_c=-0.04307;  sig_par2_c=0.001563;
				sig_par0_l=0.3886;  sig_par1_l=-0.04368;  sig_par2_l=0.001624;
									  
			}
			else if(eta<0.522){
				par0_b=0.546; par1_b=-0.05542; par2_b=-15.69; par3_b=0.00174;
				par0_c=0.2203; par1_c=-0.02256; par2_c=-7.193; par3_c=0.0008311;
				par0_l=0.2565; par1_l=-0.02865; par2_l=-5.971; par3_l=0.001142;

				sig_par0_b=0.3758;  sig_par1_b=-0.04093;  sig_par2_b=0.001472;
				sig_par0_c=0.3721; sig_par1_c=-0.0392;  sig_par2_c=0.001392;
				sig_par0_l=0.3764; sig_par1_l=-0.04074; sig_par2_l=0.001468;
																		
			}
			else if(eta<0.696){
				par0_b=0.5462; par1_b=-0.05543; par2_b=-15.62; par3_b=0.001738;
				par0_c=0.2206; par1_c=-0.02253; par2_c=-7.178; par3_c=0.0008341;
				par0_l=0.2568; par1_l=-0.0286; par2_l=-5.996; par3_l=0.001149;

				sig_par0_b=0.3772; sig_par1_b=-0.04093; sig_par2_b=0.001456;
				sig_par0_c=0.3744; sig_par1_c=-0.03921; sig_par2_c=0.001372;
				sig_par0_l=0.3997; sig_par1_l=-0.0455; sig_par2_l=0.001697;									  
							  
			}
			else if(eta<0.879){
				par0_b=0.5461; par1_b=-0.05541; par2_b=-15.64; par3_b=0.001743;
				par0_c=0.2211; par1_c=-0.02248; par2_c=-7.153; par3_c=0.0008387;
				par0_l=0.2574; par1_l=-0.02853; par2_l=-5.957; par3_l=0.001155;

				sig_par0_b=0.3777; sig_par1_b=-0.04088; sig_par2_b=0.001461;
				sig_par0_c=0.3788; sig_par1_c=-0.03919; sig_par2_c=0.001335;
				sig_par0_l=0.4018; sig_par1_l=-0.04543; sig_par2_l=0.00169;
				
			}
			else if(eta<1.131){
				par0_b=0.374; par1_b=-0.03208; par2_b=-13.33; par3_b=0.0009114;
				par0_c=0.2817; par1_c=-0.02891; par2_c=-8.401; par3_c=0.001044;
				par0_l=0.2828; par1_l=-0.0302; par2_l=-6.436; par3_l=0.001168;

				sig_par0_b=0.3845; sig_par1_b=-0.04073; sig_par2_b=0.001425;
				sig_par0_c=0.4007; sig_par1_c=-0.04248; sig_par2_c=0.001474;
				sig_par0_l=0.4105; sig_par1_l=-0.04529; sig_par2_l=0.001634;
									 
							 
			}
			else if(eta<1.392){
				par0_b=0.3729; par1_b=-0.03199; par2_b=-13.61; par3_b=0.000936;
				par0_c=0.2824; par1_c=-0.02884; par2_c=-8.359; par3_c=0.00105;
				par0_l=0.391; par1_l=-0.04392; par2_l=-7.896; par3_l=0.001679;

				sig_par0_b=0.4114; sig_par1_b=-0.0436; sig_par2_b=0.001532;
				sig_par0_c=0.4129; sig_par1_c=-0.04212; sig_par2_c=0.001423;
				sig_par0_l=0.4252; sig_par1_l=-0.0449; sig_par2_l=0.001567;
			}
			else if(eta<1.74){
				par0_b=0.2458; par1_b=-0.01336; par2_b=-11.89; par3_b=0.0001863;
				par0_c=0.1969; par1_c=-0.01631; par2_c=-7.176; par3_c=0.0005493;
				par0_l=0.3914; par1_l=-0.04407; par2_l=-7.66; par3_l=0.00165;
				
				sig_par0_b=0.4159; sig_par1_b=-0.04367; sig_par2_b=0.001478;
				sig_par0_c=0.4667; sig_par1_c=-0.05268; sig_par2_c=0.001906;
				sig_par0_l=0.4671; sig_par1_l=-0.05274; sig_par2_l=0.001893;
									 
			}
			else{
				par0_b=0.4105; par1_b=-0.04068; par2_b=-11.76; par3_b=0.001256;
				par0_c=0.1713; par1_c=-0.01819; par2_c=-5.27; par3_c=0.0006939;
				par0_l=0.2761; par1_l=-0.03283; par2_l=-5.111; par3_l=0.001298;

				sig_par0_b=0.4514; sig_par1_b=-0.05365; sig_par2_b=0.001941;
				sig_par0_c=0.4701; sig_par1_c=-0.05768; sig_par2_c=0.002172;
				sig_par0_l=0.4725; sig_par1_l=-0.05803; sig_par2_l=0.002176;
			} 

			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt;
			tsjetCorr[0][i] = -1.0*(-1.0+meanb);

			Double_t sigma_b = sig_par0_b + sig_par1_b*sqrt(pt)+ sig_par2_b*pt;
			sigmajets[0][i] = (1-meanb)*pt*sigma_b;
	
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt;          
			tsjetCorr[1][i] = -1.0*(-1.0+meanc);

			Double_t sigma_c = sig_par0_c + sig_par1_c*sqrt(pt)+ sig_par2_c*pt;
			sigmajets[1][i] = (1-meanc)*pt*sigma_c;
			
			Double_t meanl =  par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt;   
			tsjetCorr[2][i] =  -1.0*(-1.0+meanl);

			Double_t sigma_l = sig_par0_l + sig_par1_l*sqrt(pt)+ sig_par2_l*pt;
			sigmajets[2][i] = (1-meanl)*pt*sigma_l;

			if (debug){
				cout << " = = for jets " << i << ": cor_b " << tsjetCorr[0][i] << "(" << sigmajets[0][i]
					 << ") , cor_c " << tsjetCorr[1][i] << "(" << sigmajets[1][i] << "), cor_l " << tsjetCorr[2][i]
					 << "(" << sigmajets[2][i] << ")" << endl;
			}


		}
		
		if (debug)
			cout << " tstype 5: Idiogram method called!!!! " << endl;				

		break;
		
		
	case 6:  // correction used at CDF experiments
		
		for (int i=0; i<4; i++){
			float jetPt = jets_f[i].Pt();
			float jetEta = fabs(jets_f[i].Eta());
			
			Double_t par0_b = 0.0140588 + -1.23734*TMath::Abs(jetEta) + 0.50893*jetEta*jetEta;
			Double_t par1_b = -0.0384425 + 0.026809*TMath::Abs(jetEta) + -0.0177366*jetEta*jetEta;
			Double_t par2_b = -0.00251252 + -0.0112548*TMath::Abs(jetEta) + 0.0168725*jetEta*jetEta;
			Double_t meanb = exp(par0_b+par1_b*jetPt) + par2_b;
			tsjetCorr[0][i]=1+meanb;
			Double_t par0_w = -0.513158 + -0.847359*TMath::Abs(jetEta) + 0.250814*jetEta*jetEta;
			Double_t par1_w = -0.0353034 + -0.0134198*TMath::Abs(jetEta) + 0.00499046*jetEta*jetEta;
			Double_t par2_w = -0.0276111 + 0.00524618*TMath::Abs(jetEta) + 0.0086811*jetEta*jetEta;
			Double_t meanw = exp(par0_w+par1_w*jetPt) + par2_w;
			tsjetCorr[2][i]=1+meanw;
			
			Double_t par0_b_sigma = -1.44143 + -0.0178878*TMath::Abs(jetEta) + 0.0801477*jetEta*jetEta;
			Double_t par1_b_sigma = -0.0155933 + -0.0112122*TMath::Abs(jetEta) + 0.00449874*jetEta*jetEta;
			Double_t par2_b_sigma = 0.101061 + 0.00676025*TMath::Abs(jetEta) + -0.0165298*jetEta*jetEta;
			Double_t meanb_sigma = exp(par0_b_sigma+par1_b_sigma*jetPt) + par2_b_sigma;
			sigmajets[0][i]=jetPt*(1+meanb)*meanb_sigma;
			Double_t par0_w_sigma = -1.36288 + -0.262984*TMath::Abs(jetEta) + 0.169646*jetEta*jetEta;
			Double_t par1_w_sigma = -0.0307105 + 0.000556003*TMath::Abs(jetEta) + -0.00285268*jetEta*jetEta;
			Double_t par2_w_sigma = 0.122143 + -0.0309707*TMath::Abs(jetEta) + 0.00881518*jetEta*jetEta;
			Double_t meanw_sigma = exp(par0_w_sigma+par1_w_sigma*jetPt) + par2_w_sigma;
			sigmajets[2][i]=jetPt*(1+meanw)*meanw_sigma;
		}

		if (debug)
			cout << " tstype 6: CDF  parton correction " << endl;
		
		break;		


	case 7:

		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());

			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0;
	
			if(eta<0.174){
				par0_b=0.5447; par1_b=-0.05512; par2_b=-15.72; par3_b=0.001745;
				par0_c=0.3833; par1_c=-0.0458; par2_c=-9.272; par3_c=0.00175;
				par0_l=0.2634; par1_l=-0.02955; par2_l=-6.17; par3_l=0.001194;				

				par0_sigb=0.359; par1_sigb=-0.03734; par2_sigb=0.001297;
				par0_sigc=0.3712; par1_sigc=-0.03865; par2_sigc=0.001361;
				par0_sigl=0.377; par1_sigl=-0.0406; par2_sigl=0.001456;
			}

			else if(eta<0.348){
				par0_b=0.5447; par1_b=-0.05513; par2_b=-15.73; par3_b=0.001744;
				par0_c=0.2171; par1_c=-0.0217; par2_c=-7.227; par3_c=0.0008051;
				par0_l=0.2636; par1_l=-0.02958; par2_l=-6.106; par3_l=0.001187;

				par0_sigb=0.3738; par1_sigb=-0.04054; par2_sigb=0.001454;
				par0_sigc=0.3936; par1_sigc=-0.04318; par2_sigc=0.001567;
				par0_sigl=0.3888; par1_sigl=-0.0437; par2_sigl=0.001625;		
			}			
			else if(eta<0.522){
				par0_b=0.5445; par1_b=-0.05521; par2_b=-15.66; par3_b=0.001731;
				par0_c=0.2166; par1_c=-0.0218; par2_c=-7.183; par3_c=0.0007932;
				par0_l=0.2635; par1_l=-0.02963; par2_l=-6.065; par3_l=0.001178;

				par0_sigb=0.3738; par1_sigb=-0.04054; par2_sigb=0.001454;
				par0_sigc=0.3711; par1_sigc=-0.03897; par2_sigc=0.001381;
				par0_sigl=0.3748; par1_sigl=-0.04039; par2_sigl=0.001452;
			}
			else if(eta<0.696){
				par0_b=0.5447; par1_b=-0.05521; par2_b=-15.63; par3_b=0.001731;
				par0_c=0.2169; par1_c=-0.02177; par2_c=-7.169; par3_c=0.0007962;
				par0_l=0.2638; par1_l=-0.02958; par2_l=-6.092; par3_l=0.001185;

				par0_sigb=0.3754; par1_sigb=-0.04054; par2_sigb=0.001436;
				par0_sigc=0.3735; par1_sigc=-0.03898; par2_sigc=0.00136;
				par0_sigl=0.3984; par1_sigl=-0.04527; par2_sigl=0.001687;
			}		
			else if(eta<0.879){
				par0_b=0.5448; par1_b=-0.0552; par2_b=-15.62; par3_b=0.001732;
				par0_c=0.2173; par1_c=-0.02172; par2_c=-7.143; par3_c=0.0008008;
				par0_l=0.2645; par1_l=-0.02951; par2_l=-6.053; par3_l=0.001191;

				par0_sigb=0.3759; par1_sigb=-0.04049; par2_sigb=0.001441;
				par0_sigc=0.3778; par1_sigc=-0.03896; par2_sigc=0.001323;
				par0_sigl=0.4007; par1_sigl=-0.0452; par2_sigl=0.001679;
			}
			else if(eta<1.131){
				par0_b=0.3719; par1_b=-0.03178; par2_b=-13.31; par3_b=0.0008998;
				par0_c=0.2917; par1_c=-0.03029; par2_c=-8.54; par3_c=0.001095;
				par0_l=0.2741; par1_l=-0.02899; par2_l=-6.325; par3_l=0.001125;	

				par0_sigb=0.3821; par1_sigb=-0.04035; par2_sigb=0.00141;
				par0_sigc=0.4013; par1_sigc=-0.0426; par2_sigc=0.001481;
				par0_sigl=0.4094; par1_sigl=-0.04506; par2_sigl=0.001623;
			}
			else if(eta<1.392){
				par0_b=0.3708; par1_b=-0.03169; par2_b=-13.59; par3_b=0.0009247;
				par0_c=0.2924; par1_c=-0.03023; par2_c=-8.477; par3_c=0.001099;
				par0_l=0.387; par1_l=-0.0433; par2_l=-7.858; par3_l=0.001654;

				par0_sigb=0.4114; par1_sigb=-0.04361; par2_sigb=0.001533;
				par0_sigc=0.4135; par1_sigc=-0.04225; par2_sigc=0.00143;
				par0_sigl=0.4242; par1_sigl=-0.04468; par2_sigl=0.001555;
			}
			else if(eta<1.74){
				par0_b=0.2521; par1_b=-0.01422; par2_b=-11.99; par3_b=0.0002192;
				par0_c=0.194; par1_c=-0.01584; par2_c=-7.154; par3_c=0.0005301;
				par0_l=0.3874; par1_l=-0.04344; par2_l=-7.629; par3_l=0.001625;

				par0_sigb=0.4159; par1_sigb=-0.04368; par2_sigb=0.001478;
				par0_sigc=0.4669; par1_sigc=-0.05272; par2_sigc=0.001908;
				par0_sigl=0.4649; par1_sigl=-0.05221; par2_sigl=0.001862;
			}
			else{
				par0_b=0.4297; par1_b=-0.04326; par2_b=-12.05; par3_b=0.001351;
				par0_c=0.1683; par1_c=-0.01771; par2_c=-5.259; par3_c=0.0006745;
				par0_l=0.2752; par1_l=-0.03268; par2_l=-5.106; par3_l=0.001292;						

				par0_sigb=0.4517; par1_sigb=-0.05371; par2_sigb=0.001943;
				par0_sigc=0.4708; par1_sigc=-0.05784; par2_sigc=0.00218;
				par0_sigl=0.4729; par1_sigl=-0.05812; par2_sigl=0.00218;
			}
    
			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt;
			tsjetCorr[0][i]=-1.*(meanb-1);
    
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt;       			
			tsjetCorr[1][i] = -1.*(-1.+meanc);

			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt;       			
			tsjetCorr[2][i] = -1.*(-1.+meanl);

			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb*pt;
			sigmajets[0][i] = (1-meanb)*pt*sigmab;

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc*pt;
			sigmajets[1][i] = (1-meanc)*pt*sigmac;			

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl*pt;
			sigmajets[2][i] = (1-meanl)*pt*sigmal;			

			if (debug)
				cout << " Pt = " << pt << ", eta " << eta << " =>b corr : " << tsjetCorr[0][i] << ", sigmab = " << sigmab << ", sigma*ptcorr = " << sigmajets[0][i] << endl;
		}

		if (debug){
			cout << " tstype 7: parton pt>20GeV, L7 correction" << endl;
			//			cout << " For jet pt =  " << jets_f[0].Pt() <<   endl;
			//cout << " For jet 0 bcorr err = " << sigmajets[0][0]/(tsjetCorr[0][0]*jets_f[0].Pt()) << " : jet err = " << sigmajets[0][0] << ", jet corr = " << tsjetCorr[0][0] <<  endl;
			//cout << " For jet 0 ccorr err = " << sigmajets[1][0]/(tsjetCorr[1][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[1][0]  << ", jet corr = " << tsjetCorr[1][0] <<  endl;
			//cout << " For jet 0 lcorr err = " << sigmajets[2][0]/(tsjetCorr[2][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[2][0] << ", jet corr = " << tsjetCorr[2][0]   << endl;
		}
		break;


	case 8: // all four jets matching to the partons

		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());

			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0;
	
			if(eta<0.174){
				par0_b=0.6549; par1_b=-0.07084; par2_b=-16.84; par3_b=0.00233;
				par0_c=0.2882; par1_c=-0.0292; par2_c=-7.596; par3_c=0.001057;
				par0_l=0.4932; par1_l=-0.06029; par2_l=-8.68; par3_l=0.002336;				

				par0_sigb=0.3597; par1_sigb=-0.03794; par2_sigb=0.001328;
				par0_sigc=0.3664; par1_sigc=-0.03877; par2_sigc=0.001369;
				par0_sigl=0.3572; par1_sigl=-0.03777; par2_sigl=0.001352;
			}

			else if(eta<0.348){
				par0_b=0.5846; par1_b=-0.06142; par2_b=-15.74; par3_b=0.001977;
				par0_c=0.2736; par1_c=-0.02994; par2_c=-7.027; par3_c=0.001186;
				par0_l=0.4933; par1_l=-0.06029; par2_l=-8.675; par3_l=0.002337;

				par0_sigb=0.3589; par1_sigb=-0.03803; par2_sigb=0.001321;
				par0_sigc=0.3581; par1_sigc=-0.03876; par2_sigc=0.001451;
				par0_sigl=0.391; par1_sigl=-0.04625; par2_sigl=0.001799;		
			}			
			else if(eta<0.522){
				par0_b=0.5845; par1_b=-0.06155; par2_b=-15.62; par3_b=0.001954;
				par0_c=0.2838; par1_c=-0.03025; par2_c=-7.298; par3_c=0.001127;
				par0_l=0.3983; par1_l=-0.04688; par2_l=-7.413; par3_l=0.001822;

				par0_sigb=0.3463; par1_sigb=-0.03539; par2_sigb=0.001199;
				par0_sigc=0.3605; par1_sigc=-0.03888; par2_sigc=0.001406;
				par0_sigl=0.3743; par1_sigl=-0.04151; par2_sigl=0.001526;
			}
			else if(eta<0.696){
				par0_b=0.5312; par1_b=-0.05521; par2_b=-14.67; par3_b=0.001767;
				par0_c=0.3286; par1_c=-0.03545; par2_c=-8.092; par3_c=0.001314;
				par0_l=0.3984; par1_l=-0.04687; par2_l=-7.408; par3_l=0.001823;

				par0_sigb=0.3497; par1_sigb=-0.03542; par2_sigb=0.001162;
				par0_sigc=0.3661; par1_sigc=-0.0388; par2_sigc=0.001367;
				par0_sigl=0.3946; par1_sigl=-0.04636; par2_sigl=0.001792;
			}		
			else if(eta<0.879){
				par0_b=0.6546; par1_b=-0.07119; par2_b=-16.59; par3_b=0.002337;
				par0_c=0.3288; par1_c=-0.03553; par2_c=-7.992; par3_c=0.001298;
				par0_l=0.3992; par1_l=-0.04675; par2_l=-7.393; par3_l=0.001836;

				par0_sigb=0.3737; par1_sigb=-0.04057; par2_sigb=0.001438;
				par0_sigc=0.3689; par1_sigc=-0.03872; par2_sigc=0.001349;
				par0_sigl=0.3803; par1_sigl=-0.04262; par2_sigl=0.001588;
			}
			else if(eta<1.131){
				par0_b=0.2863; par1_b=-0.01995; par2_b=-11.64; par3_b=0.0004187;
				par0_c=0.4506; par1_c=-0.05007; par2_c=-10.13; par3_c=0.00183;
				par0_l=0.4647; par1_l=-0.05452; par2_l=-8.231; par3_l=0.002094;	

				par0_sigb=0.3805; par1_sigb=-0.04041; par2_sigb=0.001404;
				par0_sigc=0.3729; par1_sigc=-0.03874; par2_sigc=0.001305;
				par0_sigl=0.3916; par1_sigl=-0.04247; par2_sigl=0.00151;
			}
			else if(eta<1.392){
				par0_b=0.2924; par1_b=-0.01919; par2_b=-12.29; par3_b=0.0003552;
				par0_c=0.2731; par1_c=-0.02216; par2_c=-7.969; par3_c=0.0006855;
				par0_l=0.5361; par1_l=-0.06263; par2_l=-9.2; par3_l=0.002402;

				par0_sigb=0.3919; par1_sigb=-0.04009; par2_sigb=0.001352;
				par0_sigc=0.3923; par1_sigc=-0.03842; par2_sigc=0.001179;
				par0_sigl=0.4314; par1_sigl=-0.04755; par2_sigl=0.001714;
			}
			else if(eta<1.74){
				par0_b=0.2932; par1_b=-0.01922; par2_b=-12.13; par3_b=0.0003447;
				par0_c=0.4303; par1_c=-0.0473; par2_c=-9.403; par3_c=0.001738;
				par0_l=0.5365; par1_l=-0.06292; par2_l=-8.824; par3_l=0.002348;

				par0_sigb=0.3966; par1_sigb=-0.04012; par2_sigb=0.001299;
				par0_sigc=0.4662; par1_sigc=-0.05392; par2_sigc=0.001983;
				par0_sigl=0.4671; par1_sigl=-0.05365; par2_sigl=0.001946;
			}
			else{
				par0_b=0.4618; par1_b=-0.04945; par2_b=-11.73; par3_b=0.001614;
				par0_c=0.5526; par1_c=-0.07559; par2_c=-8.576; par3_c=0.003072;
				par0_l=0.4191; par1_l=-0.05081; par2_l=-6.492; par3_l=0.001968;						

				par0_sigb=0.4362; par1_sigb=-0.05088; par2_sigb=0.001786;
				par0_sigc=0.4444; par1_sigc=-0.0545; par2_sigc=0.002089;
				par0_sigl=0.454; par1_sigl=-0.05428; par2_sigl=0.001956;
			}
    
			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt;
			tsjetCorr[0][i]=(1-meanb);
    
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt;       	    
			tsjetCorr[1][i] = (1.-meanc);

			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt;           	
			tsjetCorr[2][i] = (1.-meanl);

			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb*pt;
			sigmajets[0][i] = (1-meanb)*pt*sigmab;

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc*pt;
			sigmajets[1][i] = (1-meanc)*pt*sigmac;			

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl*pt;
			sigmajets[2][i] = (1-meanl)*pt*sigmal;			

			if (debug)
				cout << " Pt = " << pt << ", eta " << eta << " =>b corr : " << tsjetCorr[0][i] << ", sigmab = " << sigmab << ", sigma*ptcorr = " << sigmajets[0][i] << endl;
		}

		if (debug){
			cout << " tstype 8: parton pt>20GeV, L7 correction" << endl;
			//			cout << " For jet pt =  " << jets_f[0].Pt() <<   endl;
			//cout << " For jet 0 bcorr err = " << sigmajets[0][0]/(tsjetCorr[0][0]*jets_f[0].Pt()) << " : jet err = " << sigmajets[0][0] << ", jet corr = " << tsjetCorr[0][0] <<  endl;
			//cout << " For jet 0 ccorr err = " << sigmajets[1][0]/(tsjetCorr[1][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[1][0]  << ", jet corr = " << tsjetCorr[1][0] <<  endl;
			//cout << " For jet 0 lcorr err = " << sigmajets[2][0]/(tsjetCorr[2][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[2][0] << ", jet corr = " << tsjetCorr[2][0]   << endl;
		}

		break;

	case 9: // test corr2 profile

		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());

			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0;
	
			if(eta<0.174){
				par0_b=-0.2599; par1_b=0.02162; par2_b=13.63; par3_b=-0.0008631;
				par0_c=-0.2064; par1_c=0.01463; par2_c=8.419; par3_c=-0.0006308;
				par0_l=-0.2941; par1_l=0.02752; par2_l=8.058; par3_l=-0.001301;


				par0_sigb=0.3597; par1_sigb=-0.03794; par2_sigb=0.001328;
				par0_sigc=0.3664; par1_sigc=-0.03877; par2_sigc=0.001369;
				par0_sigl=0.3572; par1_sigl=-0.03777; par2_sigl=0.001352;
			}

			else if(eta<0.348){
				par0_b=-0.3028; par1_b=0.0276; par2_b=14.2; par3_b=-0.001092;
				par0_c=-0.2942; par1_c=0.029; par2_c=9.452; par3_c=-0.001291;
				par0_l=-0.2204; par1_l=0.01694; par2_l=7.079; par3_l=-0.0008767;


				par0_sigb=0.3589; par1_sigb=-0.03803; par2_sigb=0.001321;
				par0_sigc=0.3581; par1_sigc=-0.03876; par2_sigc=0.001451;
				par0_sigl=0.391; par1_sigl=-0.04625; par2_sigl=0.001799;		
			}			
			else if(eta<0.522){
				par0_b=-0.3238; par1_b=0.03114; par2_b=14.34; par3_b=-0.001233;
				par0_c=-0.1271; par1_c=0.003747; par2_c=7.518; par3_c=-0.0002342;
				par0_l=-0.2334; par1_l=0.0197; par2_l=7.059; par3_l=-0.001013;

				par0_sigb=0.3463; par1_sigb=-0.03539; par2_sigb=0.001199;
				par0_sigc=0.3605; par1_sigc=-0.03888; par2_sigc=0.001406;
				par0_sigl=0.3743; par1_sigl=-0.04151; par2_sigl=0.001526;
			}
			else if(eta<0.696){
				par0_b=-0.2603; par1_b=0.02333; par2_b=13.18; par3_b=-0.0009777;
				par0_c=-0.2408; par1_c=0.02216; par2_c=8.639; par3_c=-0.001061;
				par0_l=-0.2942; par1_l=0.02809; par2_l=7.877; par3_l=-0.001332;

				par0_sigb=0.3497; par1_sigb=-0.03542; par2_sigb=0.001162;
				par0_sigc=0.3661; par1_sigc=-0.0388; par2_sigc=0.001367;
				par0_sigl=0.3946; par1_sigl=-0.04636; par2_sigl=0.001792;
			}		
			else if(eta<0.879){
				par0_b=-0.2779; par1_b=0.02531; par2_b=13.52; par3_b=-0.001028;
				par0_c=-0.1044; par1_c=0.001598; par2_c=7.07; par3_c=-0.0002145;
				par0_l=-0.2929; par1_l=0.02805; par2_l=7.755; par3_l=-0.001341;

				par0_sigb=0.3737; par1_sigb=-0.04057; par2_sigb=0.001438;
				par0_sigc=0.3689; par1_sigc=-0.03872; par2_sigc=0.001349;
				par0_sigl=0.3803; par1_sigl=-0.04262; par2_sigl=0.001588;
			}
			else if(eta<1.131){
				par0_b=-0.1693; par1_b=0.01185; par2_b=11.8; par3_b=-0.0006093;
				par0_c=-0.1399; par1_c=0.00624; par2_c=7.749; par3_c=-0.0004579;
				par0_l=-0.3267; par1_l=0.03242; par2_l=8.279; par3_l=-0.00153;

				par0_sigb=0.3805; par1_sigb=-0.04041; par2_sigb=0.001404;
				par0_sigc=0.3729; par1_sigc=-0.03874; par2_sigc=0.001305;
				par0_sigl=0.3916; par1_sigl=-0.04247; par2_sigl=0.00151;
			}
			else if(eta<1.392){
				par0_b=-0.1815; par1_b=0.01379; par2_b=12.12; par3_b=-0.0007118;
				par0_c=-0.1665; par1_c=0.01108; par2_c=7.78; par3_c=-0.0006983;
				par0_l=-0.3336; par1_l=0.03235; par2_l=8.347; par3_l=-0.00154;


				par0_sigb=0.3919; par1_sigb=-0.04009; par2_sigb=0.001352;
				par0_sigc=0.3923; par1_sigc=-0.03842; par2_sigc=0.001179;
				par0_sigl=0.4314; par1_sigl=-0.04755; par2_sigl=0.001714;
			}
			else if(eta<1.74){
				par0_b=-0.1383; par1_b=0.007426; par2_b=11.36; par3_b=-0.00047;
				par0_c=-0.1156; par1_c=0.001654; par2_c=6.99; par3_c=-0.0001997;
				par0_l=-0.3281; par1_l=0.03189; par2_l=7.848; par3_l=-0.001529;

				par0_sigb=0.3966; par1_sigb=-0.04012; par2_sigb=0.001299;
				par0_sigc=0.4662; par1_sigc=-0.05392; par2_sigc=0.001983;
				par0_sigl=0.4671; par1_sigl=-0.05365; par2_sigl=0.001946;
			}
			else{
				par0_b=-0.3173; par1_b=0.03976; par2_b=11.22; par3_b=-0.001994;
				par0_c=0.06553; par1_c=-0.02538; par2_c=4.057; par3_c=0.0009399;
				par0_l=-0.1456; par1_l=0.009954; par2_l=4.504; par3_l=-0.0008699;

				par0_sigb=0.4362; par1_sigb=-0.05088; par2_sigb=0.001786;
				par0_sigc=0.4444; par1_sigc=-0.0545; par2_sigc=0.002089;
				par0_sigl=0.454; par1_sigl=-0.05428; par2_sigl=0.001956;
			}
    
			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt;
			tsjetCorr[0][i]=(1-meanb);
    
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt;       	    
			tsjetCorr[1][i] = (1.-meanc);

			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt;           	
			tsjetCorr[2][i] = (1.-meanl);

			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb*pt;
			sigmajets[0][i] = (1-meanb)*pt*sigmab;

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc*pt;
			sigmajets[1][i] = (1-meanc)*pt*sigmac;			

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl*pt;
			sigmajets[2][i] = (1-meanl)*pt*sigmal;			

			if (debug)
				cout << " Pt = " << pt << ", eta " << eta << " =>b corr : " << tsjetCorr[0][i] << ", sigmab = " << sigmab << ", sigma*ptcorr = " << sigmajets[0][i] << endl;
		}

		if (debug){
			cout << " tstype 9: YJ's corr2, profile fit" << endl;
			//			cout << " For jet pt =  " << jets_f[0].Pt() <<   endl;
			//cout << " For jet 0 bcorr err = " << sigmajets[0][0]/(tsjetCorr[0][0]*jets_f[0].Pt()) << " : jet err = " << sigmajets[0][0] << ", jet corr = " << tsjetCorr[0][0] <<  endl;
			//cout << " For jet 0 ccorr err = " << sigmajets[1][0]/(tsjetCorr[1][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[1][0]  << ", jet corr = " << tsjetCorr[1][0] <<  endl;
			//cout << " For jet 0 lcorr err = " << sigmajets[2][0]/(tsjetCorr[2][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[2][0] << ", jet corr = " << tsjetCorr[2][0]   << endl;
		}

		break;

	case 10: // test corr5 profile, corrections only

		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());

			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0;
	
			if(eta<0.174){
				par0_b=-0.546; par1_b=0.04965; par2_b=17.75; par3_b=-0.001318;
				par0_c=-0.3883; par1_c=0.03633; par2_c=10.55; par3_c=-0.00102;
				par0_l=-0.4215; par1_l=0.04184; par2_l=9.329; par3_l=-0.001265;



				par0_sigb=0.3597; par1_sigb=-0.03794; par2_sigb=0.001328;
				par0_sigc=0.3664; par1_sigc=-0.03877; par2_sigc=0.001369;
				par0_sigl=0.3572; par1_sigl=-0.03777; par2_sigl=0.001352;
			}

			else if(eta<0.348){
				par0_b=-0.5632; par1_b=0.05161; par2_b=18.08; par3_b=-0.001374;
				par0_c=-0.4317; par1_c=0.04316; par2_c=11.14; par3_c=-0.001323;
				par0_l=-0.4156; par1_l=0.04133; par2_l=9.154; par3_l=-0.001255;



				par0_sigb=0.3589; par1_sigb=-0.03803; par2_sigb=0.001321;
				par0_sigc=0.3581; par1_sigc=-0.03876; par2_sigc=0.001451;
				par0_sigl=0.391; par1_sigl=-0.04625; par2_sigl=0.001799;		
			}			
			else if(eta<0.522){
				par0_b=-0.5849; par1_b=0.05527; par2_b=18.19; par3_b=-0.001518;
				par0_c=-0.3955; par1_c=0.03833; par2_c=10.62; par3_c=-0.00112;
				par0_l=-0.3992; par1_l=0.03967; par2_l=8.807; par3_l=-0.001205;


				par0_sigb=0.3463; par1_sigb=-0.03539; par2_sigb=0.001199;
				par0_sigc=0.3605; par1_sigc=-0.03888; par2_sigc=0.001406;
				par0_sigl=0.3743; par1_sigl=-0.04151; par2_sigl=0.001526;
			}
			else if(eta<0.696){
				par0_b=-0.5357; par1_b=0.04935; par2_b=17.25; par3_b=-0.001327;
				par0_c=-0.3588; par1_c=0.03333; par2_c=10.08; par3_c=-0.0009552;
				par0_l=-0.4078; par1_l=0.0407; par2_l=8.961; par3_l=-0.001246;


				par0_sigb=0.3497; par1_sigb=-0.03542; par2_sigb=0.001162;
				par0_sigc=0.3661; par1_sigc=-0.0388; par2_sigc=0.001367;
				par0_sigl=0.3946; par1_sigl=-0.04636; par2_sigl=0.001792;
			}		
			else if(eta<0.879){
				par0_b=-0.5572; par1_b=0.05206; par2_b=17.66; par3_b=-0.001424;
				par0_c=-0.4297; par1_c=0.04378; par2_c=10.93; par3_c=-0.001363;
				par0_l=-0.386; par1_l=0.03748; par2_l=8.637; par3_l=-0.00113;


				par0_sigb=0.3737; par1_sigb=-0.04057; par2_sigb=0.001438;
				par0_sigc=0.3689; par1_sigc=-0.03872; par2_sigc=0.001349;
				par0_sigl=0.3803; par1_sigl=-0.04262; par2_sigl=0.001588;
			}
			else if(eta<1.131){
				par0_b=-0.4866; par1_b=0.04304; par2_b=16.49; par3_b=-0.001118;
				par0_c=-0.5257; par1_c=0.05604; par2_c=12.41; par3_c=-0.00182;
				par0_l=-0.44; par1_l=0.04378; par2_l=9.454; par3_l=-0.001325;


				par0_sigb=0.3805; par1_sigb=-0.04041; par2_sigb=0.001404;
				par0_sigc=0.3729; par1_sigc=-0.03874; par2_sigc=0.001305;
				par0_sigl=0.3916; par1_sigl=-0.04247; par2_sigl=0.00151;
			}
			else if(eta<1.392){
				par0_b=-0.4822; par1_b=0.04177; par2_b=16.62; par3_b=-0.001056;
				par0_c=-0.6269; par1_c=0.07052; par2_c=13.48; par3_c=-0.002389;
				par0_l=-0.5517; par1_l=0.05815; par2_l=10.88; par3_l=-0.001848;



				par0_sigb=0.3919; par1_sigb=-0.04009; par2_sigb=0.001352;
				par0_sigc=0.3923; par1_sigc=-0.03842; par2_sigc=0.001179;
				par0_sigl=0.4314; par1_sigl=-0.04755; par2_sigl=0.001714;
			}
			else if(eta<1.74){
				par0_b=-0.4483; par1_b=0.03692; par2_b=15.97; par3_b=-0.0008628;
				par0_c=-0.4338; par1_c=0.04117; par2_c=10.96; par3_c=-0.001168;
				par0_l=-0.6009; par1_l=0.0656; par2_l=11.03; par3_l=-0.002123;


				par0_sigb=0.3966; par1_sigb=-0.04012; par2_sigb=0.001299;
				par0_sigc=0.4662; par1_sigc=-0.05392; par2_sigc=0.001983;
				par0_sigl=0.4671; par1_sigl=-0.05365; par2_sigl=0.001946;
			}
			else{
				par0_b=-0.449; par1_b=0.04125; par2_b=13.96; par3_b=-0.001097;
				par0_c=-0.5826; par1_c=0.06961; par2_c=11.08; par3_c=-0.002437;
				par0_l=-0.6214; par1_l=0.07515; par2_l=9.8; par3_l=-0.002667;

				par0_sigb=0.4362; par1_sigb=-0.05088; par2_sigb=0.001786;
				par0_sigc=0.4444; par1_sigc=-0.0545; par2_sigc=0.002089;
				par0_sigl=0.454; par1_sigl=-0.05428; par2_sigl=0.001956;
			}
    
			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt;
			tsjetCorr[0][i]=(1-meanb);
    
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt;       	    
			tsjetCorr[1][i] = (1.-meanc);

			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt;           	
			tsjetCorr[2][i] = (1.-meanl);

			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb*pt;
			sigmajets[0][i] = (1-meanb)*pt*sigmab;

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc*pt;
			sigmajets[1][i] = (1-meanc)*pt*sigmac;			

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl*pt;
			sigmajets[2][i] = (1-meanl)*pt*sigmal;			

			if (debug)
				cout << " Pt = " << pt << ", eta " << eta << " =>b corr : " << tsjetCorr[0][i] << ", sigmab = " << sigmab << ", sigma*ptcorr = " << sigmajets[0][i] << endl;
		}

		if (debug){
			cout << " tstype 9: YJ's corr2, profile fit" << endl;
			//			cout << " For jet pt =  " << jets_f[0].Pt() <<   endl;
			//cout << " For jet 0 bcorr err = " << sigmajets[0][0]/(tsjetCorr[0][0]*jets_f[0].Pt()) << " : jet err = " << sigmajets[0][0] << ", jet corr = " << tsjetCorr[0][0] <<  endl;
			//cout << " For jet 0 ccorr err = " << sigmajets[1][0]/(tsjetCorr[1][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[1][0]  << ", jet corr = " << tsjetCorr[1][0] <<  endl;
			//cout << " For jet 0 lcorr err = " << sigmajets[2][0]/(tsjetCorr[2][0]*jets_f[0].Pt()) << " jet err = " << sigmajets[2][0] << ", jet corr = " << tsjetCorr[2][0]   << endl;
		}
    
		break;

	case 11: // 022 type. Crystal ball fit for having b-jet correction && profile fit for c-jet/l-jet correction
    
		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());
	      
			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0, par3_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0, par3_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0, par3_sigl=0;
	      
			if(eta<0.174){
				par0_b=0.3241; par1_b=-0.02988; par2_b=-11.13; par3_b=0.0009809;
				par0_c=-0.2064; par1_c=0.01463; par2_c=8.419; par3_c=-0.0006308;
				par0_l=-0.2941; par1_l=0.02752; par2_l=8.058; par3_l=-0.001301;

				par0_sigb=-0.3562; par1_sigb=0.05372; par2_sigb=14.82; par3_sigb=-0.001947;
				par0_sigc=0.3749; par1_sigc=-0.03753; par2_sigc=-0.6679; par3_sigc=0.001264;
				par0_sigl=0.2395; par1_sigl=-0.01987; par2_sigl=1.145; par3_sigl=0.0006714;
			}
			else if(eta<0.348){
				par0_b=0.3963; par1_b=-0.04002; par2_b=-12.1; par3_b=0.001364;
				par0_c=-0.2942; par1_c=0.029; par2_c=9.452; par3_c=-0.001291;
				par0_l=-0.2204; par1_l=0.01694; par2_l=7.079; par3_l=-0.0008767;

				par0_sigb=-0.5593; par1_sigb=0.0814; par2_sigb=17.79; par3_sigb=-0.002954;
				par0_sigc=0.3659; par1_sigc=-0.03858; par2_sigc=-0.4095; par3_sigc=0.001417;
				par0_sigl=0.3675; par1_sigl=-0.0419; par2_sigl=0.01179; par3_sigl=0.001646;
			}
			else if(eta<0.522){
				par0_b=0.3958; par1_b=-0.04007; par2_b=-12.13; par3_b=0.001358;
				par0_c=-0.1271; par1_c=0.003747; par2_c=7.518; par3_c=-0.0002342;
				par0_l=-0.2334; par1_l=0.0197; par2_l=7.059; par3_l=-0.001013;

				par0_sigb=-0.4647; par1_sigb=0.06791; par2_sigb=16.23; par3_sigb=-0.002433;
				par0_sigc=0.1331; par1_sigc=-0.005143; par2_sigc=2.486; par3_sigc=0.0001123;
				par0_sigl=0.5433; par1_sigl=-0.06482; par2_sigl=-2.431; par3_sigl=0.00245;
			}
			else if(eta<0.696){
				par0_b=0.3034; par1_b=-0.0278; par2_b=-10.64; par3_b=0.0009127;
				par0_c=-0.2408; par1_c=0.02216; par2_c=8.639; par3_c=-0.001061;
				par0_l=-0.2942; par1_l=0.02809; par2_l=7.877; par3_l=-0.001332;

				par0_sigb=-0.02226; par1_sigb=0.008973; par2_sigb=9.73; par3_sigb=-0.0003142;
				par0_sigc=0.4149; par1_sigc=-0.04391; par2_sigc=-1.123; par3_sigc=0.001551;
				par0_sigl=0.2698; par1_sigl=-0.02718; par2_sigl=1.268; par3_sigl=0.001056;
			}
			else if(eta<0.879){
				par0_b=0.3719; par1_b=-0.03698; par2_b=-11.64; par3_b=0.001248;
				par0_c=-0.1044; par1_c=0.001598; par2_c=7.07; par3_c=-0.0002145;
				par0_l=-0.2929; par1_l=0.02805; par2_l=7.755; par3_l=-0.001341;

				par0_sigb=-0.3996; par1_sigb=0.05815; par2_sigb=15.81; par3_sigb=-0.002067;
				par0_sigc=0.4151; par1_sigc=-0.04396; par2_sigc=-1.021; par3_sigc=0.00154;
				par0_sigl=0.1643; par1_sigl=-0.01048; par2_sigl=2.465; par3_sigl=0.0003478;
			}
			else if(eta<1.131){
				par0_b=0.3053; par1_b=-0.02803; par2_b=-10.78; par3_b=0.0009414;
				par0_c=-0.1399; par1_c=0.00624; par2_c=7.749; par3_c=-0.0004579;
				par0_l=-0.3267; par1_l=0.03242; par2_l=8.279; par3_l=-0.00153;

				par0_sigb=0.004968; par1_sigb=0.004328; par2_sigb=10.09; par3_sigb=-0.00008404;
				par0_sigc=0.1208; par1_sigc=-0.003847; par2_sigc=3.245; par3_sigc=0.00004158;
				par0_sigl=0.3082; par1_sigl=-0.03091; par2_sigl=0.9317; par3_sigl=0.001138;
			}
			else if(eta<1.392){
				par0_b=0.3039; par1_b=-0.02792; par2_b=-11.11; par3_b=0.0009715;
				par0_c=-0.1665; par1_c=0.01108; par2_c=7.78; par3_c=-0.0006983;
				par0_l=-0.3336; par1_l=0.03235; par2_l=8.347; par3_l=-0.00154;

				par0_sigb=0.1545; par1_sigb=-0.01655; par2_sigb=8.588; par3_sigb=0.0007291;
				par0_sigc=0.2802; par1_sigc=-0.02091; par2_sigc=0.9066; par3_sigc=0.000511;
				par0_sigl=0.2612; par1_sigl=-0.02254; par2_sigl=1.822; par3_sigl=0.0007766;
			}
			else if(eta<1.74){
				par0_b=0.2638; par1_b=-0.02067; par2_b=-10.81; par3_b=0.0006382;
				par0_c=-0.1156; par1_c=0.001654; par2_c=6.99; par3_c=-0.0001997;
				par0_l=-0.3281; par1_l=0.03189; par2_l=7.848; par3_l=-0.001529;

				par0_sigb=-0.1427; par1_sigb=0.02675; par2_sigb=12.29; par3_sigb=-0.001013;
				par0_sigc=0.2617; par1_sigc=-0.02193; par2_sigc=2.058; par3_sigc=0.0006649;
				par0_sigl=0.4832; par1_sigl=-0.05413; par2_sigl=-0.7617; par3_sigl=0.001968;
			}
			else{
				par0_b=0.2527; par1_b=-0.02188; par2_b=-8.768; par3_b=0.0006768;
				par0_c=0.06553; par1_c=-0.02538; par2_c=4.057; par3_c=0.0009399;
				par0_l=-0.1456; par1_l=0.009954; par2_l=4.504; par3_l=-0.0008699;

				par0_sigb=-0.1814; par1_sigb=0.02446; par2_sigb=13.84; par3_sigb=-0.0007675;
				par0_sigc=0.3632; par1_sigc=-0.03843; par2_sigc=0.321; par3_sigc=0.001299;
				par0_sigl=0.3567; par1_sigl=-0.03996; par2_sigl=0.9658; par3_sigl=0.001485;

			}   

			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt; 
			tsjetCorr[0][i]=(1-meanb);

			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt; 
			tsjetCorr[1][i]=(1+meanc);

			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt; 
			tsjetCorr[2][i]=(1+meanl);

	      
			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb/pt+par3_sigb*pt; 
			sigmajets[0][i] = (1-meanb)*pt*sigmab;		

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc/pt+par3_sigc*pt; 
			sigmajets[1][i] = (1+meanc)*pt*sigmac;		

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl/pt+par3_sigl*pt; 
			sigmajets[2][i] = (1+meanl)*pt*sigmal;		

		}
	

		break;

	case 12: // 422 type. Use |dpt|<25 GeV cut for b-jet correction && profile fit for c-jet/l-jet correction
	  
		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());
	    
			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0, par3_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0, par3_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0, par3_sigl=0;
	    
			if(eta<0.174){
				par0_b=-0.5476; par1_b=0.05133; par2_b=16.75; par3_b=-0.001388;
				par0_c=-0.2064; par1_c=0.01463; par2_c=8.419; par3_c=-0.0006308;
				par0_l=-0.2941; par1_l=0.02752; par2_l=8.058; par3_l=-0.001301;

				par0_sigb=0.225; par1_sigb=-0.02574; par2_sigb=6.567; par3_sigb=0.001011;
				par0_sigc=0.3749; par1_sigc=-0.03753; par2_sigc=-0.6679; par3_sigc=0.001264;
				par0_sigl=0.2395; par1_sigl=-0.01987; par2_sigl=1.145; par3_sigl=0.0006714;
			}
			else if(eta<0.348){
				par0_b=-0.5568; par1_b=0.05233; par2_b=16.94; par3_b=-0.001412;
				par0_c=-0.2942; par1_c=0.029; par2_c=9.452; par3_c=-0.001291;
				par0_l=-0.2204; par1_l=0.01694; par2_l=7.079; par3_l=-0.0008767;

				par0_sigb=-0.3773; par1_sigb=0.05323; par2_sigb=16.01; par3_sigb=-0.001803;
				par0_sigc=0.3659; par1_sigc=-0.03858; par2_sigc=-0.4095; par3_sigc=0.001417;
				par0_sigl=0.3675; par1_sigl=-0.0419; par2_sigl=0.01179; par3_sigl=0.001646;

			}
			else if(eta<0.522){
				par0_b=-0.5877; par1_b=0.05722; par2_b=17.2; par3_b=-0.001603;
				par0_c=-0.1271; par1_c=0.003747; par2_c=7.518; par3_c=-0.0002342;
				par0_l=-0.2334; par1_l=0.0197; par2_l=7.059; par3_l=-0.001013;

				par0_sigb=-0.4108; par1_sigb=0.05883; par2_sigb=15.88; par3_sigb=-0.002036;
				par0_sigc=0.1331; par1_sigc=-0.005143; par2_sigc=2.486; par3_sigc=0.0001123;
				par0_sigl=0.5433; par1_sigl=-0.06482; par2_sigl=-2.431; par3_sigl=0.00245;
			}
			else if(eta<0.696){
				par0_b=-0.5381; par1_b=0.05119; par2_b=16.27; par3_b=-0.001407;
				par0_c=-0.2408; par1_c=0.02216; par2_c=8.639; par3_c=-0.001061;
				par0_l=-0.2942; par1_l=0.02809; par2_l=7.877; par3_l=-0.001332;

				par0_sigb=-0.3952; par1_sigb=0.05951; par2_sigb=15.41; par3_sigb=-0.002196;
				par0_sigc=0.4149; par1_sigc=-0.04391; par2_sigc=-1.123; par3_sigc=0.001551;
				par0_sigl=0.2698; par1_sigl=-0.02718; par2_sigl=1.268; par3_sigl=0.001056;

			}
			else if(eta<0.879){
				par0_b=-0.5431; par1_b=0.05148; par2_b=16.45; par3_b=-0.001407;
				par0_c=-0.1044; par1_c=0.001598; par2_c=7.07; par3_c=-0.0002145;
				par0_l=-0.2929; par1_l=0.02805; par2_l=7.755; par3_l=-0.001341;

				par0_sigb=-0.5272; par1_sigb=0.0767; par2_sigb=17.25; par3_sigb=-0.002771;
				par0_sigc=0.4151; par1_sigc=-0.04396; par2_sigc=-1.021; par3_sigc=0.00154;
				par0_sigl=0.1643; par1_sigl=-0.01048; par2_sigl=2.465; par3_sigl=0.0003478;
			}

			else if(eta<1.131){
				par0_b=-0.4821; par1_b=0.04372; par2_b=15.43; par3_b=-0.001146;
				par0_c=-0.1399; par1_c=0.00624; par2_c=7.749; par3_c=-0.0004579;
				par0_l=-0.3267; par1_l=0.03242; par2_l=8.279; par3_l=-0.00153;

				par0_sigb=0.01363; par1_sigb=0.002518; par2_sigb=10.01; par3_sigb=0.000002041;
				par0_sigc=0.1208; par1_sigc=-0.003847; par2_sigc=3.245; par3_sigc=0.00004158;
				par0_sigl=0.3082; par1_sigl=-0.03091; par2_sigl=0.9317; par3_sigl=0.001138;

			}
			else if(eta<1.392){
				par0_b=-0.493; par1_b=0.045; par2_b=15.65; par3_b=-0.001193;
				par0_c=-0.1665; par1_c=0.01108; par2_c=7.78; par3_c=-0.0006983;
				par0_c=-0.1665; par1_c=0.01108; par2_c=7.78; par3_c=-0.0006983;
				par0_l=-0.3336; par1_l=0.03235; par2_l=8.347; par3_l=-0.00154;

				par0_sigb=-0.09308; par1_sigb=0.01788; par2_sigb=12.15; par3_sigb=-0.0005895;
				par0_sigc=0.2802; par1_sigc=-0.02091; par2_sigc=0.9066; par3_sigc=0.000511;
				par0_sigl=0.2612; par1_sigl=-0.02254; par2_sigl=1.822; par3_sigl=0.0007766;
			}
			else if(eta<1.74){
				par0_b=-0.4569; par1_b=0.03966; par2_b=15.04; par3_b=-0.0009733;
				par0_c=-0.1156; par1_c=0.001654; par2_c=6.99; par3_c=-0.0001997;
				par0_l=-0.3281; par1_l=0.03189; par2_l=7.848; par3_l=-0.001529;

				par0_sigb=-0.2528; par1_sigb=0.04188; par2_sigb=14.12; par3_sigb=-0.001599;
				par0_sigc=0.2617; par1_sigc=-0.02193; par2_sigc=2.058; par3_sigc=0.0006649;
				par0_sigl=0.4832; par1_sigl=-0.05413; par2_sigl=-0.7617; par3_sigl=0.001968;

			}
			else{
				par0_b=-0.4481; par1_b=0.04262; par2_b=13.06; par3_b=-0.001162;
				par0_c=0.06553; par1_c=-0.02538; par2_c=4.057; par3_c=0.0009399;
				par0_l=-0.1456; par1_l=0.009954; par2_l=4.504; par3_l=-0.0008699;

				par0_sigb=-0.3068; par1_sigb=0.03895; par2_sigb=16.08; par3_sigb=-0.001206;
				par0_sigc=0.3632; par1_sigc=-0.03843; par2_sigc=0.321; par3_sigc=0.001299;
				par0_sigl=0.3567; par1_sigl=-0.03996; par2_sigl=0.9658; par3_sigl=0.001485;
			}  
	    

			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt; 

			tsjetCorr[0][i]=(1+meanb);

			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt; 
			tsjetCorr[1][i]=(1+meanc);

			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt; 
			tsjetCorr[2][i]=(1+meanl);

	      
			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb/pt+par3_sigb*pt; 
			sigmajets[0][i] = (1+meanb)*pt*sigmab;		

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc/pt+par3_sigc*pt; 
			sigmajets[1][i] = (1+meanc)*pt*sigmac;		

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl/pt+par3_sigl*pt; 
			sigmajets[2][i] = (1+meanl)*pt*sigmal;

			if (debug){
				cout << " ======= For case 12: 422 type =========== " << endl;
				cout << " For jet pt = " << pt << endl; 
				cout << " b-jet corr = " << 1-meanb << " , sigma = " << sigmab << " , corr sigma = " << (1-meanb)*pt*sigmab << endl;
				cout << " c-jet corr = " << 1-meanc << " , sigma = " << sigmac << " , corr sigma = " << (1-meanc)*pt*sigmac << endl;
				cout << " b-jet corr = " << 1-meanl << " , sigma = " << sigmal << " , corr sigma = " << (1-meanl)*pt*sigmal << endl;

			}
	    
		}

		break;

	case 13:// correction with top pt reweight: 022 type

		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());
	      
			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0, par3_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0, par3_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0, par3_sigl=0;
	      
			if(eta<0.174){
				par0_b=0.4519; par1_b=-0.04548; par2_b=-13; par3_b=0.001471;
				par0_c=-0.1995; par1_c=0.01237; par2_c=8.528; par3_c=-0.0005324;
				par0_l=-0.2979; par1_l=0.02754; par2_l=8.201; par3_l=-0.001326;

				par0_sigb=0.1326; par1_sigb=-0.01317; par2_sigb=7.885; par3_sigb=0.0005316;
				par0_sigc=0.4101; par1_sigc=-0.04369; par2_sigc=-0.987; par3_sigc=0.001559;
				par0_sigl=0.2374; par1_sigl=-0.0199; par2_sigl=1.208; par3_sigl=0.0006941;
			}
			else if(eta<0.348){
				par0_b=0.4521; par1_b=-0.04553; par2_b=-12.92; par3_b=0.001461;
				par0_c=-0.2866; par1_c=0.02688; par2_c=9.53; par3_c=-0.001208;
				par0_l=-0.2291; par1_l=0.01767; par2_l=7.283; par3_l=-0.0009294;
		  
				par0_sigb=-0.2257; par1_sigb=0.03464; par2_sigb=13.12; par3_sigb=-0.001173;
				par0_sigc=0.3315; par1_sigc=-0.03358; par2_sigc=-0.01424; par3_sigc=0.001234;
				par0_sigl=0.3143; par1_sigl=-0.03392; par2_sigl=0.6005; par3_sigl=0.001332;
			}
			else if(eta<0.522){
				par0_b=0.3747; par1_b=-0.03508; par2_b=-11.76; par3_b=0.001059;
				par0_c=-0.1168; par1_c=0.001053; par2_c=7.585; par3_c=-0.0001227;
				par0_l=-0.2434; par1_l=0.02058; par2_l=7.29; par3_l=-0.00107;
		  
				par0_sigb=-0.2273; par1_sigb=0.03464; par2_sigb=12.84; par3_sigb=-0.00116;
				par0_sigc=0.1435; par1_sigc=-0.007334; par2_sigc=2.413; par3_sigc=0.0002287;
				par0_sigl=0.4923; par1_sigl=-0.05751; par2_sigl=-1.827; par3_sigl=0.002178;
			}
			else if(eta<0.696){
				par0_b=0.393; par1_b=-0.03948; par2_b=-11.65; par3_b=0.001299;
				par0_c=-0.2361; par1_c=0.02047; par2_c=8.749; par3_c=-0.0009981;
				par0_l=-0.293; par1_l=0.0274; par2_l=7.966; par3_l=-0.001331;
		  
				par0_sigb=0.1751; par1_sigb=-0.01442; par2_sigb=5.989; par3_sigb=0.0004364;
				par0_sigc=0.5479; par1_sigc=-0.06382; par2_sigc=-2.705; par3_sigc=0.002356;
				par0_sigl=0.2242; par1_sigl=-0.01989; par2_sigl=1.711; par3_sigl=0.000754;
			}
			else if(eta<0.879){
				par0_b=0.5798; par1_b=-0.06449; par2_b=-14.35; par3_b=0.002197;
				par0_c=-0.09953; par1_c=-0.0002103; par2_c=7.183; par3_c=-0.0001419;
				par0_l=-0.2977; par1_l=0.02823; par2_l=7.915; par3_l=-0.001372;
		  
				par0_sigb=-0.5749; par1_sigb=0.08178; par2_sigb=18.15; par3_sigb=-0.002911;
				par0_sigc=0.372; par1_sigc=-0.03663; par2_sigc=-0.6704; par3_sigc=0.001218;
				par0_sigl=0.1221; par1_sigl=-0.004342; par2_sigl=2.967; par3_sigl=0.0001104;
			}
			else if(eta<1.131){
				par0_b=0.3055; par1_b=-0.02548; par2_b=-10.85; par3_b=0.0007256;
				par0_c=-0.1355; par1_c=0.004565; par2_c=7.865; par3_c=-0.0003958;
				par0_l=-0.3262; par1_l=0.03197; par2_l=8.365; par3_l=-0.001546;
		  
				par0_sigb=-0.05772; par1_sigb=0.01128; par2_sigb=11.2; par3_sigb=-0.0002926;
				par0_sigc=0.1049; par1_sigc=-0.000284; par2_sigc=3.248; par3_sigc=-0.0001325;
				par0_sigl=0.2977; par1_sigl=-0.02945; par2_sigl=1.046; par3_sigl=0.001089;
			}
			else if(eta<1.392){
				par0_b=-0.02931; par1_b=0.02178; par2_b=-6.606; par3_b=-0.001062;
				par0_c=-0.153; par1_c=0.007903; par2_c=7.817; par3_c=-0.0005719;
				par0_l=-0.3484; par1_l=0.03416; par2_l=8.612; par3_l=-0.001646;
		  
				par0_sigb=0.1621; par1_sigb=-0.01926; par2_sigb=8.8; par3_sigb=0.0008894;
				par0_sigc=0.3699; par1_sigc=-0.03524; par2_sigc=-0.06528; par3_sigc=0.001121;
				par0_sigl=0.3011; par1_sigl=-0.02928; par2_sigl=1.432; par3_sigl=0.001088;
			}
			else if(eta<1.74){
				par0_b=0.3999; par1_b=-0.03765; par2_b=-12.66; par3_b=0.001189;
				par0_c=-0.09843; par1_c=-0.002012; par2_c=6.98; par3_c=-0.00005632;
				par0_l=-0.3413; par1_l=0.03374; par2_l=8.07; par3_l=-0.001653;
		  
				par0_sigb=-0.3558; par1_sigb=0.05506; par2_sigb=15.61; par3_sigb=-0.002056;
				par0_sigc=0.1394; par1_sigc=-0.003827; par2_sigc=3.497; par3_sigc=-0.00005752;
				par0_sigl=0.5663; par1_sigl=-0.06745; par2_sigl=-1.654; par3_sigl=0.00255;
			}
			else{
				par0_b=0.3804; par1_b=-0.03934; par2_b=-10.16; par3_b=0.001295;
				par0_c=0.1074; par1_c=-0.03254; par2_c=3.746; par3_c=0.001216;
				par0_l=-0.1234; par1_l=0.006638; par2_l=4.315; par3_l=-0.0007936;
		  
				par0_sigb=-0.5949; par1_sigb=0.07867; par2_sigb=20.19; par3_sigb=-0.002704;
				par0_sigc=0.4363; par1_sigc=-0.04966; par2_sigc=-0.5373; par3_sigc=0.001785;
				par0_sigl=0.3632; par1_sigl=-0.04; par2_sigl=0.8006; par3_sigl=0.001426;
		  
			}   
	  
			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt; 
			tsjetCorr[0][i]=(1-meanb);
	  
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt; 
			tsjetCorr[1][i]=(1+meanc);
	  
			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt; 
			tsjetCorr[2][i]=(1+meanl);

	      
			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb/pt+par3_sigb*pt; 
			sigmajets[0][i] = (1-meanb)*pt*sigmab;		

			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc/pt+par3_sigc*pt; 
			sigmajets[1][i] = (1+meanc)*pt*sigmac;		

			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl/pt+par3_sigl*pt; 
			sigmajets[2][i] = (1+meanl)*pt*sigmal;

			if (debug){
				cout << " ======= For case 13: 022 type =========== " << endl;
				cout << " For jet pt = " << pt << endl; 
				cout << " b-jet corr = " << 1-meanb << " , sigma = " << sigmab << " , corr sigma = " << (1-meanb)*pt*sigmab << endl;
				cout << " c-jet corr = " << 1-meanc << " , sigma = " << sigmac << " , corr sigma = " << (1-meanc)*pt*sigmac << endl;
				cout << " b-jet corr = " << 1-meanl << " , sigma = " << sigmal << " , corr sigma = " << (1-meanl)*pt*sigmal << endl;
		  
			}
		}
	
	
		break;
	
	case 14: //422 corrections after top pt reweight
	  
		for (int i=0; i<4; i++){
			float pt = jets_f[i].Pt();
			float eta = fabs(jets_f[i].Eta());
		  
			Double_t par0_b=0., par1_b=0., par2_b=0., par3_b=0.;
			Double_t par0_c=0., par1_c=0., par2_c=0., par3_c=0.;
			Double_t par0_l=0., par1_l=0., par2_l=0., par3_l=0.;
			Double_t par0_sigb=0, par1_sigb =0, par2_sigb=0, par3_sigb=0;
			Double_t par0_sigc=0, par1_sigc =0, par2_sigc=0, par3_sigc=0;
			Double_t par0_sigl=0, par1_sigl =0, par2_sigl=0, par3_sigl=0;
		  
			if(eta<0.174){
				par0_b=-0.5774; par1_b=0.0542; par2_b=17.44; par3_b=-0.001465;
				par0_c=-0.1995; par1_c=0.01237; par2_c=8.528; par3_c=-0.0005324;
				par0_l=-0.2979; par1_l=0.02754; par2_l=8.201; par3_l=-0.001326;
			  
				par0_sigb=-0.3333; par1_sigb=0.05044; par2_sigb=14.5; par3_sigb=-0.001823;
				par0_sigc=0.4101; par1_sigc=-0.04369; par2_sigc=-0.987; par3_sigc=0.001559;
				par0_sigl=0.2374; par1_sigl=-0.0199; par2_sigl=1.208; par3_sigl=0.0006941;
			}
			else if(eta<0.348){
				par0_b=-0.5821; par1_b=0.0546; par2_b=17.57; par3_b=-0.001468;
				par0_c=-0.2866; par1_c=0.02688; par2_c=9.53; par3_c=-0.001208;
				par0_l=-0.2291; par1_l=0.01767; par2_l=7.283; par3_l=-0.0009294;
			  
				par0_sigb=-0.4744; par1_sigb=0.06758; par2_sigb=16.99; par3_sigb=-0.002373;
				par0_sigc=0.3315; par1_sigc=-0.03358; par2_sigc=-0.01424; par3_sigc=0.001234;
				par0_sigl=0.3143; par1_sigl=-0.03392; par2_sigl=0.6005; par3_sigl=0.001332;
			}
			else if(eta<0.522){
				par0_b=-0.6125; par1_b=0.05943; par2_b=17.82; par3_b=-0.001656;
				par0_c=-0.1168; par1_c=0.001053; par2_c=7.585; par3_c=-0.0001227;
				par0_l=-0.2434; par1_l=0.02058; par2_l=7.29; par3_l=-0.00107;
			  
				par0_sigb=-0.5308; par1_sigb=0.07682; par2_sigb=17.08; par3_sigb=-0.002757;
				par0_sigc=0.1435; par1_sigc=-0.007334; par2_sigc=2.413; par3_sigc=0.0002287;
				par0_sigl=0.4923; par1_sigl=-0.05751; par2_sigl=-1.827; par3_sigl=0.002178;
			}
			else if(eta<0.696){
				par0_b=-0.5643; par1_b=0.0536; par2_b=16.92; par3_b=-0.001468;
				par0_c=-0.2361; par1_c=0.02047; par2_c=8.749; par3_c=-0.0009981;
				par0_l=-0.293; par1_l=0.0274; par2_l=7.966; par3_l=-0.001331;
			  
				par0_sigb=-0.04004; par1_sigb=0.01117; par2_sigb=9.989; par3_sigb=-0.0003874;
				par0_sigc=0.5479; par1_sigc=-0.06382; par2_sigc=-2.705; par3_sigc=0.002356;
				par0_sigl=0.2242; par1_sigl=-0.01989; par2_sigl=1.711; par3_sigl=0.000754;
			}
			else if(eta<0.879){
				par0_b=-0.5693; par1_b=0.05391; par2_b=17.08; par3_b=-0.001469;
				par0_c=-0.09953; par1_c=-0.0002103; par2_c=7.183; par3_c=-0.0001419;
				par0_l=-0.2977; par1_l=0.02823; par2_l=7.915; par3_l=-0.001372;
			  
				par0_sigb=-0.5279; par1_sigb=0.07609; par2_sigb=17.52; par3_sigb=-0.002753;
				par0_sigc=0.372; par1_sigc=-0.03663; par2_sigc=-0.6704; par3_sigc=0.001218;
				par0_sigl=0.1221; par1_sigl=-0.004342; par2_sigl=2.967; par3_sigl=0.0001104;
			}
			else if(eta<1.131){
				par0_b=-0.5026; par1_b=0.04535; par2_b=15.99; par3_b=-0.001178;
				par0_c=-0.1355; par1_c=0.004565; par2_c=7.865; par3_c=-0.0003958;
				par0_l=-0.3262; par1_l=0.03197; par2_l=8.365; par3_l=-0.001546;
			  
				par0_sigb=-0.008748; par1_sigb=0.006114; par2_sigb=10.23; par3_sigb=-0.0001456;
				par0_sigc=0.1049; par1_sigc=-0.000284; par2_sigc=3.248; par3_sigc=-0.0001325;
				par0_sigl=0.2977; par1_sigl=-0.02945; par2_sigl=1.046; par3_sigl=0.001089;
			}
			else if(eta<1.392){
				par0_b=-0.5189; par1_b=0.04724; par2_b=16.3; par3_b=-0.001244;
				par0_c=-0.153; par1_c=0.007903; par2_c=7.817; par3_c=-0.0005719;
				par0_l=-0.3484; par1_l=0.03416; par2_l=8.612; par3_l=-0.001646;
			  
				par0_sigb=-0.00576; par1_sigb=0.006223; par2_sigb=10.61; par3_sigb=-0.0001532;
				par0_sigc=0.3699; par1_sigc=-0.03524; par2_sigc=-0.06528; par3_sigc=0.001121;
				par0_sigl=0.3011; par1_sigl=-0.02928; par2_sigl=1.432; par3_sigl=0.001088;
			}
			else if(eta<1.74){
				par0_b=-0.4733; par1_b=0.04073; par2_b=15.53; par3_b=-0.0009859;
				par0_c=-0.09843; par1_c=-0.002012; par2_c=6.98; par3_c=-0.00005632;
				par0_l=-0.3413; par1_l=0.03374; par2_l=8.07; par3_l=-0.001653;
			  
				par0_sigb=-0.1803; par1_sigb=0.03173; par2_sigb=12.78; par3_sigb=-0.001192;
				par0_sigc=0.1394; par1_sigc=-0.003827; par2_sigc=3.497; par3_sigc=-0.00005752;
				par0_sigl=0.5663; par1_sigl=-0.06745; par2_sigl=-1.654; par3_sigl=0.00255;
			}
			else{
				par0_b=-0.463; par1_b=0.04362; par2_b=13.5; par3_b=-0.001173;
				par0_c=0.1074; par1_c=-0.03254; par2_c=3.746; par3_c=0.001216;
				par0_l=-0.1234; par1_l=0.006638; par2_l=4.315; par3_l=-0.0007936;
			  
				par0_sigb=-0.1383; par1_sigb=0.01703; par2_sigb=13.63; par3_sigb=-0.0004439;
				par0_sigc=0.4363; par1_sigc=-0.04966; par2_sigc=-0.5373; par3_sigc=0.001785;
				par0_sigl=0.3632; par1_sigl=-0.04; par2_sigl=0.8006; par3_sigl=0.001426;
			}   
		  
			Double_t meanb = par0_b+par1_b*sqrt(pt)+par2_b/pt+par3_b*pt; 
			tsjetCorr[0][i]=(1+meanb);
		  
			Double_t meanc = par0_c+par1_c*sqrt(pt)+par2_c/pt+par3_c*pt; 
			tsjetCorr[1][i]=(1+meanc);
		  
			Double_t meanl = par0_l+par1_l*sqrt(pt)+par2_l/pt+par3_l*pt; 
			tsjetCorr[2][i]=(1+meanl);
		  
		  
			Double_t sigmab = par0_sigb+par1_sigb*sqrt(pt)+par2_sigb/pt+par3_sigb*pt; 
			sigmajets[0][i] = (1+meanb)*sigmab*pt;
			//sigmajets[0][i] = (1+meanb)*sigmab;		
		  
			Double_t sigmac = par0_sigc+par1_sigc*sqrt(pt)+par2_sigc/pt+par3_sigc*pt; 
			sigmajets[1][i] = (1+meanc)*sigmac*pt;
			//sigmajets[1][i] = (1+meanc)*sigmac;		
		  
			Double_t sigmal = par0_sigl+par1_sigl*sqrt(pt)+par2_sigl/pt+par3_sigl*pt; 
			sigmajets[2][i] = (1+meanl)*sigmal*pt;
			//sigmajets[2][i] = (1+meanl)*sigmal;
		}
	  
		if (debug)
			cout << " TS correction: 422 after top pt reweight " << endl;
	  
		break;
	  
	default: // No ts corrections. Use only JES uncertainties
	  
		for (int i=0; i<4; i++){
		  
			tsjetCorr[0][i] = 1.;
			tsjetCorr[1][i] = 1.;
			tsjetCorr[2][i] = 1.;
			sigmajets[0][i] = 0.1*jets_f[i].Pt();
			sigmajets[1][i] = 0.1*jets_f[i].Pt();
			sigmajets[2][i] = 0.1*jets_f[i].Pt();
		  
		}
	  
		if (debug)
			cout << "No corrections applied !!!! " << endl;
	  
		break;
	  
	}// end of switch
  
	return;
}




	





