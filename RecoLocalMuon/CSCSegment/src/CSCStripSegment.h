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
  std::pair<int,double>* stripHits() {return sHits;}

  ~CSCStripSegment();

private:
  
  int theKeyHalfStrip;
  int nlayersWithHits;
  int thePatternRank;
  std::pair<int,double> sHits[6];
  // TH2F* stripPattern

};

#endif
