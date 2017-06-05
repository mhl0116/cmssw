
/** \file CSCSegmentBuilder.cc
 *
 *
 */

//#include <RecoLocalMuon/CSCRecHitD/src/CSCHitFromStripOnly.h>
//#include <RecoLocalMuon/CSCRecHitD/src/CSCHitFromWireOnly.h>
//#include <RecoLocalMuon/CSCRecHitD/src/CSCWireHitCollection.h>
//#include <RecoLocalMuon/CSCRecHitD/src/CSCStripHitCollection.h>
//#include <RecoLocalMuon/CSCRecHitD/src/CSCWireHit.h>
//#include <RecoLocalMuon/CSCRecHitD/src/CSCStripHit.h>
//#include <RecoLocalMuon/CSCRecHitD/src/CSCRangeMapForRecHit.h>

#include <RecoLocalMuon/CSCSegment/src/CSCSegmentBuilder.h>
#include <Geometry/CSCGeometry/interface/CSCChamberSpecs.h>
#include <Geometry/CSCGeometry/interface/CSCLayer.h>
#include <Geometry/CSCGeometry/interface/CSCGeometry.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>
#include <DataFormats/CSCRecHit/interface/CSCRecHit2D.h>
#include <DataFormats/CSCRecHit/interface/CSCRangeMapAccessor.h>

#include <RecoLocalMuon/CSCSegment/src/CSCSegmentAlgorithm.h>
#include <RecoLocalMuon/CSCSegment/src/CSCSegmentBuilderPluginFactory.h>

#include <FWCore/Utilities/interface/Exception.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h> 

CSCSegmentBuilder::CSCSegmentBuilder(const edm::ParameterSet& ps) : geom_(0) {
    
    // The algo chosen for the segment building
    int chosenAlgo = ps.getParameter<int>("algo_type") - 1;
    
    // Find appropriate ParameterSets for each algo type
    std::vector<edm::ParameterSet> algoPSets = ps.getParameter<std::vector<edm::ParameterSet> >("algo_psets");

    // Now load the right parameter set
    // Algo name
    std::string algoName = algoPSets[chosenAlgo].getParameter<std::string>("algo_name");
        
    LogDebug("CSCSegment|CSC")<< "CSCSegmentBuilder algorithm name: " << algoName;

    // SegAlgo parameter set
    std::vector<edm::ParameterSet> segAlgoPSet = algoPSets[chosenAlgo].getParameter<std::vector<edm::ParameterSet> >("algo_psets");

    // Chamber types to handle
    std::vector<std::string> chType = algoPSets[chosenAlgo].getParameter<std::vector<std::string> >("chamber_types");
    LogDebug("CSCSegment|CSC")<< "No. of chamber types to handle: " << chType.size();

    // Algo to chamber type 
    std::vector<int> algoToType = algoPSets[chosenAlgo].getParameter<std::vector<int> >("parameters_per_chamber_type");

    // Trap if we don't have enough parameter sets or haven't assigned an algo to every type   
    if (algoToType.size() !=  chType.size()) {
        throw cms::Exception("ParameterSetError") << 
	  "#dim algosToType=" << algoToType.size() << ", #dim chType=" << chType.size() << std::endl;
    }

    // Ask factory to build this algorithm, giving it appropriate ParameterSet
            
    for (size_t j=0; j<chType.size(); ++j) {
        algoMap[chType[j]] = CSCSegmentBuilderPluginFactory::get()->
                create(algoName, segAlgoPSet[algoToType[j]-1]);
	edm::LogVerbatim("CSCSegment|CSC")<< "using algorithm #" << algoToType[j] << " for chamber type " << chType[j];
    }

//    hitsFromStripOnly_     = new CSCHitFromStripOnly( ps );
//    hitsFromWireOnly_      = new CSCHitFromWireOnly( ps );

}

CSCSegmentBuilder::~CSCSegmentBuilder() {
  //
  // loop on algomap and delete them
  //
  for (std::map<std::string, CSCSegmentAlgorithm*>::iterator it = algoMap.begin();it != algoMap.end(); it++){
    delete ((*it).second);
  }

//  delete hitsFromStripOnly_;
//  delete hitsFromWireOnly_;

}



