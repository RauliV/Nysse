#include "taxi.hh"

Taxi::Taxi()
{
    speed_ = 2;
    costPerTick_ = 0.4;
    int maxPromilleLevel_ = 2;
}

Taxi::~Taxi()
{

}


Interface::Location Taxi::giveLocation() const
{
        return location_;
}


void Taxi::move(Interface::Location loc)
{
    location_ = loc;
}

bool Taxi::isRemoved() const
{
    return false; //poistetaanko kun akku tyhjä?
}

void Taxi::remove()
{
                  // ^
}

 std::string Taxi::getName() const
 {
    return "taxi";
 }

 std::vector<std::shared_ptr<Interface::IPassenger> > Taxi::getPassengers() const
 {
     return {};
 }

 void Taxi::addPassenger(std::shared_ptr<Interface::IPassenger> passenger)
 {

 }

 void Taxi::removePassenger(std::shared_ptr<Interface::IPassenger> passenger)
 {

 }


 int Taxi::getSpeed()
 {
     return speed_;
 }

 double Taxi::getCostPerTick()
 {
     return costPerTick_;
 }

 int Taxi::getMaxPromilleLevel()
 {
     return maxPromilleLevel_;
 }
