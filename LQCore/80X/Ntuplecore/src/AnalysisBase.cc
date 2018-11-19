#include "AnalysisBase.h"

static const double _arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
static const double _arraypT[]  = {10.,15.,20.,25.,30.,35.,45.,60.,80.,100.};
static const Int_t nintpT=7;
static const Int_t ninteta=4;

AnalysisBase::AnalysisBase(): Mass_Z(91.1876), Mass_W(80.398){
}

AnalysisBase::~AnalysisBase(){

}


int AnalysisBase::nthdigit(int x, int n) {
  static int powersof10[] = {1, 10, 100, 1000, 10000, 100000};
  return ((x / powersof10[n]) % 10);
}



bool AnalysisBase::isPrompt(long pdgid) {
  pdgid = abs(pdgid);
  if (pdgid >= 1000001 && pdgid <= 1000006) return true; // SUSY squarks
  else if (pdgid >= 1000011 && pdgid <= 1000016) return true; // SUSY sleptons sneutrinos
  else if (pdgid >= 2000001 && pdgid <= 2000006) return true; // SUSY squarks
  else if (pdgid >= 2000011 && pdgid <= 2000015) return true; // SUSY sleptons
  else if (pdgid >= 1000021 && pdgid <= 1000025) return true; // SUSY gluino chargino neutralinos
  else if (pdgid >= 1000035 && pdgid <= 1000039) return true; // SUSY neutralinos charginos gravitino*/
  
  if (pdgid == 24) return true; // Z
  else if (pdgid == 23) return true; // W
  else if (pdgid == 15) return true; // taus
  else if (pdgid == 90) return true; // N
  else if (pdgid == 13) return true;
  else return false;
  //  return indexToPromptBool[ abs(pdgToIndex[pdgid]) ];
}


void AnalysisBase::getFakerate(TH2F* h1, TH2F* h2, TH2F* out, int nbinX, int nbinY) {
   double frate,ferr;
   for (int i=1; i<nbinX+1; i++)
      for (int j=1; j<nbinY+1; j++){
         double a = h1->GetBinContent(i,j);
         double b = h2->GetBinContent(i,j);
         if (b){
            frate = ((double) a)/((double) b);
            ferr = sqrt( frate*(1-frate)/(double) b); 
            out->SetBinContent(i,j,frate);
            out->SetBinError(i,j,ferr);
         }
         else {
            out->SetBinContent(i,j,0);
         }
   }
}

void AnalysisBase::getFakerate(TH1F* h1, TH1F* h2, TH1F* out, int nbinX) {
   double frate,ferr;
   for (int i=1; i<nbinX+1; i++) {
     double a = h1->GetBinContent(i);
     double b = h2->GetBinContent(i);
       if (b){
         frate = ((double) a)/((double) b);
         ferr = sqrt( frate*(1-frate)/(double) b);
         out->SetBinContent(i,frate);
         out->SetBinError(i,ferr);
       }
       else {
         out->SetBinContent(i,0);
       }
   }
}

