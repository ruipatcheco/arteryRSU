/*
 * Artery V2X Simulation Framework
 * Copyright 2016-2018 Raphael Riebl, Christina Obermaier
 * Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
 */

#include "artery/application/DenmObject.h"
#include "artery/application/DenService.h"
#include "artery/application/den/IcyRoadUseCaseRSU.h"
#include "artery/application/StoryboardSignal.h"
#include <omnetpp/cexception.h>

#include <omnetpp/simtime.h>
#include "artery/utility/simtime_cast.h"
#include <iostream>
#include <string>

#include <stdbool.h>

Define_Module(artery::den::IcyRoadRSU);

namespace artery
{
namespace den
{


void IcyRoadRSU::check()
//note invoked for each middleware time step (trigger)
{

    //const omnetpp::SimTime& T_now = omnetpp::simTime();

    if(mLastTimestamp == omnetpp::SimTime::ZERO){
        printf("initializing RSU\n");
        fflush(stdout);

        mLastTimestamp = omnetpp::simTime();
    }

    const omnetpp::SimTime T_elapsed = mLastTimestamp - omnetpp::simTime();

    //printf("RSU time last %d\n", mLastTimestamp);
    //printf("RSU time now %d\n", omnetpp::simTime());
    //printf("RSU time elapsed %d\n", T_elapsed);
    fflush(stdout);

    mLastTimestamp = omnetpp::simTime();
}


void IcyRoadRSU::indicate(const artery::DenmObject& denm)
{
    const vanetza::asn1::Denm& asn1 = denm.asn1();

    if (asn1->denm.situation->eventType.causeCode == CauseCodeType_adverseWeatherCondition_Adhesion) {

        printf("IcyRoadRSU::indicate 1\n");
        fflush(stdout);

        vanetza::units::GeoAngle lat = *static_cast<vanetza::units::GeoAngle *>(static_cast<void*>(asn1->denm.alacarte->latitude_bytes));
        vanetza::units::GeoAngle lon = *static_cast<vanetza::units::GeoAngle *>(static_cast<void*>(asn1->denm.alacarte->longitude_bytes));

        printf("RSU LAT received %d\n", lat);
        fflush(stdout);

        printf("sentfromRSU %d %d\n", *asn1->denm.alacarte->sentFromRSU, asn1->denm.alacarte->sentFromRSU);
        fflush(stdout);

        retransmitMessage(asn1);
        printf("RSU reSending Message\n");


        fflush(stdout);
    }
}

void IcyRoadRSU::retransmitMessage(const vanetza::asn1::Denm& asn1)
{
    auto denm = recreateMessage(asn1);
    auto request = recreateRequest(asn1);

    printf("IcyRoadRSU::retransmitMessage 1\n");
    fflush(stdout);
    mService->sendDenm(std::move(denm), request);
    printf("IcyRoadRSU::retransmitMessage 2\n");
    fflush(stdout);
}

void IcyRoadRSU::handleStoryboardTrigger(const StoryboardSignal& signal)
{
    if (signal.getCause() == "icy_road_rsu") {
        std::string message("RSU Icy Road received from storyboard");
        std::cout << message << "\n";
    }
}

vanetza::asn1::Denm IcyRoadRSU::recreateMessage(const vanetza::asn1::Denm& asn1)
{
    auto msg = createMessageSkeleton();

    msg->denm.alacarte = vanetza::asn1::allocate<AlacarteContainer_t>();
    bool b = true;
    msg->denm.alacarte->sentFromRSU = &b;

    //msg->denm.management.eventPosition.latitude = asn1->denm.management.eventPosition.latitude;
    //msg->denm.management.eventPosition.longitude = asn1->denm.management.eventPosition.longitude;

    msg->denm.management.relevanceDistance = vanetza::asn1::allocate<RelevanceDistance_t>();
    *msg->denm.management.relevanceDistance = RelevanceDistance_lessThan50m;
    msg->denm.management.relevanceTrafficDirection = vanetza::asn1::allocate<RelevanceTrafficDirection_t>();
    *msg->denm.management.relevanceTrafficDirection = RelevanceTrafficDirection_allTrafficDirections;
    msg->denm.management.validityDuration = vanetza::asn1::allocate<ValidityDuration_t>();
    *msg->denm.management.validityDuration = 2;
    msg->denm.management.stationType = StationType_roadSideUnit;

    msg->denm.situation = vanetza::asn1::allocate<SituationContainer_t>();
    msg->denm.situation->informationQuality = 1;
    msg->denm.situation->eventType.causeCode =  CauseCodeType_hazardousLocation_SurfaceCondition;
    msg->denm.situation->eventType.subCauseCode = 0;

    return msg;
}

vanetza::btp::DataRequestB IcyRoadRSU::recreateRequest(const vanetza::asn1::Denm& asn1)
{
    namespace geonet = vanetza::geonet;
    using vanetza::units::si::seconds;
    using vanetza::units::si::meter;

    vanetza::btp::DataRequestB request;
    request.gn.traffic_class.tc_id(0);
    request.gn.maximum_hop_limit = 1;

    geonet::DataRequest::Repetition repetition;
    repetition.interval = 1 * seconds;
    repetition.maximum = 60 * seconds;
    request.gn.repetition = repetition;

    geonet::Area destination;
    geonet::Circle destination_shape;
    destination_shape.r = 500.0 * meter;
    destination.shape = destination_shape;

    vanetza::units::GeoAngle lat = *static_cast<vanetza::units::GeoAngle *>(static_cast<void*>(asn1->denm.alacarte->latitude_bytes));
    destination.position.latitude = lat;

    printf("RSU recreated LAT %d\n", destination.position.latitude);
    fflush(stdout);

    vanetza::units::GeoAngle lon = *static_cast<vanetza::units::GeoAngle *>(static_cast<void*>(asn1->denm.alacarte->longitude_bytes));
    destination.position.longitude = lon;

    request.gn.destination = destination;

    return request;
}

} // namespace den
} // namespace artery
