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

}


CSCStripSegment::~CSCStripSegment() {}