void AnalysisBase::DoubleANDSinglebkg(std::vector<snu::KParticle>& leptonColli, UInt_t &ilep, std::vector<snu::KParticle>& leptonCollj, UInt_t &jlep, Double_t *****fakeN, UInt_t &type) {

  /*
  double _arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
  if (pT35) 
    double _arraypT [] = {10.,15.,20.,25.,35.,45.,60.,80.,100.};
  else {
    _arraypT = new double [nintpT+1];
    _arraypT[0] = 10.;
    _arraypT[1] = 15.;
    _arraypT[2] = 20.;
    _arraypT[3] = 25.;
    _arraypT[4] = minbin;
    for (UInt_t i=0; i+5<nintpT+1; i++) 
      _arraypT[i+5] = minbin + binwidh * exp (i);
  }
*/
  int i0=1; int j0=1;
  int i1=1; int j1=1;
  double eta0= fabs(leptonColli[ilep].Eta());
  double Pt0 = leptonColli[ilep].Pt();
  double eta1= fabs(leptonCollj[jlep].Eta());
  double Pt1 = leptonCollj[jlep].Pt();
  if (eta0<0.0 || eta0>=2.5) {cout<<"CACCHIO eta!!!! "<<eta0<<endl; eta0<0.0 ? eta0=0.0 : eta0=2.49;} 
  if (Pt0<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt0<<endl; Pt0=10.0;}
  if (eta1<0.0 || eta1>=2.5) {cout<<"CACCHIO eta!!!! "<<eta1<<endl; eta1<0.0 ? eta1=0.0 : eta1=2.49;}
  if (Pt1<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt1<<endl; Pt1=10.0;}

  while(1) {
    if( _arrayeta[(i0-1)%(ninteta+1)]<=eta0 && _arrayeta[i0%(ninteta+1)]>eta0 )
      break;
    i0++;
  }
  if (Pt0>=_arraypT[nintpT]) j0=nintpT;
  else {
    while(1) {
      if( _arraypT[(j0-1)%(nintpT+1)]<=Pt0 && _arraypT[j0%(nintpT+1)]>Pt0 )
        break;
      j0++;
    }
  }

  while(1) {
    if( _arrayeta[(i1-1)%(ninteta+1)]<=eta1 && _arrayeta[i1%(ninteta+1)]>eta1 )
      break;
    i1++;
  }
  if (Pt1>=_arraypT[nintpT]) j1=nintpT;
  else {
    while(1) {
      if( _arraypT[(j1-1)%(nintpT+1)]<=Pt1 && _arraypT[j1%(nintpT+1)]>Pt1 )
        break;
      j1++;
    }
  }
  fakeN[0][i1-1][j1-1][i0-1][j0-1]+=1;
  fakeN[type][i1-1][j1-1][i0-1][j0-1]+=1;
}

double AnalysisBase::DoublebackGround(TH2F* fakerate, std::vector<snu::KParticle>& leptonColl, UInt_t &ilep, UInt_t &jlep, Double_t *****fakeN, UInt_t &type, Double_t weight) {
  double bkg=0;

  int i0=1; int j0=1;
  int i1=1; int j1=1;
  double eta0= fabs(leptonColl[ilep].Eta());
  double Pt0 = leptonColl[ilep].Pt();
  double eta1= fabs(leptonColl[jlep].Eta());
  double Pt1 = leptonColl[jlep].Pt();
  if (eta0<0.0 || eta0>=2.5) {cout<<"CACCHIO eta!!!! "<<eta0<<endl; eta0<0.0 ? eta0=0.0 : eta0=2.49;}
  if (Pt0<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt0<<endl; Pt0=10.0;}
  if (eta1<0.0 || eta1>=2.5) {cout<<"CACCHIO eta!!!! "<<eta1<<endl; eta1<0.0 ? eta1=0.0 : eta1=2.49;}
  if (Pt1<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt1<<endl; Pt1=10.0;}

  while(1) {
    if( _arrayeta[(i0-1)%(ninteta+1)]<=eta0 && eta0<_arrayeta[i0%(ninteta+1)] ) 
      break;
    i0++;
  }
  if (Pt0>=_arraypT[nintpT]) j0=nintpT;
  else {
    while(1) {
      if( _arraypT[(j0-1)%(nintpT+1)]<=Pt0 && Pt0<_arraypT[j0%(nintpT+1)] )
	break;
      j0++;
    }
  }

  while(1) {
    if( _arrayeta[(i1-1)%(ninteta+1)]<=eta1 && eta1<_arrayeta[i1%(ninteta+1)] )
      break;
    i1++;
  }
  if (Pt1>=_arraypT[nintpT]) j1=nintpT;
  else {
    while(1) {
      if( _arraypT[(j1-1)%(nintpT+1)]<=Pt1 && Pt1<_arraypT[j1%(nintpT+1)] )
	break;
      j1++;
    }
  }
  
  double A = fakerate->GetBinContent(i0,j0);
  double B = fakerate->GetBinContent(i1,j1);
  //double deltaA = fakerate->GetBinError(i0,j0);
  //double deltaB = fakerate->GetBinError(i1,j1);
  
  fakeN[0][i0-1][j0-1][i1-1][j1-1]+=weight;
  fakeN[type][i0-1][j0-1][i1-1][j1-1]+=weight;

  bkg = A*B / (( 1-A )*( 1-B ));
  //errbkg = sqrt ( ( B*(1-B)*deltaA+A*(1-A)*deltaB )/( pow(1-A,2)*pow(1-B,2) ) );

  return bkg;
}

