/**
 * \file CSCSegAlgRU.cc
 *
 * \authors V.Palichik & N.Voytishin
 * \some functions and structure taken from SK algo by M.Sani and SegFit class by T.Cox
 */

#include "CSCSegAlgoUF.h"
#include "CSCSegFit.h"
#include "CSCStripSegmentPattern.h"
#include "Geometry/CSCGeometry/interface/CSCLayer.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
//#include "TMatrixDSparse.h"
#include "RecoLocalMuon/CSCRecHitD/src/CSCMake2DRecHit.h"
#include "RecoLocalMuon/CSCRecHitD/src/CSCXonStrip_MatchGatti.h"
#include "RecoLocalMuon/CSCRecHitD/src/CSCFindPeakTime.h"
#include "RecoLocalMuon/CSCRecHitD/src/CSCRecoConditions.h"
//#include "RecoLocalMuon/CSCRecHitD/src/HardCodedCorrectionInitialization.cc"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"


CSCSegAlgoUF::CSCSegAlgoUF(const edm::ParameterSet& ps)
  : CSCSegmentAlgorithm(ps), myName("CSCSegAlgoUF"), sfit_(nullptr) {
  doCollisions = ps.getParameter<bool>("doCollisions");
  chi2_str_ = ps.getParameter<double>("chi2_str");
  chi2Norm_2D_ = ps.getParameter<double>("chi2Norm_2D_");
  dRMax = ps.getParameter<double>("dRMax");
  dPhiMax = ps.getParameter<double>("dPhiMax");
  dRIntMax = ps.getParameter<double>("dRIntMax");
  dPhiIntMax = ps.getParameter<double>("dPhiIntMax");
  chi2Max = ps.getParameter<double>("chi2Max");
  wideSeg = ps.getParameter<double>("wideSeg");
  minLayersApart = ps.getParameter<int>("minLayersApart");

  LogDebug("CSC") << myName << " has algorithm cuts set to: \n"
		  << "--------------------------------------------------------------------\n"
		  << "dRMax = " << dRMax << '\n'
		  << "dPhiMax = " << dPhiMax << '\n'
		  << "dRIntMax = " << dRIntMax << '\n'
		  << "dPhiIntMax = " << dPhiIntMax << '\n'
		  << "chi2Max = " << chi2Max << '\n'
		  << "wideSeg = " << wideSeg << '\n'
		  << "minLayersApart = " << minLayersApart << std::endl;

  //reset the thresholds for non-collision data
  if(!doCollisions){
    dRMax = 2.0;
    dPhiMax = 2*dPhiMax;
    dRIntMax = 2*dRIntMax;
    dPhiIntMax = 2*dPhiIntMax;
    chi2Norm_2D_ = 5*chi2Norm_2D_;
    chi2_str_ = 100;
    chi2Max = 2*chi2Max;
  }

  make2DHits_ = new CSCMake2DRecHit( ps );

}


CSCSegAlgoUF::~CSCSegAlgoUF() {
  delete make2DHits_;

}


void CSCSegAlgoUF::setConditions( CSCRecoConditions* reco ) {
  recoConditions_ = reco;
  make2DHits_->setConditions( reco );
}


std::vector<CSCSegment> CSCSegAlgoUF::run(const CSCChamber* aChamber, const ChamberHitContainer& rechits,
                                                                      const ChamberWireHitContainer& wirehits,
                                                                      const ChamberStripHitContainer& striphits,
                                                                      CSCRecoConditions* reco){
 setConditions(reco);
  
  theChamber = aChamber;
//  std::cout << theChamber->id() << std::endl;
  // get number of wire groups and strips for this chamber
  nWireGroups = theChamber->layer(1)->geometry()->numberOfWireGroups();
  nStrips = theChamber->layer(1)->geometry()->numberOfStrips();
  //std::cout << "This chamber has " << nWireGroups << " wire groups and " << nStrips << " strips " << std::endl;
  int theStation = theChamber->id().station();
  int theRing = theChamber->id().ring();
  if (theStation==1 && (theRing == 1 || theRing==4) )
     {isME11 = true;}
  else {isME11 = false;}

  return buildSegments(wirehits,striphits);
  //return buildSegments(rechits);

}


std::vector<CSCSegment> CSCSegAlgoUF::buildSegments(const ChamberWireHitContainer& uwirehits,
                                                    const ChamberStripHitContainer& ustriphits) {

  std::vector<CSCSegment> segments;

  int e = theChamber->id().endcap();
  int s = theChamber->id().station();
  int r = theChamber->id().ring();
  int c = theChamber->id().chamber();
  if (!(e == 1 && s == 1 && r == 4 && c == 17)) return segments;

  ChamberWireHitContainer wirehits = uwirehits;
  ChamberStripHitContainer striphits = ustriphits;

  TH2F* wHitsPerChamber = new TH2F("wHitsPerChamber","",nWireGroups,0,nWireGroups,6,0,6);
  TH2F* sHitsPerChamber = new TH2F("sHitsPerChamber","",2*nStrips+1,0,2*nStrips+1,6,0,6); // half strip stagger at 1,3,5 layer

  FillWireMatrix(wHitsPerChamber, wirehits); TH2F* wHitsPerChamber_c = (TH2F*)wHitsPerChamber->Clone("wHitsPerChamber_c");
  FillStripMatrix(sHitsPerChamber, striphits); TH2F* sHitsPerChamber_c = (TH2F*)sHitsPerChamber->Clone("sHitsPerChamber_c");

//  WriteTH2F(wHitsPerChamber);
//  WriteTH2F(sHitsPerChamber);

  std::list<CSCWireSegment> wireSegs;
  ScanForWireSeg(wHitsPerChamber, wireSegs, 6, false);
  ScanForWireSeg(wHitsPerChamber, wireSegs, 5, false);
  ScanForWireSeg(wHitsPerChamber, wireSegs, 4, false);
  ScanForWireSeg(wHitsPerChamber, wireSegs, 3, false);

  std::list<CSCStripSegment> stripSegs;
  ScanForStripSeg(sHitsPerChamber, stripSegs, 6);
  ScanForStripSeg(sHitsPerChamber, stripSegs, 5);
  ScanForStripSeg(sHitsPerChamber, stripSegs, 4);
  ScanForStripSeg(sHitsPerChamber, stripSegs, 3);

/*

if (int(stripSegs.size()) == 1) {

   std::cout << "keyHalfStrip: " << stripSegs.begin()->keyHalfStrip() <<
                ", nLayersWithHits: " << stripSegs.begin()->nLayersWithHits() <<
                ", patternRank: " << stripSegs.begin()->patternRank() << std::endl;
   }
if (int(wireSegs.size()) == 1) {

   std::cout << "keyWG: " << wireSegs.begin()->keyWG() << ", nLayersWithHits: " << wireSegs.begin()->nLayersWithHits() << std::endl;

   }
*/

  std::cout << theChamber->id() <<  ", nWireSegments: " << wireSegs.size() << 
                                    ", nStripSegments: " << stripSegs.size() << 
                                    ", nSegments: " << wireSegs.size() * stripSegs.size() << std::endl;

     WriteTH2F(wHitsPerChamber_c);
     WriteTH2F(sHitsPerChamber_c);

//std::cout<<std::endl;

/*
  if (int(wireSegs.size()) == 2 && abs(wireSegs.begin()->keyWG()-std::next(wireSegs.begin(),1)->keyWG()) == 1) {
     WriteTH2F(wHitsPerChamber_c);
     WriteTH2F(sHitsPerChamber_c);

  ScanForWireSeg(wHitsPerChamber_c, wireSegs, 6, true);
  ScanForWireSeg(wHitsPerChamber_c, wireSegs, 5, true);
  ScanForWireSeg(wHitsPerChamber_c, wireSegs, 4, true);
  ScanForWireSeg(wHitsPerChamber_c, wireSegs, 3, true);

     std::cout << "keyWG diff: " << abs(wireSegs.begin()->keyWG()-std::next(wireSegs.begin(),1)->keyWG()) << " wg" << std::endl;

     std::cout << std::endl;
     }
*/

//if (int(wireSegs.size()) == 0) {std::cout << "no wire seg" << std::endl; WriteTH2F(wHitsPerChamber);}
//if (int(stripSegs.size()) == 0) {std::cout << "no strip seg" << std::endl; WriteTH2F(sHitsPerChamber);}

/*
  std::cout << "NO. wire seg: "  << wHitsFromWSegs.size() << std::endl;
  for (int i = 0; i < int(wHitsFromWSegs.size()); i++) std::cout << int(wHitsFromWSegs[i].size()) << " wHits from " << i+1 << " th wSeg" << std::endl;
  std::cout << std::endl;
  std::cout << "NO. strip seg: "  << sHitsFromSSegs.size() << std::endl;
  for (int i = 0; i < int(sHitsFromSSegs.size()); i++) std::cout << int(sHitsFromSSegs[i].size()) << " sHits from " << i+1 << " th sSeg" << std::endl;
*/


  for (auto wIt = wireSegs.begin(); wIt != wireSegs.end(); wIt++) {
      for (auto sIt = stripSegs.begin(); sIt != stripSegs.end(); sIt++) {

          CSCWireSegment wireSeg = *wIt;
          CSCStripSegment stripSeg = *sIt;
//std::cout << "keyWG: " << wIt->keyWG() << ", nLayer: " << wIt->nLayersWithHits() << std::endl;
//std::cout << "keyHS: " << sIt->keyHalfStrip() << ", nLayer: " << sIt->nLayersWithHits() << std::endl;

          int wHitsFromWSeg[6] = {}; GetWireHitFromWireSeg(wireSeg, wirehits, wHitsFromWSeg);
          int sHitsFromSSeg[6] = {}; GetStripHitFromStripSeg(stripSeg, striphits, sHitsFromSSeg);
          std::vector<CSCRecHit2D> csc2DRecHits;
          for (int k = 0; k < 6; k++) {
              if (wHitsFromWSeg[k] == -1 || sHitsFromSSeg[k] == -1) continue;
              const CSCWireHit* cscwirehit = wirehits[wHitsFromWSeg[k]]; 
              const CSCStripHit* cscstriphit = striphits[sHitsFromSSeg[k]];

              const CSCWireHit& wirehit = *cscwirehit;
              const CSCStripHit& striphit = *cscstriphit;
              const CSCDetId& detId = CSCDetId(theChamber->id().endcap(),
                                               theChamber->id().station(),
                                               theChamber->id().ring(),
                                               theChamber->id().chamber(), k+1);

              const CSCLayer* cscLayer = theChamber->layer(k+1);
std::cout << "wire pos: " << cscwirehit->wHitPos() << ", strip pos: " << cscstriphit->sHitPos() << std::endl;

              CSCRecHit2D rechit = make2DHits_->hitFromStripAndWire(detId, cscLayer, wirehit, striphit );
std::cout << rechit << std::endl;
              csc2DRecHits.push_back(rechit);
              }

              ChamberHitContainer csc2DRecHits_p;
              for (std::vector<CSCRecHit2D>::const_iterator it = csc2DRecHits.begin(); it != csc2DRecHits.end(); it++)
                  { csc2DRecHits_p.push_back(&(*it)); }

              std::unique_ptr<CSCSegFit> oldfit;
              oldfit.reset(new CSCSegFit( theChamber, csc2DRecHits_p ));
              oldfit->fit();

              sfit_ = std::move(oldfit);
              if (int(sfit_->hits().size()) < 3 ) continue; // why number of hits is 0 ??? or smaller than3, wire and strip hit not found ???
              CSCSegment temp(sfit_->hits(), sfit_->intercept(),
                              sfit_->localdir(), sfit_->covarianceMatrix(), sfit_->chi2());

              sfit_ = 0;

              // do prune
              // this function return segment , inside function decide update or not
              if (temp.chi2() < 1e-4) {
                 segments.push_back(temp);
                 } else {
                        tempSeg = doPrune(csc2DRecHits_p, temp);
                        segments.push_back(tempSeg);
                        }

//std::cout << temp << std::endl;
              }
            }

  std::cout << "return " << segments.size() << " 2D segments" << std::endl;
  std::cout << std::endl;

  return segments;

}


