#include "artery/application/den/SuspendableUseCaseRSU.h"

namespace artery
{
namespace den
{


void SuspendableUseCaseRSU::setDetectionBlockingInterval(omnetpp::SimTime block)
{
    mDetectionBlockingInterval = std::max(omnetpp::SimTime::ZERO, block);
}

bool SuspendableUseCaseRSU::isDetectionBlocked()
{
    if (mDetectionBlockingSince) {
        const auto now = omnetpp::simTime();
        if (*mDetectionBlockingSince + mDetectionBlockingInterval < now) {
            mDetectionBlockingSince.reset();
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void SuspendableUseCaseRSU::blockDetection()
{
    mDetectionBlockingSince = omnetpp::simTime();
}

} // namespace den
} // namespace artery
