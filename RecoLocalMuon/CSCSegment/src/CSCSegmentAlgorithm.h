#ifndef CSCSegment_CSCSegmentAlgorithm_h
#define CSCSegment_CSCSegmentAlgorithm_h

/** \class CSCSegmentAlgo
 * An abstract base class for algorithmic classes used to
 * build segments in one chamber of an Endcap Muon CSC.
 *
 * Implementation notes: <BR>
 * For example, CSCSegmentizerSK inherits from this class,
 * and classes ported from ORCA local reco inherit from that.
 *
 * \author M. Sani
 *
 */

#include <DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h>
#include "DataFormats/CSCDigi/interface/CSCWireDigiCollection.h"
#include "DataFormats/CSCDigi/interface/CSCStripDigiCollection.h"
#include <DataFormats/CSCRecHit/interface/CSCSegment.h>
#include <Geometry/CSCGeometry/interface/CSCChamber.h>

#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <vector>

class CSCSegmentAlgorithm {
public:
    /// Constructor
    explicit CSCSegmentAlgorithm(const edm::ParameterSet&) {};
    /// Destructor
    virtual ~CSCSegmentAlgorithm() {};

    /** Run the algorithm = build the segments in this chamber
    */
    //virtual std::vector<CSCSegment> run(const CSCChamber* chamber, const std::vector<const CSCRecHit2D*>& rechits) = 0;  

//    virtual std::vector<CSCSegment> run(const CSCChamber* chamber, const std::vector<const CSCRecHit2D*>& rechits,
//                                        const std::vector< std::pair<int, const CSCWireDigiCollection::Range& > >& wires, 
//                                        const std::vector< std::pair<int, const CSCStripDigiCollection::Range& > >& strips ) = 0;

    virtual std::vector<CSCSegment> run(const CSCChamber* chamber, 
                                        std::vector< std::pair<const CSCLayer*, CSCWireDigiCollection::Range > >& wires,
                                        std::vector< std::pair<const CSCLayer*, CSCStripDigiCollection::Range > >& strips ) = 0;


    private:
};

#endif
