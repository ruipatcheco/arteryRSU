/*
 * Artery V2X Simulation Framework
 * Copyright 2018 Christina Obermaier
 * Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
 */

#ifndef ARTERY_DEN_USECASERSU_H_
#define ARTERY_DEN_USECASERSU_H_

#include "artery/application/den/UseCase.h"

namespace artery
{
namespace den
{
class UseCaseRSU : public UseCase
{
public:
    void initialize(int stage);
    vanetza::asn1::Denm createMessageSkeleton();

};

} // namespace den
} // namespace artery

#endif /* ARTERY_DEN_USECASERSU_H_ */
