#ifndef CSCSegment_CSCWireSegment_H
#define CSCSegment_CSCWireSegment_H

#include "TH2F.h"

class CSCWireSegment
{

public:

  CSCWireSegment();
  CSCWireSegment(int wg, int nLayer, TH2F* wireSegHist);

  int keyWG() const { return theKeyWG; }
  int nLayersWithHits() const { return nlayersWithHits; }
  std::pair<int,double>* wireHits() {return wHits;}

  ~CSCWireSegment();

private:

  int theKeyWG;
  int nlayersWithHits;
  std::pair<int,double> wHits[6] ;
//  TH2F* wirePattern;

};
#endif