void CSCSegmentBuilder::build(const CSCWireDigiCollection* wiredc,
                              const CSCStripDigiCollection* stripdc, 
                              CSCSegmentCollection& oc) {
/*  	
    // make wire and strip hits
    std::vector<CSCWireHit> wireHits = MakeWireDigiHits(wiredc);
    std::vector<CSCStripHit> stripHits = MakeStripDigiHits(stripdc);

    LogDebug("CSCSegment|CSC")<< "Total number of wire hits in this event: " << wireHits.size();
    LogDebug("CSCSegment|CSC")<< "Total number of strip hits in this event: " << stripHits.size();

    // save chambers containng wire hits
    std::vector<CSCDetId> chambers;
    // save wire hits for each non-empty chamber
    std::vector<std::vector<CSCWireHit> > wHitsPerChamber;

    std::vector<CSCDetId>::const_iterator chIt;
    std::vector<CSCWireHit>::const_iterator wIt;
    std::vector<CSCStripHit>::const_iterator sIt;

    for(wIt = wireHits.begin(); wIt != wireHits.end(); wIt++) {
        
        bool insert = true;
        for(chIt=chambers.begin(); chIt != chambers.end(); ++chIt) 
            if (((*wIt).cscDetId().chamber() == (*chIt).chamber()) &&
                ((*wIt).cscDetId().station() == (*chIt).station()) &&
                ((*wIt).cscDetId().ring() == (*chIt).ring()) &&
                ((*wIt).cscDetId().endcap() == (*chIt).endcap())) {
    
                insert = false;
                wHitsPerChamber[chIt-chambers.begin()].push_back(*wIt);

            }
	
        if (insert) {

            chambers.push_back((*wIt).cscDetId().chamberId());
            std::vector<CSCWireHit> wHits_tmp; wHits_tmp.push_back(*wIt);
            wHitsPerChamber.push_back(wHits_tmp);

        }
    }

    LogDebug("CSCSegment|CSC")<< "Total number of chambers containing wire hits in this event: " << chambers.size();

    // loop over chambers containing wire hits, save strip hits in same chamber
    // if number of wire/strip hits per chamber is no smaller than 3, make segment for this chamber
    for(chIt=chambers.begin(); chIt != chambers.end(); ++chIt) {

       const CSCChamber* chamber = geom_->chamber(*chIt);

       std::vector<CSCWireHit> cscWireHits;
       std::vector<CSCStripHit> cscStripHits;

       for(sIt = stripHits.begin(); sIt != stripHits.end(); sIt++) 
          if (((*sIt).cscDetId().chamber() == (*chIt).chamber()) &&
               ((*sIt).cscDetId().station() == (*chIt).station()) &&
               ((*sIt).cscDetId().ring() == (*chIt).ring()) &&
               ((*sIt).cscDetId().endcap() == (*chIt).endcap()))
               cscStripHits.push_back(*sIt);
       
       if (int(cscStripHits.size()) < 3) continue;

       cscWireHits = wHitsPerChamber[chIt-chambers.begin()];

       if (int(cscWireHits.size()) < 3) continue;

       LogDebug("CSCSegment|CSC")<< "Start to make segment for chamber: " << *chIt;
       LogDebug("CSCSegment|CSC")<< "It has " << cscWireHits.size() << " wire hits and " << cscStripHits.size() << " strip hits";

//       std::vector<CSCSegment> segv = algoMap[chamber->specs()->chamberTypeName()]->run(chamber, cscWireHits, cscStripHits);

//       oc.put((*chIt), segv.begin(), segv.end());

    }
*/
}

/*
void CSCSegmentBuilder::build(const CSCRecHit2DCollection* recHits, 
                              const CSCWireDigiCollection* wiredc,
                              const CSCStripDigiCollection* stripdc, CSCSegmentCollection& oc) {

  	
  LogDebug("CSCSegment|CSC")<< "Total number of rechits in this event: " << recHits->size();

    std::vector<CSCDetId> chambers;
    std::vector<CSCDetId>::const_iterator chIt;
    
    for(CSCRecHit2DCollection::const_iterator it2 = recHits->begin(); it2 != recHits->end(); it2++) {
        
        bool insert = true;
        for(chIt=chambers.begin(); chIt != chambers.end(); ++chIt) 
            if (((*it2).cscDetId().chamber() == (*chIt).chamber()) &&
                ((*it2).cscDetId().station() == (*chIt).station()) &&
                ((*it2).cscDetId().ring() == (*chIt).ring()) &&
                ((*it2).cscDetId().endcap() == (*chIt).endcap()))
                insert = false;
	
        if (insert)
            chambers.push_back((*it2).cscDetId().chamberId());
    }

    for(chIt=chambers.begin(); chIt != chambers.end(); ++chIt) {

        std::vector<const CSCRecHit2D*> cscRecHits;
        const CSCChamber* chamber = geom_->chamber(*chIt);
        
        CSCRangeMapAccessor acc;
        CSCRecHit2DCollection::range range = recHits->get(acc.cscChamber(*chIt));
        
        std::vector<int> hitPerLayer(6);
        for(CSCRecHit2DCollection::const_iterator rechit = range.first; rechit != range.second; rechit++) {
            
            hitPerLayer[(*rechit).cscDetId().layer()-1]++;
            cscRecHits.push_back(&(*rechit));
        }    
        
        LogDebug("CSCSegment|CSC") << "found " << cscRecHits.size() << " rechits in chamber " << *chIt;
            
        // given the chamber select the appropriate algo... and run it
        std::vector<CSCSegment> segv = algoMap[chamber->specs()->chamberTypeName()]->run(chamber, cscRecHits);

        LogDebug("CSCSegment|CSC") << "found " << segv.size() << " segments in chamber " << *chIt;

        // Add the segments to master collection
        oc.put((*chIt), segv.begin(), segv.end());
    }
}
*/

