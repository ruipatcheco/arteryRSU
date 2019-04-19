/*
 * Artery V2X Simulation Framework
 * Copyright 2016-2018 Raphael Riebl, Christina Obermaier
 * Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
 */

#ifndef ARTERY_DEN_ICYROADUSECASE_H_FE8Z3BLA
#define ARTERY_DEN_ICYROADUSECASE_H_FE8Z3BLA

#include "artery/application/den/UseCase.h"
#include "artery/application/den/UseCaseVehicle.h"
#include <vanetza/units/velocity.hpp>

//typedef boost::units::quantity<boost::units::si::velocity> Velocity;

// forward declaration
namespace traci { class VehicleController; }

namespace artery
{
namespace den
{

class IcyRoad : public UseCaseVehicle
{
public:
    // UseCase interface
    void check();
    void indicate(const artery::DenmObject&);
    void handleStoryboardTrigger(const StoryboardSignal&);

    vanetza::asn1::Denm createMessage(vanetza::units::GeoAngle lat ,vanetza::units::GeoAngle lon);
    vanetza::btp::DataRequestB createRequest(vanetza::units::GeoAngle lat ,vanetza::units::GeoAngle lon);

private:
    bool mPendingRequest = false;
    void transmitMessage();

    void slowDown();
    traci::VehicleController* mVehicleController = nullptr;


};

} // namespace den
} // namespace artery

#endif /* ARTERY_DEN_ICYROADUSECASE_H_FE8Z3BLA */

