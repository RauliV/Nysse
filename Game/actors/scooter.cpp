#include "scooter.hh"

Scooter::Scooter()
{
    battery_ = 100;
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
