/*
 * Artery V2X Simulation Framework
 * Copyright 2018 Christina Obermaier
 * Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
 */

#ifndef ARTERY_DEN_USECASEVEHICLE_H_
#define ARTERY_DEN_USECASEVEHICLE_H_

#include "artery/application/den/UseCase.h"

namespace artery
{

class VehicleDataProvider;

namespace den
{
class UseCaseVehicle : public UseCase
{
public:
    void initialize(int stage);
    vanetza::asn1::Denm createMessageSkeleton();

protected:
    const VehicleDataProvider* mVdp = nullptr;
};

} // namespace den
} // namespace artery


#endif /* ARTERY_DEN_USECASEVEHICLE_H_ */
