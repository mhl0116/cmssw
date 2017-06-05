#include <DataFormats/CSCRecHit/interface/CSCRecHit2D.h>
#include <DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h>

#include <DataFormats/CSCRecHit/interface/CSCSegment.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

#include <DataFormats/CSCRecHit/interface/CSCWireHit.h>
#include <DataFormats/CSCRecHit/interface/CSCWireHitCollection.h>

#include <DataFormats/CSCRecHit/interface/CSCStripHit.h>
#include <DataFormats/CSCRecHit/interface/CSCStripHitCollection.h>

#include <DataFormats/Common/interface/Wrapper.h>
#include <vector>

namespace DataFormats_CSCRecHit {
  struct dictionary {
    std::map<CSCDetId,std::pair<unsigned int,unsigned int> > dummycscdetid1;  
    std::map<CSCDetId,std::pair<unsigned long,unsigned long> > dummycscdetid2;  
    CSCRecHit2DCollection dc;
    edm::Wrapper<CSCRecHit2DCollection> dwc;
    CSCSegmentCollection seg;    
    edm::Wrapper<CSCSegmentCollection> dwc1;
    CSCWireHitCollection clWD;
    edm::Wrapper<CSCWireHitCollection> wWD;
    CSCStripHitCollection clSD;
    edm::Wrapper<CSCStripHitCollection> wSD;
    CSCSegmentRef ref;    
  };
}