void CSCSegAlgoUF::WriteTH2F(TH2F* hist) {
     for (int i = 1; i < hist->GetNbinsY()+1; i++) {
         for (int j = 1; j < hist->GetNbinsX()+1; j++) {

             if (hist->GetBinContent(j,i)==0)
                {std::cout << "-";} else {std::cout << 1;}

             }
         std::cout << std::endl;
         }

//     std::cout << std::endl;

}


void CSCSegAlgoUF::FillWireMatrix(TH2F* whitsMatrix, ChamberWireHitContainer whits) {
     std::vector<double> rows_v; std::vector<double> cols_v; std::vector<double> data_v;
     for (unsigned int i = 0; i < whits.size(); i++) {
         const CSCWireHit* whit = whits[i];
         int wLayer = whit->cscDetId().layer();
         for (unsigned int j = 0; j < whit->wgroups().size(); j++) {
             int wg = (whit->wgroups())[j]; cols_v.push_back(wg-1);
             int wgTimeBinOn = (whit->timeBinsOn())[j]; data_v.push_back(wgTimeBinOn);
             rows_v.push_back(wLayer-1);
         }
     }
     double* rows_a = &rows_v[0]; double* cols_a = &cols_v[0]; double* data_a = &data_v[0];
     whitsMatrix->FillN(int(rows_v.size()), cols_a, rows_a, data_a);     
}



void CSCSegAlgoUF::FillStripMatrix(TH2F* shitsMatrix, ChamberStripHitContainer shits) {

     std::vector<double> rows_v; std::vector<double> cols_v; std::vector<double> data_v;
     for (unsigned int i = 0; i < shits.size(); i++) {
         const CSCStripHit* shit = shits[i];
         int sLayer = shit->cscDetId().layer();
         //std::cout << "shit->strips.size(): "  << shit->strips().size() << ", shit->s_adc().size(): " << shit->s_adc().size() << std::endl;
         // strip hits contain either 1 or 3 strips: see makeCluster method from RecoLocalMuon/CSCRecHitD/src/CSCHitFromStripOnly.cc
std::cout << "layer: " << sLayer << ", sHitPos:  " << shit->sHitPos() << std::endl;
std::cout << "layer: " << sLayer << ", strip cluster size:  " << shit->strips().size() << std::endl;
         if (int(shit->strips().size()) == 1) {

            int sp = (shit->strips())[0];
            if (isME11 || (!isME11 && (sLayer == 2 || sLayer == 4 || sLayer == 6) ) ){
               cols_v.push_back(2*sp-2); //cols_v.push_back(2*sp-1);
               }
            if (!isME11 && (sLayer == 1 || sLayer == 3 || sLayer == 5) ) {
               cols_v.push_back(2*sp-1); //cols_v.push_back(2*sp);
               }

            rows_v.push_back(sLayer-1); //rows_v.push_back(sLayer-1);
            data_v.push_back(1); //data_v.push_back(1);

            }

         if (int(shit->strips().size()) == 3) {

            int sp = (shit->strips())[1];            
            double leftC = (shit->s_adc())[shit->tmax()]; double rightC = (shit->s_adc())[shit->tmax()+8]; 
            // above line ugly hardcode, can be improved!
            // reason is for each strip hit, 4 time bins of adc for 3 strips in one strip cluster are saved: CSCHitFromStripOnly.cc
            rows_v.push_back(sLayer-1); data_v.push_back(1);
            if (isME11 || (!isME11 && (sLayer == 2 || sLayer == 4 || sLayer == 6) ) ) {
               leftC >= rightC ? cols_v.push_back(2*sp-2) : cols_v.push_back(2*sp-1);
               }
            if (!isME11 && (sLayer == 1 || sLayer == 3 || sLayer == 5) ) {
               leftC >= rightC ? cols_v.push_back(2*sp-1) : cols_v.push_back(2*sp);
               } 

            }
     }
     double* rows_a = &rows_v[0]; double* cols_a = &cols_v[0]; double* data_a = &data_v[0];
     shitsMatrix->FillN(int(rows_v.size()), cols_a, rows_a, data_a);
}


