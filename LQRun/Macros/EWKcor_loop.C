#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

TList *FileList;
TFile *Target;

void EWKcor_loop() {
  
//  Int_t iso=00; Int_t pt=3;  

//  Target = TFile::Open( "Total_FR_TL_13.root", "RECREATE" );
  Target = TFile::Open( "QCD_mu15_v3_FR40_31_bis.root", "RECREATE" );
  char faa[100];
  FileList = new TList();
  for (UInt_t i=0; i<1; i++) {
    strcpy(faa,"");
//    sprintf(faa,"SingleMu_FR40_job%i_13.root",i);
    sprintf(faa,"QCD_mu15_v3_FR40_31.root",i);
    FileList->Add( TFile::Open(faa) ); 
  }

  FileList->Print();

  TString path( (char*)strstr( Target->GetPath(), ":" ) );
  path.Remove( 0, 2 );

  TFile *first_source = (TFile*)FileList->First();
  first_source->cd( path );
  TDirectory *current_sourcedir = gDirectory;

  // loop over all keys in this directory
  TChain *globChain = 0;
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key;
  while ( (key = (TKey*)nextkey())) {

    // read object from first source file
    first_source->cd( path );
    TObject *obj = key->ReadObj();
    if ( obj->IsA()->InheritsFrom( "TH2F" ) || true) {
      // descendant of TH1F -> merge it

      //      cout << "Merging histogram " << obj->GetName() << endl;
      TH1F *h1 = (TH1F*)obj;

      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      TFile *nextsource = (TFile*)FileList->After( first_source );
      Int_t scal=0;
      while ( nextsource ) {
        
        // make sure we are at the correct directory level by cd'ing to path
        nextsource->cd( path );
        TH1F *h2 = (TH1F*)gDirectory->Get( h1->GetName() );
        if ( h2 ) {
          h1->Add( h2 );  //scale factor not need if is need the same as to be applied to h1
          cout<<"file "<<nextsource->GetName()<<endl;
          delete h2; // don't know if this is necessary, i.e. if 
                     // h2 is created by the call to gDirectory above.
        }
	
        nextsource = (TFile*)FileList->After( nextsource );
	scal++;
      }
    }
    // now write the merged histogram (which is "in" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by "target->Write()" below
    if ( obj ) {
      Target->cd();
      obj->Write( key->GetName() );
    }
    
  } // while ( ( TKey *key = (TKey*)nextkey() ) )
  
  Target->Write();
  
  Target->cd();
  getFakerate2(h_nEvents, h_nEventsFO, h_FOrate);
  getFakerate1(h_nVertex1, h_nVertex0, h_nVertex2);
  h_FOrate->Write("h_FOrate3");
  h_nEvents->Write("h_Events2");
  h_nEventsFO->Write("h_EventsFO2");
  h_nVertex1->Write("h_nVertex1_2");
  h_nVertex0->Write("h_nVertex0_2");
  h_nVertex2->Write("h_nVertex3");
  delete h_nVertex2;
  delete h_FOrate;
  Target->Close();

}   


void getFakerate2(TH2F* h1, TH2F* h2, TH2F* out) {
   double frate,ferr;
   Int_t nbinX=h1->GetNbinsX();
   Int_t nbinY=h1->GetNbinsY();
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

void getFakerate1(TH1F* h1, TH1F* h2, TH1F* out) {
   double frate,ferr;
   Int_t nbinX=h1->GetNbinsX();
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

