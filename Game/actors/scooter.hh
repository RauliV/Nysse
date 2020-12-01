#ifndef SCOOTER_HH
#define SCOOTER_HH

#include "interfaces/ivehicle.hh"
#include "interfaces/ipassenger.hh"
#include "memory"


class Scooter : public Interface::IVehicle
{
public:
    Scooter();
    ~Scooter();

    Interface::Location giveLocation() const;

    void move(Interface::Location loc);

    bool isRemoved() const;

    void remove();

     std::string getName() const;

     std::vector<std::shared_ptr<Interface::IPassenger> > getPassengers();

     void addPassenger(std::shared_ptr<Interface::IPassenger> passenger);

     void removePassenger(std::shared_ptr<Interface::IPassenger> passenger);

   };




#endif // SCOOTER_HH
