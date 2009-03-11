#ifndef RecoEgamma_EgammaPhotonProducers_ConvertedPhotonProducer_h
#define RecoEgamma_EgammaPhotonProducers_ConvertedPhotonProducer_h
/** \class ConvertedPhotonProducer
 **  
 **
 **  $Id: ConvertedPhotonProducer.h,v 1.23 2009/03/04 21:20:03 nancy Exp $ 
 **  $Date: 2009/03/04 21:20:03 $ 
 **  $Revision: 1.23 $
 **  \author Nancy Marinelli, U. of Notre Dame, US
 **
 ***/

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "RecoTracker/MeasurementDet/interface/MeasurementTracker.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/MeasurementDet/interface/LayerMeasurements.h"
#include "TrackingTools/DetLayers/interface/NavigationSetter.h"
#include "TrackingTools/DetLayers/interface/NavigationSchool.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "RecoTracker/TkNavigation/interface/SimpleNavigationSchool.h"
#include "RecoTracker/TkDetLayers/interface/GeometricSearchTracker.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/Common/interface/View.h"

class ConversionTrackEcalImpactPoint;
class ConversionTrackPairFinder;
class ConversionVertexFinder;
class ConvertedPhotonProducer : public edm::EDProducer {

 public:

  ConvertedPhotonProducer (const edm::ParameterSet& ps);
  ~ConvertedPhotonProducer();

  virtual void beginRun (edm::Run& r, edm::EventSetup const & es);
  virtual void endRun (edm::Run& r, edm::EventSetup const & es);
  virtual void produce(edm::Event& evt, const edm::EventSetup& es);
  virtual void endJob();


 private:

  void buildCollections ( const edm::Handle<edm::View<reco::CaloCluster> > & scHandle,
			  const edm::Handle<edm::View<reco::CaloCluster> > & bcHandle,
			  std::map<std::vector<reco::TransientTrack>, reco::CaloClusterPtr>& allPairs,
			  reco::ConversionCollection & outputConvPhotonCollection);
    
  
  std::string conversionOITrackProducer_;
  std::string conversionIOTrackProducer_;


  std::string outInTrackSCAssociationCollection_;
  std::string inOutTrackSCAssociationCollection_;


  std::string ConvertedPhotonCollection_;
  
//  std::string bcProducer_;
  edm::InputTag bcBarrelCollection_;
  edm::InputTag bcEndcapCollection_;
  edm::InputTag scHybridBarrelProducer_;
  edm::InputTag scIslandEndcapProducer_;
  //  std::string scHybridBarrelCollection_;
  //std::string scIslandEndcapCollection_;
  edm::ParameterSet conf_;

  edm::ESHandle<MagneticField> theMF_;
  edm::ESHandle<TransientTrackBuilder> theTransientTrackBuilder_;

  ConversionTrackPairFinder*      theTrackPairFinder_;
  ConversionVertexFinder*         theVertexFinder_;
  ConversionTrackEcalImpactPoint* theEcalImpactPositionFinder_;

  int nEvt_;
  std::string algoName_;


};
#endif
