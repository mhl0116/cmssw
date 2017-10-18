#include "RecoLocalMuon/CSCSegment/src/CSCWireSegment.h"

CSCWireSegment::CSCWireSegment() {}

CSCWireSegment::CSCWireSegment(int wg,
                               int nLayer,
                               TH2F* wireSegHist) :
   theKeyWG( wg ),
   nlayersWithHits( nLayer )
  
{

   TH1D* wHitHists[6];
   TH1D* nHitHists = wireSegHist->ProjectionY("nLayerHits",0,-1);
   for (int i = 0; i < 6; i++) {

       wHitHists[i] = wireSegHist->ProjectionX("layer"+TString(i+1),i+1,i+1);
       wHits[i] = wHitHists[i]->GetMean()+0.5; 
       // first number is layer, second number is wPos in unit of wire group
       // +0.5 is because of ROOT histogram property, GetMean() returns 4.5 for example if fill only one entry at 4 
       nHits[i] = nHitHists->GetBinContent(i+1);

       }

}


CSCWireSegment::~CSCWireSegment() {}

void CSCWireSegment::updateWHits(double* wHits2, int* nHits2) 
{

   for (int i = 0; i < 6; i++) {

       wHits[i] = (wHits[i]*nHits[i] + wHits2[i]*nHits2[i] )/(nHits[i]+nHits2[i]);
       nHits[i] = nHits[i]+nHits2[i];

       }

}