void CSCSegmentBuilder::setGeometry(const CSCGeometry* geom) {
	geom_ = geom;
}

/*
std::vector<CSCWireHit> CSCSegmentBuilder::MakeWireDigiHits(const CSCWireDigiCollection* wiredc) {

  std::vector<CSCWireHit> cscWireHits;

  for ( CSCWireDigiCollection::DigiRangeIterator it = wiredc->begin(); it != wiredc->end(); ++it ){
    const CSCDetId& id = (*it).first;
    const CSCLayer* layer = getLayer( id );
//    const CSCWireDigiCollection::Range& rwired = (*it).second;
    
    // Skip if no wire digis in this layer
//    if ( rwired.second == rwired.first ) continue;

    const CSCDetId& sDetId = id;
 
    CSCDetId compId = sDetId;
    CSCWireDigiCollection::Range rwired = wiredc->get( sDetId );
    // Skip if no wire digis in this layer
    // But for ME11, real wire digis are labelled as belonging to ME1b, so that's where ME1a must look
    // (We try ME1a - above - anyway, because simulated wire digis are labelled as ME1a.)
    if ( rwired.second == rwired.first ) {
      if ( sDetId.station()!=1 || sDetId.ring()!=4 ){
        continue; // not ME1a, skip to next layer
      }
      // So if ME1a has no wire digis (always the case for data) make the
      // wire digi ID point to ME1b. This is what is compared to the
      // strip digi ID below (and not used anywhere else). 
      // Later, rechits use the strip digi ID for construction.
      
      // It is ME1a but no wire digis there, so try ME1b...
      int endcap  = sDetId.endcap();
      int chamber = sDetId.chamber();
      int layer   = sDetId.layer();
      CSCDetId idw( endcap, 1, 1, chamber, layer ); // Set idw to same layer in ME1b
      compId = idw;
      rwired = wiredc->get( compId );
    }
 
    // Fill bad channel bitsets for this layer
    // this has been done twice, for wire and strip, is it a potential issue ? 
    recoConditions_->fillBadChannelWords( id );
    
    // Build wire hits for this layer
    std::vector<CSCWireHit> const & wireHitsPerLayer = hitsFromWireOnly_->runWire(compId, layer, rwired);

    if (wireHitsPerLayer.empty()) continue;

    //hits_in_layer = 0;
   
    LogTrace("CSCSegment|CSC")<< "[CSCSegmentBuilder] found " << wireHitsPerLayer.size() << " wire hits in layer " << sDetId;

    cscWireHits.insert(cscWireHits.end(), wireHitsPerLayer.begin(), wireHitsPerLayer.end() );
    
  }

  return cscWireHits;

}


std::vector<CSCStripHit> CSCSegmentBuilder::MakeStripDigiHits(const CSCStripDigiCollection* stripdc) {

  std::vector<CSCStripHit> cscStripHits;

  for ( CSCStripDigiCollection::DigiRangeIterator it = stripdc->begin(); it != stripdc->end(); ++it ){

    const CSCDetId& id = (*it).first;
    const CSCLayer* layer = getLayer( id );
    const CSCStripDigiCollection::Range& rstripd = (*it).second;
    
    // Skip if no strip digis in this layer
    if ( rstripd.second == rstripd.first ) continue;

    const CSCDetId& sDetId = id;
 
    // Fill bad channel bitsets for this layer
    recoConditions_->fillBadChannelWords( id );
    
    // Build strip hits for this layer
    std::vector<CSCStripHit> const & stripHitsPerLayer = hitsFromStripOnly_->runStrip( id, layer, rstripd);

    if (stripHitsPerLayer.empty()) continue;

    //hits_in_layer = 0;
   
    LogTrace("CSCSegment|CSC")<< "[CSCSegmentBuilder] found " << stripHitsPerLayer.size() << " strip hits in layer " << sDetId;
    
    cscStripHits.insert(cscStripHits.end(), stripHitsPerLayer.begin(), stripHitsPerLayer.end() );

  }

  return cscStripHits;

}

void CSCSegmentBuilder::setConditions( CSCRecoConditions* reco ) {
  recoConditions_ = reco;
  hitsFromStripOnly_->setConditions( reco );
  hitsFromWireOnly_->setConditions( reco );
}
*/
const CSCLayer* CSCSegmentBuilder::getLayer( const CSCDetId& detId )  {
  return geom_->layer(detId);
}