double AnalysisBase::SinglebackGround(TH2F* fakerate, std::vector<snu::KParticle>& leptonColl, UInt_t &ilep, Double_t ***fakeN, UInt_t &type, Double_t weight) {
  double bkg=0;
  
  int i=1; int j=1;
  double eta= fabs(leptonColl[ilep].Eta());
  double Pt = leptonColl[ilep].Pt();
  if (eta<0.0 || eta>=2.5) {cout<<"CACCHIO eta!!!! "<<eta<<endl; eta<0.0 ? eta=0.0 : eta=2.49;}
  if (Pt<20.0) {cout<<"CACCHIO Pt!!!! "<<Pt<<endl; Pt=10.0;}

  while(1) {
    if( _arrayeta[(i-1)%(ninteta+1)]<=eta && eta<_arrayeta[i%(ninteta+1)] )
      break;
    i++;
  }
  if (Pt>=_arraypT[nintpT]) j=nintpT;
  else {
    while(1) {
      if( _arraypT[(j-1)%(nintpT+1)]<=Pt && Pt<_arraypT[j%(nintpT+1)] ) 
	break;
      j++;
    }
  }
  fakeN[0][i-1][j-1]+=weight;
  fakeN[type][i-1][j-1]+=weight;

  bkg = fakerate->GetBinContent(i,j) /( 1-fakerate->GetBinContent(i,j) );
  //errbkg = fakerate->GetBinError(i,j) / pow( 1-fakerate->GetBinContent(i,j),2 );

  return bkg; 
}

double AnalysisBase::DoubleTOSinglebkg(TH2F* fakerate, std::vector<snu::KParticle>& leptonColl, UInt_t &ilep, UInt_t &jlep) {
  double bkg=0;

  int i0=1; int j0=1;
  int i1=1; int j1=1;
  double eta0= fabs(leptonColl[ilep].Eta());
  double Pt0 = leptonColl[ilep].Pt();
  double eta1= fabs(leptonColl[jlep].Eta());
  double Pt1 = leptonColl[jlep].Pt();
  if (eta0<0.0 || eta0>=2.5) {cout<<"CACCHIO eta!!!! "<<eta0<<endl; eta0<0.0 ? eta0=0.0 : eta0=2.49;}
  if (Pt0<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt0<<endl; Pt0=10.0;}
  if (eta1<0.0 || eta1>=2.5) {cout<<"CACCHIO eta!!!! "<<eta1<<endl; eta1<0.0 ? eta1=0.0 : eta1=2.49;}
  if (Pt1<10.0) {cout<<"CACCHIO Pt!!!! "<<Pt1<<endl; Pt1=10.0;}

  while(1) {
    if( _arrayeta[(i0-1)%(ninteta+1)]<=eta0 && eta0<_arrayeta[i0%(ninteta+1)] ) 
      break;
    i0++;
  }
  if (Pt0>=_arraypT[nintpT]) j0=nintpT;
  else {
    while(1) {
      if( _arraypT[(j0-1)%(nintpT+1)]<=Pt0 && Pt0<_arraypT[j0%(nintpT+1)] )
	break;
      j0++;
    }
  }

  while(1) {
    if( _arrayeta[(i1-1)%(ninteta+1)]<=eta1 && eta1<_arrayeta[i1%(ninteta+1)] )
      break;
    i1++;
  }
  if (Pt1>=_arraypT[nintpT]) j1=nintpT;
  else {
    while(1) {
      if( _arraypT[(j1-1)%(nintpT+1)]<=Pt1 && Pt1<_arraypT[j1%(nintpT+1)] )
	break;
      j1++;
    }
  }
  
  double A = fakerate->GetBinContent(i0,j0);
  double B = fakerate->GetBinContent(i1,j1);

  bkg = (-A/(1-A))* (A*(1-B)+B*(1-A)) / (( 1-A )*( 1-B ));

  return bkg;
}


