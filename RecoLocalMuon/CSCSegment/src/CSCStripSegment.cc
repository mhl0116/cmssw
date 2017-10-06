#include "RecoLocalMuon/CSCSegment/src/CSCStripSegment.h"

CSCStripSegment::CSCStripSegment() {}

CSCStripSegment::CSCStripSegment(int halfStrip,
                               int nLayer,
                               int patternRank,
                               TH2F* stripSegHist) :
   theKeyHalfStrip( halfStrip ),
   nlayersWithHits( nLayer ),
   thePatternRank( patternRank )

{

   TH1D* sHitHists[6];
   for (int i = 0; i < 6; i++) {

       sHitHists[i] = stripSegHist->ProjectionX("layer"+TString(i+1),i+1,i+1);
       sHits[i] = std::make_pair(i+1, sHitHists[i]->GetMean()+0.5 );

   }

}


CSCStripSegment::~CSCStripSegment() {}