void CSCSegAlgoUF::ScanForWireSeg(TH2F* wHitsPerChamber, std::list<CSCWireSegment>& wireSegs, int nLayer, bool debug) {

     double w_rows_1[14] = {0,0,0,1,1,2,3,3,4,4,4,5,5,5};
     double w_rows_2[14] = {5,5,5,4,4,3,2,2,1,1,1,0,0,0};
     double w_cols[14] = {-2,-1,0,-1,0,0,0,1,0,1,2,0,1,2};
     double w_data[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};

     for (int i = 0; i < nWireGroups; i++) {

         double w_cols_scan[14] = {};
         int thisKeyWG = nWireGroups-i;

         for (int j = 0; j < 14; j++) w_cols_scan[j] = w_cols[j] + thisKeyWG - 1; // scan from wide end of chamber

             TH2F* wirePattern = new TH2F("wirePattern","",nWireGroups,0,nWireGroups,6,0,6);
             int station = theChamber->id().station();
             if (station == 1 || station == 2 ) wirePattern->FillN(14,w_cols_scan,w_rows_1,w_data);
             if (station == 3 || station == 4) wirePattern->FillN(14,w_cols_scan,w_rows_2,w_data);
//if (i == 10) {std::cout << "wPattern: " << std::endl;WriteTH2F(wirePattern);std::cout << std::endl;}
             wirePattern->Multiply(wHitsPerChamber); // scan is done here
             TH1D* hitsLayer = wirePattern->ProjectionY();
             hitsLayer->Divide(hitsLayer);
             int thisNLayer = hitsLayer->Integral();// find layers with w hits 

             if (thisNLayer != nLayer) {delete wirePattern; continue;} // 3 or 4 is hardcoded

             if (int(wireSegs.size()) == 0 ) {
//std::cout << "wPattern: " << std::endl; WriteTH2F(wirePattern);
//std::cout << std::endl;
                wireSegs.push_back( CSCWireSegment(thisKeyWG, thisNLayer, wirePattern) );
                wHitsPerChamber->Add(wirePattern,-1); 
                delete wirePattern; continue;
                }

             CSCWireSegment lastSeg = wireSegs.back();
             int lastKeyWG =  lastSeg.keyWG();
//std::cout << "wPattern: " << std::endl; WriteTH2F(wirePattern);
//std::cout << std::endl;
             CSCWireSegment tmpWireSeg = CSCWireSegment(thisKeyWG, thisNLayer, wirePattern);
             if (abs(lastKeyWG-thisKeyWG) > 1) wireSegs.push_back(tmpWireSeg);
             if (abs(lastKeyWG-thisKeyWG) == 1) {
                wireSegs.back().updateWHits(tmpWireSeg.wireHits(), tmpWireSeg.nLayerHits());

                }

//             wireSegs.push_back( CSCWireSegment(thisKeyWG, thisNLayer, wirePattern) );
if (debug) {

   std::cout << theChamber->id() << std::endl;
   std::cout << "n layer = " << nLayer << std::endl; 
   std::cout << "before:" << std::endl; WriteTH2F(wHitsPerChamber);
}
             wHitsPerChamber->Add(wirePattern,-1); // delete wire group being used
//std::cout << "after:" << std::endl; WriteTH2F(wHitsPerChamber);
             delete wirePattern; 

//               }
/*
            CSCWireSegment lastSeg = wireSegs.back();
            int lastKeyWG =  lastSeg.keyWG();
            int lastNLayer = lastSeg.nLayersWithHits();

            if (thisKeyWG - lastKeyWG < -1) {
               wireSegs.push_back( CSCWireSegment(thisKeyWG, thisNLayer, wirePattern) );

               } else if ((thisKeyWG - lastKeyWG == -1) && (thisNLayer > lastNLayer) ) {
                         wireSegs.pop_back();
                         wireSegs.push_back( CSCWireSegment(thisKeyWG, thisNLayer, wirePattern) );

                         }


*/
         }


}


void CSCSegAlgoUF::ScanForStripSeg(TH2F* sHitsPerChamber, std::list<CSCStripSegment>& stripSegs, int nLayer) {

     TH1D* nonEmptyStrip = sHitsPerChamber->ProjectionX();
     for (int i = 0; i < nStrips*2+1; i++) {

         if (nonEmptyStrip->GetBinContent(i+1) == 0 && // only scan non empty area, what about under/over flow ? need to check !
             nonEmptyStrip->GetBinContent(i) == 0 && nonEmptyStrip->GetBinContent(i+2) == 0 ) continue; 
         for (int j = 0; j < 9; j++) {// scan patterns sequentially, according to ranks
                                   // scan from high rank (high pt) patterns to low pt patterns
             int nhalfStrips = nHalfStrips[j]; 
             int thisKeyHalfStrip = i+1; 
             int thisRank = patternRanks[j];
             double s_cols_scan[nhalfStrips] = {}; 
             if (isME11) {
                for (int k = 0; k < nhalfStrips; k++) s_cols_scan[k] = s_cols[j][k] + thisKeyHalfStrip -1;
                } else {
                       for (int k = 0; k < nhalfStrips; k++) s_cols_scan[k] = s_cols[j][k] + thisKeyHalfStrip ;
                       }

             TH2F* stripPattern = new TH2F("stripPattern","",nStrips*2+1,0,nStrips*2+1,6,0,6);
             stripPattern->FillN(nhalfStrips,s_cols_scan,s_rows[j],s_data[j]); 
//if (i == 10) {std::cout << "sPattern: " << std::endl; WriteTH2F(stripPattern);std::cout << std::endl;}
             stripPattern->Multiply(sHitsPerChamber); // scan is done here

             TH1D* hitsLayer = stripPattern->ProjectionY();
             hitsLayer->Divide(hitsLayer); 
             int thisNLayer = hitsLayer->Integral(); // find layers with s hits

             if (thisNLayer != nLayer) { delete stripPattern; continue; } // 3 or 4 is hardcode

//             stripSegs.push_back( CSCStripSegment(thisKeyHalfStrip,thisNLayer,thisRank,stripPattern) );
//             sHitsPerChamber->Add(stripPattern,-1); // delete wire group being used

             if (int(stripSegs.size()) == 0 ) {
//std::cout << "sPattern: " << std::endl; WriteTH2F(stripPattern);
//std::cout << std::endl;
                stripSegs.push_back( CSCStripSegment(thisKeyHalfStrip,thisNLayer,thisRank,stripPattern) ); 
                sHitsPerChamber->Add(stripPattern,-1);
                delete stripPattern; continue;
                }

             CSCStripSegment lastSeg = stripSegs.back();
             int lastKeyHalfStrip = lastSeg.keyHalfStrip();
//std::cout << "sPattern: " << std::endl; WriteTH2F(stripPattern);
//std::cout << std::endl;

             CSCStripSegment tmpStripSeg = CSCStripSegment(thisKeyHalfStrip,thisNLayer,thisRank,stripPattern);
             if (abs(thisKeyHalfStrip - lastKeyHalfStrip) > 1) stripSegs.push_back(tmpStripSeg);
             if (abs(thisKeyHalfStrip - lastKeyHalfStrip) == 1) {
                stripSegs.back().updateSHits(tmpStripSeg.stripHits(), tmpStripSeg.nLayerHits());

                }

             sHitsPerChamber->Add(stripPattern,-1); // delete wire group being used
             delete stripPattern;

/*
          CSCStripSegment lastSeg = stripSegs.back();
          int lastKeyHalfStrip = lastSeg.keyHalfStrip();
          int lastNLayer = lastSeg.nLayersWithHits();
          int lastRank = lastSeg.patternRank();

          if (thisKeyHalfStrip - lastKeyHalfStrip > 2) {
             stripSegs.push_back( CSCStripSegment(thisKeyHalfStrip,thisNLayer,thisRank,stripPattern) );
           
             }

          else if (thisNLayer > lastNLayer) {
                  stripSegs.pop_back();
                  stripSegs.push_back( CSCStripSegment(thisKeyHalfStrip,thisNLayer,thisRank,stripPattern) );    

                  }
          
          else if ((thisNLayer == lastNLayer) && (thisRank < lastRank) ) {
                  stripSegs.pop_back();
                  stripSegs.push_back( CSCStripSegment(thisKeyHalfStrip,thisNLayer,thisRank,stripPattern) );

                  }

          delete stripPattern;

*/
             }
         }


}



