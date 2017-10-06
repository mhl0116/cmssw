#include "RecoLocalMuon/CSCSegment/src/CSCWireSegment.h"

CSCWireSegment::CSCWireSegment() {}

CSCWireSegment::CSCWireSegment(int wg,
                               int nLayer,
                               TH2F* wireSegHist) :
   theKeyWG( wg ),
   nlayersWithHits( nLayer )
  
{

   TH1D* wHitHists[6];
   for (int i = 0; i < 6; i++) {

       wHitHists[i] = wireSegHist->ProjectionX("layer"+TString(i+1),i+1,i+1);
       wHits[i] = std::make_pair(i+1, wHitHists[i]->GetMean()+0.5 ); 
       // first number is layer, second number is wPos in unit of wire group
       // +0.5 is because of ROOT histogram property, GetMean() returns 4.5 for example if fill only one entry at 4 

       }

}


CSCWireSegment::~CSCWireSegment() {}


