/*
 * Artery V2X Simulation Framework
 * Copyright 2016-2018 Raphael Riebl, Christina Obermaier
 * Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
 */

#include "artery/application/DenmObject.h"
#include "artery/application/DenService.h"
#include "artery/application/den/UseCase.h"
#include "artery/application/den/IcyRoadUseCase.h"
#include "artery/application/StoryboardSignal.h"
#include "artery/application/VehicleDataProvider.h"
#include <omnetpp/cexception.h>

#include "artery/traci/VehicleController.h"
#include <boost/units/base_units/metric/hour.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include <iostream>
#include <string>
#include <unistd.h>

#include <stdbool.h>

static const auto hour = 3600.0 * boost::units::si::seconds;
static const auto km_per_hour = boost::units::si::kilo * boost::units::si::meter / hour;



Define_Module(artery::den::IcyRoad);

namespace artery
{
namespace den
{


void IcyRoad::check()
{
    if (mPendingRequest) {
        transmitMessage();
        mPendingRequest = false;
    }
}

void IcyRoad::indicate(const artery::DenmObject& denm)
{
    const vanetza::asn1::Denm& asn1 = denm.asn1();

    vanetza::units::GeoAngle lat = *static_cast<vanetza::units::GeoAngle *>(static_cast<void*>(asn1->denm.alacarte->latitude_bytes));

    printf("CAR received lat %d \n", lat);
    fflush(stdout);

    printf("sentfromRSU %d\n", *asn1->denm.alacarte->sentFromRSU);
    fflush(stdout);

    if (denm & CauseCode::AdverseWeatherCondition_Adhesion) {

        mVehicleController = &mService->getFacilities().get_mutable<traci::VehicleController>();

        auto vehID = mVehicleController->getVehicleId();
        printf("%d Received Icy Road\n", vehID);
        fflush(stdout);


        slowDown();
    }


}

void IcyRoad::slowDown()
{

    double speed = 3;
    //mVehicleController->setSpeed(1 * boost::units::si::meter_per_second);

    auto vehicleID = mVehicleController->getVehicleId();
    //mVehicleController->getLiteAPI().vehicle().setSpeed(vehicleID, -1);

    //in miliseconds
    double duration = 20000;

    mVehicleController->getLiteAPI().vehicle().slowDown(vehicleID, speed, duration);

}

void IcyRoad::transmitMessage()
{
    vanetza::units::GeoAngle lat = mVdp->latitude();
    vanetza::units::GeoAngle lon = mVdp->longitude();

    auto denm = createMessage(lat,lon);
    auto request = createRequest(lat,lon);
    printf("IcyRoad::transmitMessage 1\n");
    fflush(stdout);
    mService->sendDenm(std::move(denm), request);
    printf("IcyRoad::transmitMessage 2\n");
    fflush(stdout);
}

void IcyRoad::handleStoryboardTrigger(const StoryboardSignal& signal)
{
    if (signal.getCause() == "icy_road") {

        mVehicleController = &mService->getFacilities().get_mutable<traci::VehicleController>();


        auto vehID = mVehicleController->getVehicleId();
        printf("%d Storyboard Icy Road\n", vehID);
        fflush(stdout);

        auto viewID = std::string("View #0");
        mVehicleController->getLiteAPI().gui().trackVehicle(viewID, vehID);

        mPendingRequest = true;
    }
}


vanetza::asn1::Denm IcyRoad::createMessage(vanetza::units::GeoAngle lat ,vanetza::units::GeoAngle lon)
{
    auto msg = createMessageSkeleton();

    msg->denm.alacarte = vanetza::asn1::allocate<AlacarteContainer_t>();
    bool b = true;
    msg->denm.alacarte->sentFromRSU = &b;

    printf("Bool %d %d\n", b, &b );
    printf("Bool sentfromRSU %d\n", *msg->denm.alacarte->sentFromRSU);
    printf("Bool sentfromRSU %d\n", msg->denm.alacarte->sentFromRSU);
    fflush(stdout);

    printf("CAR LAT before%d\n", lat);
    fflush(stdout);

    char latitude_bytes[sizeof lat];
    std::copy(static_cast<const char*>(static_cast<const void*>(&lat)),
              static_cast<const char*>(static_cast<const void*>(&lat)) + sizeof lat,
              latitude_bytes);

    msg->denm.alacarte->latitude_bytes = latitude_bytes;

    lat = *static_cast<vanetza::units::GeoAngle *>(static_cast<void*>(latitude_bytes));
    printf("CAR LAT after%d\n", lat);
    fflush(stdout);

    char longitude_bytes[sizeof lon];
    std::copy(static_cast<const char*>(static_cast<const void*>(&lon)),
              static_cast<const char*>(static_cast<const void*>(&lon)) + sizeof lon,
              longitude_bytes);

    msg->denm.alacarte->longitude_bytes = longitude_bytes;


    msg->denm.management.relevanceDistance = vanetza::asn1::allocate<RelevanceDistance_t>();
    *msg->denm.management.relevanceDistance = RelevanceDistance_lessThan50m;
    msg->denm.management.relevanceTrafficDirection = vanetza::asn1::allocate<RelevanceTrafficDirection_t>();
    *msg->denm.management.relevanceTrafficDirection = RelevanceTrafficDirection_allTrafficDirections;
    msg->denm.management.validityDuration = vanetza::asn1::allocate<ValidityDuration_t>();
    *msg->denm.management.validityDuration = 2;
    msg->denm.management.stationType = StationType_unknown; // TODO retrieve type from SUMO mVdp->getStationType();

    msg->denm.situation = vanetza::asn1::allocate<SituationContainer_t>();
    msg->denm.situation->informationQuality = 1;
    msg->denm.situation->eventType.causeCode =  CauseCodeType_adverseWeatherCondition_Adhesion;
    msg->denm.situation->eventType.subCauseCode = 0;

    return msg;
}

vanetza::btp::DataRequestB IcyRoad::createRequest(vanetza::units::GeoAngle lat ,vanetza::units::GeoAngle lon)
{
    //http://doxygen.cohdawireless.com/api/html/a01491.html
    namespace geonet = vanetza::geonet;
    using vanetza::units::si::seconds;
    using vanetza::units::si::meter;

    vanetza::btp::DataRequestB request;
    request.gn.traffic_class.tc_id(0); //http://doxygen.cohdawireless.com/api/html/a00996.html
    request.gn.maximum_hop_limit = 1;

    /*
    geonet::DataRequest::Repetition repetition;
    repetition.interval = 1 * seconds;
    repetition.maximum = 0 * seconds;
    request.gn.repetition = repetition;
    */

    geonet::Area destination;
    geonet::Circle destination_shape;
    destination_shape.r = 100.0 * meter;
    destination.shape = destination_shape;
    destination.position.latitude = lat;
    destination.position.longitude = lon;
    request.gn.destination = destination;

    return request;
}

} // namespace den
} // namespace artery
