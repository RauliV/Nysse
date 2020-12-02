#ifndef SCOOTER_HH
#define SCOOTER_HH

#include "interfaces/ivehicle.hh"
#include "interfaces/ipassenger.hh"
//#include "QString"
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

    std::vector<std::shared_ptr<Interface::IPassenger> > getPassengers() const;

    void addPassenger(std::shared_ptr<Interface::IPassenger> passenger);

    void removePassenger(std::shared_ptr<Interface::IPassenger> passenger);

private:
    Interface::Location location_;
    std::string name_;
    int battery_;
   };




#endif // SCOOTER_HH
