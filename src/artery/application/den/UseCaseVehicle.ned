package artery.application.den;

moduleinterface UseCaseVehicle
{
}

moduleinterface SuspendableUseCase extends UseCaseVehicle
{
    double detectionBlockingInterval @unit(s);
}
