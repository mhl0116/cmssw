#ifndef CSCSegment_CSCStripSegment_H
#define CSCSegment_CSCStripSegment_H

#include "TH2F.h"

class CSCStripSegment 
{

public:

  CSCStripSegment();
  CSCStripSegment(int halfStrip, int nLayer, int patternRank, TH2F* stripSegHist);

  int keyHalfStrip() const {return theKeyHalfStrip;}
  int nLayersWithHits() const {return nlayersWithHits;}
  int patternRank() const {return thePatternRank;}

  ~CSCStripSegment();

private:
  
  int theKeyHalfStrip;
  int nlayersWithHits;
  int thePatternRank;
  // TH2F* stripPattern
};

#endif
