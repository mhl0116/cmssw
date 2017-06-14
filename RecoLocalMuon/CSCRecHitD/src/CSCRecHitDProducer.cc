#include <RecoLocalMuon/CSCRecHitD/src/CSCRecHitDProducer.h>
#include <RecoLocalMuon/CSCRecHitD/src/CSCRecHitDBuilder.h>
#include <RecoLocalMuon/CSCRecHitD/src/CSCRecoConditions.h>

#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDProducer.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/MakerMacros.h>
#include <DataFormats/Common/interface/Handle.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <FWCore/Utilities/interface/Exception.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h>

#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include <DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCWireHitCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCStripHitCollection.h>


CSCRecHitDProducer::CSCRecHitDProducer( const edm::ParameterSet& ps ) : 
  iRun( 0 ),   
  useCalib( ps.getParameter<bool>("CSCUseCalibrations") ),
  useStaticPedestals( ps.getParameter<bool>("CSCUseStaticPedestals") ),
  useTimingCorrections(ps.getParameter<bool>("CSCUseTimingCorrections") ),
  useGasGainCorrections(ps.getParameter<bool>("CSCUseGasGainCorrections") )

{
  s_token = consumes<CSCStripDigiCollection>( ps.getParameter<edm::InputTag>("stripDigiTag") );
  w_token = consumes<CSCWireDigiCollection>( ps.getParameter<edm::InputTag>("wireDigiTag") );

  recHitBuilder_     = new CSCRecHitDBuilder( ps ); // pass on the parameter sets
  recoConditions_    = new CSCRecoConditions( ps ); // access to conditions data

  recHitBuilder_->setConditions( recoConditions_ ); // pass down to who needs access

  // register what this produces
  produces<CSCRecHit2DCollection>();
  produces<CSCWireHitCollection>();
  produces<CSCStripHitCollection>();


}

CSCRecHitDProducer::~CSCRecHitDProducer()
{
  delete recHitBuilder_;
  delete recoConditions_;
}


void  CSCRecHitDProducer::produce( edm::Event& ev, const edm::EventSetup& setup )
{
  // Dumps the message TWICE if both categories are set!
  //  LogTrace("CSCRecHitDProducer|CSCRecHit")<< "[CSCRecHitDProducer] starting event " << ev.id().event() << " of run " << ev.id().run();
  LogTrace("CSCRecHit")<< "[CSCRecHitDProducer] starting event " << ev.id().event() << " of run " << ev.id().run();
  // find the geometry for this event & cache it in the builder
  edm::ESHandle<CSCGeometry> h;
  setup.get<MuonGeometryRecord>().get( h );
  const CSCGeometry* pgeom = &*h;
  recHitBuilder_->setGeometry( pgeom );

  // access conditions data for this event 
  if ( useCalib || useStaticPedestals || useTimingCorrections || useGasGainCorrections) {  
    recoConditions_->initializeEvent( setup ); 
  }
	
  // Get the collections of strip & wire digis from event
  edm::Handle<CSCStripDigiCollection> stripDigis;
  edm::Handle<CSCWireDigiCollection> wireDigis;

  ev.getByToken( s_token, stripDigis);
  ev.getByToken( w_token, wireDigis);

  // Create empty collection of rechits  
  auto oc = std::make_unique<CSCRecHit2DCollection>();
  auto oc_w = std::make_unique<CSCWireHitCollection>();
  auto oc_s = std::make_unique<CSCStripHitCollection>();

  // Fill the CSCRecHit2DCollection
  recHitBuilder_->build( stripDigis.product(), wireDigis.product(), *oc, *oc_w, *oc_s);

  // Put collection in event
  LogTrace("CSCRecHit")<< "[CSCRecHitDProducer] putting collection of " << oc->size() << " rechits into event.";
  LogTrace("CSCRecHit")<< "[CSCRecHitDProducer] putting collection of " << oc_w->size() << " wire hits into event.";
  LogTrace("CSCRecHit")<< "[CSCRecHitDProducer] putting collection of " << oc_s->size() << " strip hits into event.";
  std::cout << "[CSCRecHitDProducer] putting collection of " << oc->size() << " rechits into event." << std::endl;
  std::cout << "[CSCRecHitDProducer] putting collection of " << oc_w->size() << " wire hits into event." << std::endl;
  std::cout << "[CSCRecHitDProducer] putting collection of " << oc_s->size() << " strip hits into event." << std::endl;
  std::cout << std::endl;

  ev.put(std::move(oc));
  ev.put(std::move(oc_w));
  ev.put(std::move(oc_s));

}

