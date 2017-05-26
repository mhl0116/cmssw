#ifndef CSCSegment_CSCSegmentBuilder_h
#define CSCSegment_CSCSegmentBuilder_h

/** \class CSCSegmentBuilder 
 * Algorithm to build CSCSegment's from CSCRecHit2D collection
 * by implementing a 'build' function required by CSCSegmentProducer.
 *
 * Implementation notes: <BR>
 * Configured via the Producer's ParameterSet. <BR>
 * Presume this might become an abstract base class one day. <BR>
 *
 * \author M. Sani
 *
 *
 */

#include <DataFormats/CSCDigi/interface/CSCWireDigiCollection.h>
#include <DataFormats/CSCDigi/interface/CSCStripDigiCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

#include <FWCore/ParameterSet/interface/ParameterSet.h>

class CSCLayer;
class CSCGeometry;
class CSCSegmentAlgorithm;

class CSCSegmentBuilder {
public:

    /// Typedefs
//    typedef std::pair<int, const CSCWireDigiCollection::Range& > LayerWireContainer;
//    typedef std::pair<int, const CSCStripDigiCollection::Range& > LayerStripContainer;
    typedef std::pair< const CSCLayer*, const CSCWireDigiCollection::Range& > LayerWireContainer;
    typedef std::pair< const CSCLayer*, const CSCStripDigiCollection::Range& > LayerStripContainer;
   
    /** Configure the algorithm via ctor.
     * Receives ParameterSet percolated down from EDProducer
     * which owns this Builder.
     */
    explicit CSCSegmentBuilder(const edm::ParameterSet&);
    /// Destructor
    ~CSCSegmentBuilder();

    /** Find rechits in each CSCChamber, build CSCSegment's in each chamber,
     *  and fill into output collection.
     */
    void build(const CSCRecHit2DCollection* rechits, 
               const CSCWireDigiCollection* wires,
               const CSCStripDigiCollection* strips, CSCSegmentCollection& oc);

    /** Cache pointer to geometry _for current event_
     */
    void setGeometry(const CSCGeometry* geom);

    const CSCLayer* getLayer( const CSCDetId& detId );

private:

    const CSCGeometry* geom_;
    std::map<std::string, CSCSegmentAlgorithm*> algoMap;
};

#endif
