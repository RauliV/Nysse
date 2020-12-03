#include "scooter.hh"

Scooter::Scooter()
{
    battery_ = 100;
    speed_ = 2;
    costPerTick_ = 0.4;
    int maxPromilleLevel_ = 2;

}

Scooter::~Scooter()
{

}


Interface::Location Scooter::giveLocation() const
{
        return location_;
}


void Scooter::move(Interface::Location loc)
{
    location_ = loc;
}

bool Scooter::isRemoved() const
{
    return false; //poistetaanko kun akku tyhjä?
}

void Scooter::remove()
{
                  // ^
}

 std::string Scooter::getName() const
 {
    return "scooter";
 }

 std::vector<std::shared_ptr<Interface::IPassenger> > Scooter::getPassengers() const
 {
     return {};
 }

 void Scooter::addPassenger(std::shared_ptr<Interface::IPassenger> passenger)
 {

 }

 void Scooter::removePassenger(std::shared_ptr<Interface::IPassenger> passenger)
 {

 }

 int Scooter::getSpeed()
 {
     return speed_;
 }

 double Scooter::getCostPerTick()
 {
     return costPerTick_;
 }

 int Scooter::getMaxPromilleLevel()
 {
     return maxPromilleLevel_;
 }