void AnalysisBase::BackGroundEstimate(TH2F* fakerate,  Double_t ***fakeN1, Double_t *****prova, Double_t *****fakeN2, Double_t *singolo, Double_t *errsingolo, Double_t *doppio, Double_t *errdoppio, Double_t *singoloreale, Double_t *errsingoloreale, Double_t *doppioreale, Double_t *totale, Double_t *doubletosingle, Double_t *errdoubletosingle) {
  UInt_t nbinX=fakerate->GetNbinsX(); UInt_t nbinY=fakerate->GetNbinsY();
  Double_t tmperrsingolo, tmperrdoppio, tmperrsingoloreale, tmpdoubletosinglerr;
  for (UInt_t z=0; z<4; z++) {
    tmperrsingolo=tmperrdoppio=tmperrsingoloreale=tmpdoubletosinglerr=0;
    for (UInt_t i=1; i<nbinX+1; i++)
      for (UInt_t j=1; j<nbinY+1; j++) {
	if (fakeN1[z][i-1][j-1]) {
	  Double_t FR = fakerate->GetBinContent(i,j);
	  Double_t deltaFR = fakerate->GetBinError(i,j);
	  singolo[z]+=fakeN1[z][i-1][j-1]*FR/(1-FR);
	  tmperrsingolo+=pow(fakeN1[z][i-1][j-1],2)*pow( (deltaFR/pow( (1-FR) ,2)) ,2) + fakeN1[z][i-1][j-1]*pow(FR/(1-FR),2);
	}
	for (UInt_t m=1; m<nbinX+1; m++)
	  for (UInt_t n=1; n<nbinY+1; n++) {
	    if (fakeN2[z][i-1][j-1][m-1][n-1]) {
	      Double_t FRi = fakerate->GetBinContent(i,j);
	      Double_t deltaFRi = fakerate->GetBinError(i,j);
	      Double_t FRm = fakerate->GetBinContent(m,n);
	      Double_t deltaFRm = fakerate->GetBinError(m,n);
	      Double_t W = FRi*FRm / ((1-FRi)*(1-FRm));
	      Double_t deltaW = sqrt( ( pow(FRi*(1-FRi), 2)*pow(deltaFRm,2) + pow(FRm*(1-FRm), 2)*pow(deltaFRi,2 ) ) / ( pow( (1-FRi) ,4)*pow( (1-FRm) ,4) ) );
	      doppio[z]+=fakeN2[z][i-1][j-1][m-1][n-1]*W;
	      tmperrdoppio+=pow(fakeN2[z][i-1][j-1][m-1][n-1],2)*pow(deltaW,2) + fakeN2[z][i-1][j-1][m-1][n-1]*pow(W,2);
	    }  
	    if (fakeN2[z][i-1][j-1][m-1][n-1] || prova[z][i-1][j-1][m-1][n-1]) {
            Double_t FRi = fakerate->GetBinContent(i,j);
            Double_t FRm = fakerate->GetBinContent(m,n);
            Double_t deltaFRi = fakerate->GetBinError(i,j);
            Double_t deltaFRm = fakerate->GetBinError(m,n);
	    Double_t singolorealetmp= FRi/(1-FRi) * ( prova[z][i-1][j-1][m-1][n-1] - ( fakeN2[z][i-1][j-1][m-1][n-1] * ( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)) ) );
            singoloreale[z]+= FRi/(1-FRi) * ( prova[z][i-1][j-1][m-1][n-1] - ( fakeN2[z][i-1][j-1][m-1][n-1] * ( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)) ) );
            tmperrsingoloreale+=pow(prova[z][i-1][j-1][m-1][n-1], 2)*pow(deltaFRi/pow(1-FRi,2), 2) + prova[z][i-1][j-1][m-1][n-1]*pow(FRi/(1-FRi), 2) + pow(fakeN2[z][i-1][j-1][m-1][n-1], 2)*(pow(FRm-1, 2)*pow(FRm+FRi*(2-3*FRm), 2)*pow(deltaFRi,2) + pow(FRi-1, 4)*pow(FRi, 2)*pow(deltaFRm,2)) / (pow( (FRi-1) ,6)*pow( (FRm-1) ,4)) + fakeN2[z][i-1][j-1][m-1][n-1]*pow( (( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)))*FRi/(1-FRi) ,2);
            Double_t doppiorealetmp= FRi*FRm*fakeN2[z][i-1][j-1][m-1][n-1] / ((1-FRi)*(1-FRm));
            doppioreale[z]+= FRi*FRm*fakeN2[z][i-1][j-1][m-1][n-1] / ((1-FRi)*(1-FRm));
            totale[z]+=singolorealetmp + doppiorealetmp;

	    doubletosingle[z] += fakeN2[z][i-1][j-1][m-1][n-1] * ( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm));
	    tmpdoubletosinglerr += fakeN2[z][i-1][j-1][m-1][n-1]*pow(( FRm*(1-FRi)+FRi*(1-FRm) ) / ((1-FRi)*(1-FRm)),2) + pow(fakeN2[z][i-1][j-1][m-1][n-1]*deltaFRi/pow(1-FRi,2),2) + pow(fakeN2[z][i-1][j-1][m-1][n-1]*deltaFRm/pow(1-FRm,2),2);
	    }
	  
	  }
    }
    errsingoloreale[z]=sqrt(tmperrsingoloreale);
    errsingolo[z]=sqrt(tmperrsingolo);
    errdoppio[z]=sqrt(tmperrdoppio);
    errdoubletosingle[z]=sqrt(tmpdoubletosinglerr);
  }
}