void CSCSegAlgoUF::GetWireHitFromWireSeg(CSCWireSegment wireSeg, ChamberWireHitContainer whits, int* wireHitIndex) {

  double keyWH = wireSeg.keyWG();
  double wgLow = wireSeg.comHitLow();
  double wgHigh = wireSeg.comHitHigh();
std::cout << "keyWH: " << keyWH << std::endl;
std::cout << "low: " << wgLow << ", high: " << wgHigh << std::endl;

  for (int i = 0; i < 6; i++) { // loop over 6 layers
      double wHitPos = (wireSeg.wireHits())[i];
      int wHitIndex = -999;
      double wPosDiff = 113; //112 is max one can get
std::cout << "wpos: " << wHitPos << std::endl;
      bool hitMissed = false;
      for (int j = 0; j < int(whits.size()); j++) {
          const CSCWireHit* tmpHit = whits[j];
          int wHitLayer = tmpHit->cscDetId().layer();
          double wHitPos2 = tmpHit->wHitPos();
if (i==0) std::cout << "wHitPos2: " << wHitPos2 << std::endl;
          if (wHitLayer != (i+1) ) continue;

          if (wHitPos == 0 && abs(keyWH-wHitPos2) <= 2 && (wHitPos2 >= wgLow) && (wHitPos2 <= wgHigh) ) {
std::cout << "here: " << wHitPos2 << std::endl;
             wHitIndex = j; hitMissed=true; break;

             }       
          if (abs(wHitPos-wHitPos2) < wPosDiff) {
             wPosDiff = abs(wHitPos-wHitPos2);
             wHitIndex = j;

             }
          }

      if ((wPosDiff < 113 && wHitPos >= 1) || (wHitPos==0&&hitMissed)) { // if pattern doesn't cover some hit, and is close, to keyWH, include it
         wireHitIndex[i] = wHitIndex;

         } else {
                wireHitIndex[i] = -1;
                }

      }


}


void CSCSegAlgoUF::GetStripHitFromStripSeg(CSCStripSegment stripSeg, ChamberStripHitContainer shits, int* stripHitIndex) {

  double keySH = ceil(stripSeg.keyHalfStrip()/2.0);
std::cout << "keySH: " << keySH << std::endl;
  double comHitLow = stripSeg.comHitLow(isME11);
  double comHitHigh = stripSeg.comHitHigh(isME11);
std::cout << "low: " << comHitLow << ", high: " << comHitHigh << std::endl;
  for (int i = 0; i < 6; i++) {
      double sHitPos_ = (stripSeg.stripHits())[i]; // comparator position in unit of half strip
      double sHitPos = -1;  // strip hit position in unit of strip
std::cout << "sHitPos_: " << sHitPos_ << std::endl;
 
      if (!isME11 && (i==0||i==2||i==4) ) sHitPos = ceil((sHitPos_-1)/2.0); // convert comparator number to strip number
      if (isME11 || (!isME11 && (i==1||i==3||i==5) ) ) sHitPos = ceil(sHitPos_/2.0);
      if (sHitPos_==1 || sHitPos_==2) sHitPos = 1;

      int sHitIndex = -999;
      double sPosDiff = 81;
      bool hitMissed = false;
std::cout << "sHitPos: " << sHitPos << std::endl;
      for (int j = 0; j < int(shits.size()); j++) {
          const CSCStripHit* tmpHit = shits[j];
          int sHitLayer = tmpHit->cscDetId().layer();
          double sHitPos2 = tmpHit->sHitPos();
if (i==0) std::cout << "sHitPos2: " << sHitPos2 << std::endl;

          if ((i+1) != sHitLayer) continue;

          if (sHitPos == 0 && abs(keySH-sHitPos2)<2 && ((2*sHitPos2-1) >= comHitLow-1.5) && (2*sHitPos2 <= comHitHigh+1.5) ) {
             sHitIndex = j; hitMissed = true; break;
             }

          if (abs(sHitPos-sHitPos2) < sPosDiff) {
             sPosDiff = abs(sHitPos-sHitPos2);
             sHitIndex = j;

             }
          }


      if ((sPosDiff < 81 && sHitPos >= 1) || (sHitPos==0&&hitMissed) ) {  // this line needs some simplification ! this is really ugly ...
         stripHitIndex[i] = sHitIndex;
std::cout << "layer:" << i+1 << ", sHitIndex: " << sHitIndex << std::endl;

         } else {
                stripHitIndex[i] = -1;
                }

      }

}



CSCSegment CSCSegAlgoUF::doPrune(ChamberHitContainer rechits, CSCSegment oldSeg)
{

  const int nHits = int(rechits.size());
  CSCSegment segAfterPrune[nHits] = {};
  bool updateSeg = false;
  int newSegIndex = -1;
  double chi2Improvement = 1;
  double oldChi2Prob = ChiSquaredProbability( oldSeg.chi2(), oldSeg.degreesOfFreedom() );

  for (int i = 0; i < nHits; i++) {

      ChamberHitContainer tmpRHs(nHits);
      std::copy(rechits.begin(),rechits.end(),tmpRHs);
      tmpRHs.erase(tmpRHs.begin()+i);

      CSCSegment temp;

      std::unique_ptr<CSCSegFit> oldfit;
      oldfit.reset(new CSCSegFit( theChamber, csc2DRecHits_p ));
      oldfit->fit();

      CSCSegment temp(oldfit->hits(), oldfit->intercept(),
                      oldfit->localdir(), oldfit->covarianceMatrix(), oldfit->chi2());

      oldfit = 0;

      double newChi2Prob = ChiSquaredProbability( temp.chi2(), temp.degreesOfFreedom() );
      if (newChi2Prob < 1e-10) continue;
      if (newChi2Prob/oldChi2Prob < 1e4) continue;

      if (newChi2Prob/oldChi2Prob > chi2Improvement) {
         updateSeg = true;
         segAfterPrune[i] = temp;
         chi2Improvement = newChi2Prob/oldChi2Prob;
         newSegIndex = i;

         }

      }

  if (!updateSeg) {

     return oldSeg;

     } else {

            return segAfterPrune[newSegIndex];

            }

}


// ----------------  RU ALGO ------------------

