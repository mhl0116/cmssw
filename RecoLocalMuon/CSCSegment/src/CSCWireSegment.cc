#include "RecoLocalMuon/CSCSegment/src/CSCWireSegment.h"

CSCWireSegment::CSCWireSegment() {}

CSCWireSegment::CSCWireSegment(int wg,
                               int nLayer,
                               TH2F* wireSegHist) :
   theKeyWG( wg ),
   nlayersWithHits( nLayer )
  
{

}


CSCWireSegment::~CSCWireSegment() {}