void CSCRecHitDProducer::fillDescriptions(edm::ConfigurationDescriptions & descriptions) {
   edm::ParameterSetDescription desc;
   desc.add<double>("CSCStripPeakThreshold",10.0);
   desc.add<double>("CSCStripClusterChargeCut",25.0);
   desc.add<double>("CSCStripxtalksOffset",0.03);
   desc.add<bool>("UseAverageTime",false);
   desc.add<bool>("UseParabolaFit",false);
   desc.add<bool>("UseFivePoleFit",true);
   desc.add<int>("CSCWireClusterDeltaT",1);
   desc.add<bool>("CSCUseCalibrations",true);
   desc.add<bool>("CSCUseStaticPedestals",false);
   desc.add<int>("CSCNoOfTimeBinsForDynamicPedestal",2);
   desc.add<edm::InputTag>("wireDigiTag",edm::InputTag("muonCSCDigis","MuonCSCWireDigi"));
   desc.add<edm::InputTag>("stripDigiTag",edm::InputTag("muonCSCDigis","MuonCSCStripDigi"));
   desc.add<bool>("readBadChannels",true);
   desc.add<bool>("readBadChambers",true);
   desc.add<bool>("CSCUseTimingCorrections",true);
   desc.add<bool>("CSCUseGasGainCorrections",true);
   desc.addUntracked<bool>("CSCDebug",false);
   desc.add<int>("CSCstripWireDeltaTime",8);
   desc.addUntracked<int>("CSCStripClusterSize",3); 

   desc.add<double>("XTasymmetry_ME1a",0.023),
   desc.add<double>("XTasymmetry_ME1b",0.01),
   desc.add<double>("XTasymmetry_ME12",0.015),
   desc.add<double>("XTasymmetry_ME13",0.02),
   desc.add<double>("XTasymmetry_ME21",0.023),
   desc.add<double>("XTasymmetry_ME22",0.023),
   desc.add<double>("XTasymmetry_ME31",0.023),
   desc.add<double>("XTasymmetry_ME32",0.023),
   desc.add<double>("XTasymmetry_ME41",0.023),
   desc.add<double>("ConstSyst_ME1a",0.01),
   desc.add<double>("ConstSyst_ME1b",0.02),
   desc.add<double>("ConstSyst_ME12",0.02),
   desc.add<double>("ConstSyst_ME13",0.03),
   desc.add<double>("ConstSyst_ME21",0.03),
   desc.add<double>("ConstSyst_ME22",0.03),
   desc.add<double>("ConstSyst_ME31",0.03),
   desc.add<double>("ConstSyst_ME32",0.03),
   desc.add<double>("ConstSyst_ME41",0.03),
   desc.add<double>("NoiseLevel_ME1a",9.0),
   desc.add<double>("NoiseLevel_ME1b",6.0),
   desc.add<double>("NoiseLevel_ME12",7.0),
   desc.add<double>("NoiseLevel_ME13",4.0),
   desc.add<double>("NoiseLevel_ME21",5.0),
   desc.add<double>("NoiseLevel_ME22",7.0),
   desc.add<double>("NoiseLevel_ME31",5.0),
   desc.add<double>("NoiseLevel_ME32",7.0),
   desc.add<double>("NoiseLevel_ME41",5.0);

   desc.add<bool>("CSCUseReducedWireTimeWindow", false);
   desc.add<int>("CSCWireTimeWindowLow", 0);
   desc.add<int>("CSCWireTimeWindowHigh", 15);
   descriptions.add("configWireTimeWindow", desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CSCRecHitDProducer);