void AnalysisBase::WeigthedMean(std::vector<double>& value, std::vector<double>& error, double &mean, double &stddev) {
if (value.size()>0) {
  double DEN=0; double NUM=0; double weight;
  for(UInt_t iii=0; iii<value.size(); iii++) {
    weight=1/pow(error[iii],2);
    DEN+=weight;
    NUM+=value[iii]*weight;
  }
    mean=NUM/DEN;
    stddev=sqrt(1/DEN);
 }   
}
// Function to reverse the trigger weight on the events
/*
Double_t TriggerWeight(stringtobool* HLT_triggered) {

  Char_t name[20];
  Int_t pt[]={5,8,12,15,30};
 
  Int_t mu5[]={0,0,40,100,100,150,0,320,320,640,320,320,320};
  Int_t mu8[]={4,20,20,0,60,120,120,40,80,80,80,0,0};
  Int_t mu12[]={10,420,420,0,630,450,450,70,70,70,70,0,0};
  Int_t mu15[]={0,1,160,160,0,240,720,720,65,25,25,25,0};
  Int_t mu30[]={1,1,1,0,25,80,80,10,4,4,4,0,0};
  Int_t L1_Mu3[]={60,90,120,180,240,600};
  Int_t L1_Mu7[]={1,1,40,60,80,100};
  Int_t L1_Mu10[]={1,1,1,20,30,80};
  Int_t L1_Mu12[]={1,1,1,15,20,60};

  Int_t all[5][13];
  for(Int_t i=0;i<5;i++)
    for(Int_t j=0;j<13;j++) {
      switch (i) {
	case 0:
	  if(j<4)
	    all[i][j]=mu5[j]*L1_Mu3[0];
	  else if(j<7)
	    all[i][j]=mu5[j]*L1_Mu3[1];
	  else if (j<8)
	    all[i][j]=mu5[j]*L1_Mu3[2];
	  else if (j<9)
	    all[i][j]=mu5[j]*L1_Mu3[3];
	  else if (j<10)
	    all[i][j]=mu5[j]*L1_Mu3[4];
	  else if (j<13)
	    all[i][j]=mu5[j]*L1_Mu3[5];
	  else 
	    all[i][j]=0;
	  break;
	case 1:
	  if(j<2)
	    all[i][j]=mu8[j]*L1_Mu3[0];
	  else if(j<5)
	    all[i][j]=mu8[j]*L1_Mu3[1];
	  else if (j<6)
	    all[i][j]=mu8[j]*L1_Mu3[2];
	  else if (j<7)
	    all[i][j]=mu8[j]*L1_Mu3[3];
	  else if (j<8)
	    all[i][j]=mu8[j]*L1_Mu3[4];
	  else if (j<11)
	    all[i][j]=mu8[j]*L1_Mu3[5];
	  else
	    all[i][j]=0;
	  break;
	case 2:
	  if(j<2)
	    all[i][j]=mu12[j]*L1_Mu7[0];
	  else if(j<5)
	    all[i][j]=mu12[j]*L1_Mu7[1];
	  else if (j<6)
	    all[i][j]=mu12[j]*L1_Mu7[2];
	  else if (j<7)
	    all[i][j]=mu12[j]*L1_Mu7[3];
	  else if (j<8)
	    all[i][j]=mu12[j]*L1_Mu7[4];
	  else if (j<11)
	    all[i][j]=mu12[j]*L1_Mu7[5];
	  else
	    all[i][j]=0;
	  break;
	case 3:
	  if(j<3)
	    all[i][j]=mu15[j]*L1_Mu10[0];
	  else if(j<6)
	    all[i][j]=mu15[j]*L1_Mu10[1];
	  else if (j<7)
	    all[i][j]=mu15[j]*L1_Mu10[2];
	  else if (j<8)
	    all[i][j]=mu15[j]*L1_Mu10[3];
	  else if (j<9)
	    all[i][j]=mu15[j]*L1_Mu10[4];
	  else if (j<12)
	    all[i][j]=mu15[j]*L1_Mu10[5];
	  else
	    all[i][j]=0;
	  break;
	case 4:
	  if(j<2)
	    all[i][j]=mu30[j]*L1_Mu12[0];
	  else if(j<5)
	    all[i][j]=mu30[j]*L1_Mu12[1];
	  else if (j<6)
	    all[i][j]=mu30[j]*L1_Mu12[2];
	  else if (j<7)
	    all[i][j]=mu30[j]*L1_Mu12[3];
	  else if (j<8)
	    all[i][j]=mu30[j]*L1_Mu12[4];
	  else if (j<11)
	    all[i][j]=mu30[j]*L1_Mu12[5];
	  else
	    all[i][j]=0;
	  break;
	}
    }

  for(Int_t i=4;i>=0;i--)
    for(Int_t ver=0;ver<13;ver++) {
      strcpy(name,"");strcpy(name,"");
      sprintf(name,"HLT_Mu%i_v%i",pt[i],ver+1);
      
      if ( HLT_triggered->find(name) != HLT_triggered->end() && (*HLT_triggered)[name] )
	return all[i][ver];
   
    }
  return -1;
 
}
*/
