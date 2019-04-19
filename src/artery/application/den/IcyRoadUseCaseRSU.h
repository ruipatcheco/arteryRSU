/*
 * Artery V2X Simulation Framework
 * Copyright 2016-2018 Raphael Riebl, Christina Obermaier
 * Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
 */

#ifndef ARTERY_DEN_ICYROADUSECASE_H_FE8Z3BLA
#define ARTERY_DEN_ICYROADUSECASE_H_FE8Z3BLA

#include "artery/application/den/SuspendableUseCaseRSU.h"


namespace artery
{
namespace den
{

class IcyRoadRSU : public SuspendableUseCaseRSU
{
public:
    // UseCase interface
    void check();
    void indicate(const artery::DenmObject&);
    void handleStoryboardTrigger(const StoryboardSignal&);

    vanetza::asn1::Denm recreateMessage(const vanetza::asn1::Denm& asn1);
    vanetza::btp::DataRequestB recreateRequest(const vanetza::asn1::Denm& asn1);

private:
    bool mPendingRequest = false;
    void retransmitMessage(const vanetza::asn1::Denm& asn1);
    omnetpp::SimTime mLastTimestamp = omnetpp::SimTime::ZERO;
};

} // namespace den
} // namespace artery

#endif /* ARTERY_DEN_ICYROADUSECASE_H_FE8Z3BLA */

