#include "scooter.hh"

Scooter::Scooter()
{

}

Scooter::~Scooter()
{

}


Interface::Location Scooter::giveLocation() const
{

}


void Scooter::move(Interface::Location loc)
{

}

bool Scooter::isRemoved() const
{

}

void Scooter::remove()
{

}

 std::string Scooter::getName() const
 {

 }

 std::vector<std::shared_ptr<Interface::IPassenger> > Scooter::getPassengers()
 {

 }

 void Scooter::addPassenger(std::shared_ptr<Interface::IPassenger> passenger)
 {

 }

 void Scooter::removePassenger(std::shared_ptr<Interface::IPassenger> passenger)
 {

 }