std::vector<CSCSegment> CSCSegAlgoUF::buildSegments(const ChamberHitContainer& urechits) {
  ChamberHitContainer rechits = urechits;
  LayerIndex layerIndex(rechits.size());
  int recHits_per_layer[6] = {0,0,0,0,0,0};
  //skip events with high multiplicity of hits
  if (rechits.size()>150){
    return std::vector<CSCSegment>();
  }
  int iadd = 0;
  for(unsigned int i = 0; i < rechits.size(); i++) {
    recHits_per_layer[rechits[i]->cscDetId().layer()-1]++;//count rh per chamber
    layerIndex[i] = rechits[i]->cscDetId().layer();
  }
  double z1 = theChamber->layer(1)->position().z();
  double z6 = theChamber->layer(6)->position().z();
  if (std::abs(z1) > std::abs(z6)){
    reverse(layerIndex.begin(), layerIndex.end());
    reverse(rechits.begin(), rechits.end());
  }
  if (rechits.size() < 2) {
    return std::vector<CSCSegment>();
  }
  // We have at least 2 hits. We intend to try all possible pairs of hits to start
  // segment building. 'All possible' means each hit lies on different layers in the chamber.
  // after all same size segs are build we get rid of the overcrossed segments using the chi2 criteria
  // the hits from the segs that are left are marked as used and are not added to segs in future iterations
  // the hits from 3p segs are marked as used separately in order to try to assamble them in longer segments
  // in case there is a second pass
  // Choose first hit (as close to IP as possible) h1 and second hit
  // (as far from IP as possible) h2 To do this we iterate over hits
  // in the chamber by layer - pick two layers. Then we
  // iterate over hits within each of these layers and pick h1 and h2
  // these. If they are 'close enough' we build an empty
  // segment. Then try adding hits to this segment.
  // Initialize flags that a given hit has been allocated to a segment
  BoolContainer used(rechits.size(), false);
  BoolContainer used3p(rechits.size(), false);
  // This is going to point to fits to hits, and its content will be used to create a CSCSegment
  sfit_ = 0;
  // Define buffer for segments we build
  std::vector<CSCSegment> segments;
  ChamberHitContainerCIt ib = rechits.begin();
  ChamberHitContainerCIt ie = rechits.end();
  // Possibly allow 3 passes, second widening scale factor for cuts, third for segments from displaced vertices
  windowScale = 1.; // scale factor for cuts
  bool search_disp = false;
  strip_iadd = 1;
  chi2D_iadd = 1;
  int npass = (wideSeg > 1.)? 3 : 2;
  for (int ipass = 0; ipass < npass; ++ipass) {
    if(windowScale >1.){
      iadd = 1;
      strip_iadd = 2;
      chi2D_iadd = 2;
    }
    int used_rh = 0;
    for (ChamberHitContainerCIt i1 = ib; i1 != ie; ++i1) {
      if(used[i1-ib])used_rh++;
    }

    //change the tresholds if it's time to look for displaced mu segments
    if(doCollisions && search_disp && int(rechits.size()-used_rh)>2){//check if there are enough recHits left to build a segment from displaced vertices
      doCollisions = false;
      windowScale = 1.; // scale factor for cuts
      dRMax = 2.0;
      dPhiMax = 2*dPhiMax;
      dRIntMax = 2*dRIntMax;
      dPhiIntMax = 2*dPhiIntMax;
      chi2Norm_2D_ = 5*chi2Norm_2D_;
      chi2_str_ = 100;
      chi2Max = 2*chi2Max;
    }else{
      search_disp = false;//make sure the flag is off
    }

    for(unsigned int n_seg_min = 6u; n_seg_min > 2u + iadd; --n_seg_min){
      BoolContainer common_used(rechits.size(),false);
      std::array<BoolContainer, 120> common_used_it = {};
      for (unsigned int i = 0; i < common_used_it.size(); i++) {
	common_used_it[i] = common_used;
      }
      ChamberHitContainer best_proto_segment[120];
      float min_chi[120] = {9999};
      int common_it = 0;
      bool first_proto_segment = true;
      for (ChamberHitContainerCIt i1 = ib; i1 != ie; ++i1) {
	bool segok = false;
	//skip if rh is used and the layer tat has big rh multiplicity(>25RHs)
	if(used[i1-ib] || recHits_per_layer[int(layerIndex[i1-ib])-1]>25 || (n_seg_min == 3 && used3p[i1-ib])) continue;
	int layer1 = layerIndex[i1-ib];
	const CSCRecHit2D* h1 = *i1;
	for (ChamberHitContainerCIt i2 = ie-1; i2 != i1; --i2) {
	  if(used[i2-ib] || recHits_per_layer[int(layerIndex[i2-ib])-1]>25 || (n_seg_min == 3 && used3p[i2-ib])) continue;
	  int layer2 = layerIndex[i2-ib];
	  if((abs(layer2 - layer1) + 1) < int(n_seg_min)) break;//decrease n_seg_min
	  const CSCRecHit2D* h2 = *i2;
	  if (areHitsCloseInR(h1, h2) && areHitsCloseInGlobalPhi(h1, h2)) {
	    proto_segment.clear();
	    if (!addHit(h1, layer1))continue;
	    if (!addHit(h2, layer2))continue;
	    // Can only add hits if already have a segment
	    if ( sfit_ )tryAddingHitsToSegment(rechits, used, layerIndex, i1, i2);
	    segok = isSegmentGood(rechits);
	    if (segok) {
	      if(proto_segment.size() > n_seg_min){
		baseline(n_seg_min);
		updateParameters();
	      }
	      if(sfit_->chi2() > chi2Norm_2D_*chi2D_iadd || proto_segment.size() < n_seg_min) proto_segment.clear();
	      if (!proto_segment.empty()) {
		updateParameters();
		//add same-size overcrossed protosegments to the collection
		if(first_proto_segment){
		  flagHitsAsUsed(rechits, common_used_it[0]);
		  min_chi[0] = sfit_->chi2();
		  best_proto_segment[0] = proto_segment;
		  first_proto_segment = false;
		}else{ //for the rest of found proto_segments
		  common_it++;
		  flagHitsAsUsed(rechits, common_used_it[common_it]);
		  min_chi[common_it] = sfit_->chi2();
		  best_proto_segment[common_it] = proto_segment;
		  ChamberHitContainerCIt hi, iu, ik;
		  int iter = common_it;
		  for(iu = ib; iu != ie; ++iu) {
		    for(hi = proto_segment.begin(); hi != proto_segment.end(); ++hi) {
		      if(*hi == *iu) {
			int merge_nr = -1;
			for(int k = 0; k < iter+1; k++){
			  if(common_used_it[k][iu-ib] == true){
			    if(merge_nr != -1){
			      //merge the k and merge_nr collections of flaged hits into the merge_nr collection and unmark the k collection hits
			      for(ik = ib; ik != ie; ++ik) {
				if(common_used_it[k][ik-ib] == true){
				  common_used_it[merge_nr][ik-ib] = true;
				  common_used_it[k][ik-ib] = false;
				}
			      }
			      //change best_protoseg if min_chi_2 is smaller
			      if(min_chi[k] < min_chi[merge_nr]){
				min_chi[merge_nr] = min_chi[k];
				best_proto_segment[merge_nr] = best_proto_segment[k];
				best_proto_segment[k].clear();
				min_chi[k] = 9999;
			      }
			      common_it--;
			    }
			    else{
			      merge_nr = k;
			    }
			  }//if(common_used[k][iu-ib] == true)
			}//for k
		      }//if
		    }//for proto_seg
		  }//for rec_hits
		}//else
	      }//proto seg not empty
	    }
	  } // h1 & h2 close
	  if (segok)
	    break;
	} // i2
      } // i1


      //add the reconstructed segments
      for(int j = 0;j < common_it+1; j++){
	proto_segment = best_proto_segment[j];
	best_proto_segment[j].clear();
	//SKIP empty proto-segments
	if(proto_segment.size() == 0) continue;
	updateParameters();
	// Create an actual CSCSegment - retrieve all info from the fit
	CSCSegment temp(sfit_->hits(), sfit_->intercept(),
			sfit_->localdir(), sfit_->covarianceMatrix(), sfit_->chi2());
	sfit_ = 0;
	segments.push_back(temp);
	//if the segment has 3 hits flag them as used in a particular way
	if(proto_segment.size() == 3){
	  flagHitsAsUsed(rechits, used3p);
	}
	else{
	  flagHitsAsUsed(rechits, used);
	}
	proto_segment.clear();
      }
    }//for n_seg_min

    if(search_disp){
      //reset params and flags for the next chamber
      search_disp = false;
      doCollisions = true;
      dRMax = 2.0;
      dPhiMax = dPhiMax/2;
      dRIntMax = dRIntMax/2;
      dPhiIntMax = dPhiIntMax/2;
      chi2Norm_2D_ = chi2Norm_2D_/5;
      chi2_str_ = 100;
      chi2Max = chi2Max/2;
    }

    std::vector<CSCSegment>::iterator it =segments.begin();
    bool good_segs = false;
    while(it != segments.end()) {
      if ((*it).nRecHits() > 3){
	good_segs = true;
	break;
      }
      ++it;
    }
    if (good_segs && doCollisions) { // only change window if not enough good segments were found (bool can be changed to int if a >0 number of good segs is required)
      search_disp = true;
      continue;//proceed to search the segs from displaced vertices
    }

    // Increase cut windows by factor of wideSeg only for collisions
    if(!doCollisions && !search_disp) break;
    windowScale = wideSeg;
  } // ipass

  //get rid of enchansed 3p segments
  std::vector<CSCSegment>::iterator it =segments.begin();
  while(it != segments.end()) {
    if((*it).nRecHits() == 3){
      bool found_common = false;
      const std::vector<CSCRecHit2D>& theseRH = (*it).specificRecHits();
      for (ChamberHitContainerCIt i1 = ib; i1 != ie; ++i1) {
	if(used[i1-ib] && used3p[i1-ib]){
	  const CSCRecHit2D* sh1 = *i1;
	  CSCDetId id = sh1->cscDetId();
	  int sh1layer = id.layer();
	  int RH_centerid = sh1->nStrips()/2;
	  int RH_centerStrip = sh1->channels(RH_centerid);
	  int RH_wg = sh1->hitWire();
	  std::vector<CSCRecHit2D>::const_iterator sh;
	  for(sh = theseRH.begin(); sh != theseRH.end(); ++sh){
	    CSCDetId idRH = sh->cscDetId();
	    //find segment hit coord
	    int shlayer = idRH.layer();
	    int SegRH_centerid = sh->nStrips()/2;
	    int SegRH_centerStrip = sh->channels(SegRH_centerid);
	    int SegRH_wg = sh->hitWire();
	    if(sh1layer == shlayer && SegRH_centerStrip == RH_centerStrip && SegRH_wg == RH_wg){
	      //remove the enchansed 3p segment
	      segments.erase(it,(it+1));
	      found_common = true;
	      break;
	    }
	  }//theserh
	}
	if(found_common) break;//current seg has already been erased
      }//camber hits
      if(!found_common)++it;
    }//its a 3p seg
    else{
      ++it;//go to the next seg
    }
  }//while
  // Give the segments to the CSCChamber
  return segments;
}//build segments

void CSCSegAlgoUF::tryAddingHitsToSegment(const ChamberHitContainer& rechits,
					  const BoolContainer& used, const LayerIndex& layerIndex,
					  const ChamberHitContainerCIt i1, const ChamberHitContainerCIt i2) {
  // Iterate over the layers with hits in the chamber
  // Skip the layers containing the segment endpoints
  // Test each hit on the other layers to see if it is near the segment
  // If it is, see whether there is already a hit on the segment from the same layer
  // - if so, and there are more than 2 hits on the segment, copy the segment,
  // replace the old hit with the new hit. If the new segment chi2 is better
  // then replace the original segment with the new one (by swap)
  // - if not, copy the segment, add the hit. If the new chi2/dof is still satisfactory
  // then replace the original segment with the new one (by swap)
  ChamberHitContainerCIt ib = rechits.begin();
  ChamberHitContainerCIt ie = rechits.end();
  for (ChamberHitContainerCIt i = ib; i != ie; ++i) {
    int layer = layerIndex[i-ib];
    if (hasHitOnLayer(layer) && proto_segment.size() <= 2)continue;  
    if (layerIndex[i-ib] == layerIndex[i1-ib] || layerIndex[i-ib] == layerIndex[i2-ib] || used[i-ib])continue;
    
    const CSCRecHit2D* h = *i;
    if (isHitNearSegment(h)) {
      // Don't consider alternate hits on layers holding the two starting points
      if (hasHitOnLayer(layer)) {
	if (proto_segment.size() <= 2)continue;
	compareProtoSegment(h, layer);
      }
      else{
	increaseProtoSegment(h, layer, chi2D_iadd);
      }
    } // h & seg close
  } // i
}

bool CSCSegAlgoUF::areHitsCloseInR(const CSCRecHit2D* h1, const CSCRecHit2D* h2) const {
  float maxWG_width[10] = {0, 0, 4.1, 5.69, 2.49, 5.06, 2.49, 5.06, 1.87, 5.06};
  CSCDetId id = h1->cscDetId();
  int iStn = id.iChamberType()-1;
  //find maxWG_width for ME11 (tilt = 29deg)
  int wg_num = h2->hitWire();
  if(iStn == 0 || iStn == 1){
    if (wg_num == 1){
      maxWG_width[0] = 9.25;
      maxWG_width[1] = 9.25;
    }
    if (wg_num > 1 && wg_num < 48){
      maxWG_width[0] = 3.14;
      maxWG_width[1] = 3.14;
    }
    if (wg_num == 48){
      maxWG_width[0] = 10.75;
      maxWG_width[1] = 10.75;
    }
  }
  const CSCLayer* l1 = theChamber->layer(h1->cscDetId().layer());
  GlobalPoint gp1 = l1->toGlobal(h1->localPosition());
  const CSCLayer* l2 = theChamber->layer(h2->cscDetId().layer());
  GlobalPoint gp2 = l2->toGlobal(h2->localPosition());
  //find z to understand the direction
  float h1z = gp1.z();
  float h2z = gp2.z();
  //switch off the IP check for non collisions case
  if (!doCollisions){
    h1z = 1;
    h2z = 1;
  }
  if (gp2.perp() > ((gp1.perp() - dRMax*maxWG_width[iStn])*h2z)/h1z && gp2.perp() < ((gp1.perp() + dRMax*maxWG_width[iStn])*h2z)/h1z){
    return true;
  }
  else{
    return false;
  }
}

bool CSCSegAlgoUF::areHitsCloseInGlobalPhi(const CSCRecHit2D* h1, const CSCRecHit2D* h2) const {
  float strip_width[10] = {0.003878509, 0.002958185, 0.002327105, 0.00152552, 0.00465421, 0.002327105, 0.00465421, 0.002327105, 0.00465421, 0.002327105};//in rad
  const CSCLayer* l1 = theChamber->layer(h1->cscDetId().layer());
  GlobalPoint gp1 = l1->toGlobal(h1->localPosition());
  const CSCLayer* l2 = theChamber->layer(h2->cscDetId().layer());
  GlobalPoint gp2 = l2->toGlobal(h2->localPosition());
  float err_stpos_h1 = h1->errorWithinStrip();
  float err_stpos_h2 = h2->errorWithinStrip();
  CSCDetId id = h1->cscDetId();
  int iStn = id.iChamberType()-1;
  float dphi_incr = 0;
  if(err_stpos_h1>0.25*strip_width[iStn] || err_stpos_h2>0.25*strip_width[iStn])dphi_incr = 0.5*strip_width[iStn];
  float dphi12 = deltaPhi(gp1.barePhi(),gp2.barePhi());
  return (fabs(dphi12) < (dPhiMax*strip_iadd+dphi_incr))? true:false; // +v
}

bool CSCSegAlgoUF::isHitNearSegment(const CSCRecHit2D* h) const {
  // Is hit near segment?
  // Requires deltaphi and deltaR within ranges specified in parameter set.
  // Note that to make intuitive cuts on delta(phi) one must work in
  // phi range (-pi, +pi] not [0, 2pi)
  float strip_width[10] = {0.003878509, 0.002958185, 0.002327105, 0.00152552, 0.00465421, 0.002327105, 0.00465421, 0.002327105, 0.00465421, 0.002327105};//in rad
  const CSCLayer* l1 = theChamber->layer((*(proto_segment.begin()))->cscDetId().layer());
  GlobalPoint gp1 = l1->toGlobal((*(proto_segment.begin()))->localPosition());
  const CSCLayer* l2 = theChamber->layer((*(proto_segment.begin()+1))->cscDetId().layer());
  GlobalPoint gp2 = l2->toGlobal((*(proto_segment.begin()+1))->localPosition());
  float err_stpos_h1 = (*(proto_segment.begin()))->errorWithinStrip();
  float err_stpos_h2 = (*(proto_segment.begin()+1))->errorWithinStrip();
  const CSCLayer* l = theChamber->layer(h->cscDetId().layer());
  GlobalPoint hp = l->toGlobal(h->localPosition());
  float err_stpos_h = h->errorWithinStrip();
  float hphi = hp.phi(); // in (-pi, +pi]
  if (hphi < 0.)
    hphi += 2.*M_PI; // into range [0, 2pi)
  float sphi = phiAtZ(hp.z()); // in [0, 2*pi)
  float phidif = sphi-hphi;
  if (phidif < 0.)
    phidif += 2.*M_PI; // into range [0, 2pi)
  if (phidif > M_PI)
    phidif -= 2.*M_PI; // into range (-pi, pi]
  SVector6 r_glob;
  CSCDetId id = h->cscDetId();
  int iStn = id.iChamberType()-1;
  float dphi_incr = 0;
  float pos_str = 1;
  //increase dPhi cut if the hit is on the edge of the strip
  float stpos = (*h).positionWithinStrip();
  bool centr_str = false;
  if(iStn != 0 && iStn != 1){
    if (stpos > -0.25 && stpos < 0.25) centr_str = true;
  }
  if(err_stpos_h1<0.25*strip_width[iStn] || err_stpos_h2<0.25*strip_width[iStn] || err_stpos_h < 0.25*strip_width[iStn]){
    dphi_incr = 0.5*strip_width[iStn];
  }else{
    if(centr_str) pos_str = 1.3;
  }
  r_glob((*(proto_segment.begin()))->cscDetId().layer()-1) = gp1.perp();
  r_glob((*(proto_segment.begin()+1))->cscDetId().layer()-1) = gp2.perp();
  float R = hp.perp();
  int layer = h->cscDetId().layer();
  float r_interpolated = fit_r_phi(r_glob,layer);
  float dr = fabs(r_interpolated - R);
  float maxWG_width[10] = {0, 0, 4.1, 5.69, 2.49, 5.06, 2.49, 5.06, 1.87, 5.06};
  //find maxWG_width for ME11 (tilt = 29deg)
  int wg_num = h->hitWire();
  if(iStn == 0 || iStn == 1){
    if (wg_num == 1){
      maxWG_width[0] = 9.25;
      maxWG_width[1] = 9.25;
    }
    if (wg_num > 1 && wg_num < 48){
      maxWG_width[0] = 3.14;
      maxWG_width[1] = 3.14;
    }
    if (wg_num == 48){
      maxWG_width[0] = 10.75;
      maxWG_width[1] = 10.75;
    }
  }
  return (fabs(phidif) < dPhiIntMax*strip_iadd*pos_str+dphi_incr && fabs(dr) < dRIntMax*maxWG_width[iStn])? true:false;
}

float CSCSegAlgoUF::phiAtZ(float z) const {
  if ( !sfit_ ) return 0.;
  // Returns a phi in [ 0, 2*pi )
  const CSCLayer* l1 = theChamber->layer((*(proto_segment.begin()))->cscDetId().layer());
  GlobalPoint gp = l1->toGlobal(sfit_->intercept());
  GlobalVector gv = l1->toGlobal(sfit_->localdir());
  float x = gp.x() + (gv.x()/gv.z())*(z - gp.z());
  float y = gp.y() + (gv.y()/gv.z())*(z - gp.z());
  float phi = atan2(y, x);
  if (phi < 0.f ) phi += 2. * M_PI;
  return phi ;
}

bool CSCSegAlgoUF::isSegmentGood(const ChamberHitContainer& rechitsInChamber) const {
  // If the chamber has 20 hits or fewer, require at least 3 hits on segment
  // If the chamber has >20 hits require at least 4 hits
  //@@ THESE VALUES SHOULD BECOME PARAMETERS?
  bool ok = false;
  unsigned int iadd = ( rechitsInChamber.size() > 20)? 1 : 0;
  if (windowScale > 1.)
    iadd = 1;
  if (proto_segment.size() >= 3+iadd)
    ok = true;
  return ok;
}

void CSCSegAlgoUF::flagHitsAsUsed(const ChamberHitContainer& rechitsInChamber,
				  BoolContainer& used ) const {
  // Flag hits on segment as used
  ChamberHitContainerCIt ib = rechitsInChamber.begin();
  ChamberHitContainerCIt hi, iu;
  for(hi = proto_segment.begin(); hi != proto_segment.end(); ++hi) {
    for(iu = ib; iu != rechitsInChamber.end(); ++iu) {
      if(*hi == *iu)
	used[iu-ib] = true;
    }
  }
}

bool CSCSegAlgoUF::addHit(const CSCRecHit2D* aHit, int layer) {
  // Return true if hit was added successfully
  // (and then parameters are updated).
  // Return false if there is already a hit on the same layer, or insert failed.
  ChamberHitContainer::const_iterator it;
  for(it = proto_segment.begin(); it != proto_segment.end(); it++)
    if (((*it)->cscDetId().layer() == layer) && (aHit != (*it)))
      return false;
  proto_segment.push_back(aHit);
  // make a fit
  updateParameters();
  return true;
}

void CSCSegAlgoUF::updateParameters() {
  // Delete input CSCSegFit, create a new one and make the fit
  // delete sfit_;
  sfit_.reset(new CSCSegFit( theChamber, proto_segment ));
  sfit_->fit();
}

float CSCSegAlgoUF::fit_r_phi(SVector6 points, int layer) const{
  //find R or Phi on the given layer using the given points for the interpolation
  float Sx = 0;
  float Sy = 0;
  float Sxx = 0;
  float Sxy = 0;
  for (int i=1;i<7;i++){
    if (points(i-1)== 0.) continue;
    Sy = Sy + (points(i-1));
    Sx = Sx + i;
    Sxx = Sxx + (i*i);
    Sxy = Sxy + ((i)*points(i-1));
  }
  float delta = 2*Sxx - Sx*Sx;
  float intercept = (Sxx*Sy - Sx*Sxy)/delta;
  float slope = (2*Sxy - Sx*Sy)/delta;
  return (intercept + slope*layer);
}

void CSCSegAlgoUF::baseline(int n_seg_min){
  int nhits = proto_segment.size();
  ChamberHitContainer::const_iterator iRH_worst;
  //initialise vectors for strip position and error within strip
  SVector6 sp;
  SVector6 se;
  unsigned int init_size = proto_segment.size();
  ChamberHitContainer buffer;
  buffer.clear();
  buffer.reserve(init_size);
  while (buffer.size()< init_size){
    ChamberHitContainer::iterator min;
    int min_layer = 10;
    for(ChamberHitContainer::iterator k = proto_segment.begin(); k != proto_segment.end(); k++){
      const CSCRecHit2D* iRHk = *k;
      CSCDetId idRHk = iRHk->cscDetId();
      int kLayer = idRHk.layer();
      if(kLayer < min_layer){
	min_layer = kLayer;
	min = k;
      }
    }
    buffer.push_back(*min);
    proto_segment.erase(min);
  }//while

  proto_segment.clear();
  for (ChamberHitContainer::const_iterator cand = buffer.begin(); cand != buffer.end(); cand++) {
    proto_segment.push_back(*cand);
  }

  for(ChamberHitContainer::const_iterator iRH = proto_segment.begin(); iRH != proto_segment.end(); iRH++){
    const CSCRecHit2D* iRHp = *iRH;
    CSCDetId idRH = iRHp->cscDetId();
    int kRing = idRH.ring();
    int kStation = idRH.station();
    int kLayer = idRH.layer();
    // Find the strip containing this hit
    int centerid = iRHp->nStrips()/2;
    int centerStrip = iRHp->channels(centerid);
    float stpos = (*iRHp).positionWithinStrip();
    se(kLayer-1) = (*iRHp).errorWithinStrip();
    // Take into account half-strip staggering of layers (ME1/1 has no staggering)
    if (kStation == 1 && (kRing == 1 || kRing == 4)) sp(kLayer-1) = stpos + centerStrip;
    else{
      if (kLayer == 1 || kLayer == 3 || kLayer == 5) sp(kLayer-1) = stpos + centerStrip;
      if (kLayer == 2 || kLayer == 4 || kLayer == 6) sp(kLayer-1) = stpos - 0.5 + centerStrip;
    }
  }
  float chi2_str;
  fitX(sp, se, -1, -1, chi2_str);

  //-----------------------------------------------------
  // Optimal point rejection method
  //-----------------------------------------------------
  float minSum = 1000;
  int i1b = 0;
  int i2b = 0;
  int iworst = -1;
  int bad_layer = -1;
  ChamberHitContainer::const_iterator rh_to_be_deleted_1;
  ChamberHitContainer::const_iterator rh_to_be_deleted_2;
  if ( (chi2_str) > chi2_str_*chi2D_iadd){///(nhits-2)
    for (ChamberHitContainer::const_iterator i1 = proto_segment.begin(); i1 != proto_segment.end();++i1) {
      ++i1b;
      const CSCRecHit2D* i1_1 = *i1;
      CSCDetId idRH1 = i1_1->cscDetId();
      int z1 = idRH1.layer();
      i2b = i1b;
      for (ChamberHitContainer::const_iterator i2 = i1+1; i2 != proto_segment.end(); ++i2) {
	++i2b;
	const CSCRecHit2D* i2_1 = *i2;
	CSCDetId idRH2 = i2_1->cscDetId();
	int z2 = idRH2.layer();
	int irej = 0;
	for ( ChamberHitContainer::const_iterator ir = proto_segment.begin(); ir != proto_segment.end(); ++ir) {
	  ++irej;
	  if (ir == i1 || ir == i2) continue;
	  float dsum = 0;
	  int hit_nr = 0;
	  const CSCRecHit2D* ir_1 = *ir;
	  CSCDetId idRH = ir_1->cscDetId();
	  int worst_layer = idRH.layer();
	  for (ChamberHitContainer::const_iterator i = proto_segment.begin(); i != proto_segment.end(); ++i) {
	    ++hit_nr;
	    const CSCRecHit2D* i_1 = *i;
	    if (i == i1 || i == i2 || i == ir) continue;
	    float slope = (sp(z2-1)-sp(z1-1))/(z2-z1);
	    float intersept = sp(z1-1) - slope*z1;
	    CSCDetId idRH = i_1->cscDetId();
	    int z = idRH.layer();
	    float di = fabs(sp(z-1) - intersept - slope*z);
	    dsum = dsum + di;
	  }//i
	  if (dsum < minSum){
	    minSum = dsum;
	    bad_layer = worst_layer;
	    iworst = irej;
	    rh_to_be_deleted_1 = ir;
	  }
	}//ir
      }//i2
    }//i1
    fitX(sp, se, bad_layer, -1, chi2_str);
  }//if chi2prob<1.0e-4

  //find worst from n-1 hits
  int iworst2 = -1;
  int bad_layer2 = -1;
  if (iworst > -1 && (nhits-1) > n_seg_min && (chi2_str) > chi2_str_*chi2D_iadd){///(nhits-3)
    iworst = -1;
    float minSum = 1000;
    int i1b = 0;
    int i2b = 0;
    for (ChamberHitContainer::const_iterator i1 = proto_segment.begin(); i1 != proto_segment.end();++i1) {
      ++i1b;
      const CSCRecHit2D* i1_1 = *i1;
      CSCDetId idRH1 = i1_1->cscDetId();
      int z1 = idRH1.layer();
      i2b = i1b;
      for ( ChamberHitContainer::const_iterator i2 = i1+1; i2 != proto_segment.end(); ++i2) {
	++i2b;
	const CSCRecHit2D* i2_1 = *i2;
	CSCDetId idRH2 = i2_1->cscDetId();
	int z2 = idRH2.layer();
	int irej = 0;
	for ( ChamberHitContainer::const_iterator ir = proto_segment.begin(); ir != proto_segment.end(); ++ir) {
	  ++irej;
	  int irej2 = 0;
	  if (ir == i1 || ir == i2 ) continue;
	  const CSCRecHit2D* ir_1 = *ir;
	  CSCDetId idRH = ir_1->cscDetId();
	  int worst_layer = idRH.layer();
	  for ( ChamberHitContainer::const_iterator ir2 = proto_segment.begin(); ir2 != proto_segment.end(); ++ir2) {
	    ++irej2;
	    if (ir2 == i1 || ir2 == i2 || ir2 ==ir ) continue;
	    float dsum = 0;
	    int hit_nr = 0;
	    const CSCRecHit2D* ir2_1 = *ir2;
	    CSCDetId idRH = ir2_1->cscDetId();
	    int worst_layer2 = idRH.layer();
	    for ( ChamberHitContainer::const_iterator i = proto_segment.begin(); i != proto_segment.end(); ++i) {
	      ++hit_nr;
	      const CSCRecHit2D* i_1 = *i;
	      if (i == i1 || i == i2 || i == ir|| i == ir2 ) continue;
	      float slope = (sp(z2-1)-sp(z1-1))/(z2-z1);
	      float intersept = sp(z1-1) - slope*z1;
	      CSCDetId idRH = i_1->cscDetId();
	      int z = idRH.layer();
	      float di = fabs(sp(z-1) - intersept - slope*z);
	      dsum = dsum + di;
	    }//i
	    if (dsum < minSum){
	      minSum = dsum;
	      iworst2 = irej2;
	      iworst = irej;
	      bad_layer = worst_layer;
	      bad_layer2 = worst_layer2;
	      rh_to_be_deleted_1 = ir;
	      rh_to_be_deleted_2 = ir2;
	    }
	  }//ir2
	}//ir
      }//i2
    }//i1
    fitX(sp, se, bad_layer ,bad_layer2, chi2_str);
  }//if prob(n-1)<e-4

  //----------------------------------
  //erase bad_hits
  //----------------------------------
  if( iworst2-1 >= 0 && iworst2 <= int(proto_segment.size()) ) {
    proto_segment.erase( rh_to_be_deleted_2);
  }
  if( iworst-1 >= 0 && iworst <= int(proto_segment.size()) ){
    proto_segment.erase(rh_to_be_deleted_1);
  }
}

float CSCSegAlgoUF::fitX(SVector6 points, SVector6 errors, int ir, int ir2, float &chi2_str){
  float S = 0;
  float Sx = 0;
  float Sy = 0;
  float Sxx = 0;
  float Sxy = 0;
  float sigma2 = 0;
  for (int i=1;i<7;i++){
    if (i == ir || i == ir2 || points(i-1) == 0.) continue;
    sigma2 = errors(i-1)*errors(i-1);
    float i1 = i - 3.5;
    S = S + (1/sigma2);
    Sy = Sy + (points(i-1)/sigma2);
    Sx = Sx + ((i1)/sigma2);
    Sxx = Sxx + (i1*i1)/sigma2;
    Sxy = Sxy + (((i1)*points(i-1))/sigma2);
  }
  float delta = S*Sxx - Sx*Sx;
  float intercept = (Sxx*Sy - Sx*Sxy)/delta;
  float slope = (S*Sxy - Sx*Sy)/delta;
  float chi_str = 0;
  chi2_str = 0;
  // calculate chi2_str
  for (int i=1;i<7;i++){
    if (i == ir || i == ir2 || points(i-1) == 0.) continue;
    chi_str = (points(i-1) - intercept - slope*(i-3.5))/(errors(i-1));
    chi2_str = chi2_str + chi_str*chi_str;
  }
  return (intercept + slope*0);
}

bool CSCSegAlgoUF::hasHitOnLayer(int layer) const {
  // Is there is already a hit on this layer?
  ChamberHitContainerCIt it;
  for(it = proto_segment.begin(); it != proto_segment.end(); it++)
    if ((*it)->cscDetId().layer() == layer)
      return true;
  return false;
}

bool CSCSegAlgoUF::replaceHit(const CSCRecHit2D* h, int layer) {
  // replace a hit from a layer
  ChamberHitContainer::const_iterator it;
  for (it = proto_segment.begin(); it != proto_segment.end();) {
    if ((*it)->cscDetId().layer() == layer)
      it = proto_segment.erase(it);
    else
      ++it;
  }
  return addHit(h, layer);
}

void CSCSegAlgoUF::compareProtoSegment(const CSCRecHit2D* h, int layer) {
  // Copy the input CSCSegFit
  std::unique_ptr<CSCSegFit> oldfit;
  oldfit.reset(new CSCSegFit( theChamber, proto_segment ));
  oldfit->fit();
  ChamberHitContainer oldproto = proto_segment;
  
  // May create a new fit
  bool ok = replaceHit(h, layer);
  if ( (sfit_->chi2() >= oldfit->chi2() ) || !ok ) {
    // keep original fit
    proto_segment = oldproto;
    sfit_ = std::move(oldfit); // reset to the original input fit
  }
}

void CSCSegAlgoUF::increaseProtoSegment(const CSCRecHit2D* h, int layer, int chi2_factor) {
  // Creates a new fit
  std::unique_ptr<CSCSegFit> oldfit;
  ChamberHitContainer oldproto = proto_segment;
  oldfit.reset(new CSCSegFit( theChamber, proto_segment ));
  oldfit->fit();

  bool ok = addHit(h, layer);
  //@@ TEST ON ndof<=0 IS JUST TO ACCEPT nhits=2 CASE??
  if ( !ok || ( (sfit_->ndof() > 0) && (sfit_->chi2()/sfit_->ndof() >= chi2Max)) ) {
    // reset to original fit
    proto_segment = oldproto;
    sfit_ = std::move(oldfit);
  }
}
