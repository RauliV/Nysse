#ifndef TAXI_HH
#define TAXI_HH


#include "interfaces/ivehicle.hh"
#include "interfaces/ipassenger.hh"
//#include "QString"
#include "memory"

class Taxi
{
public:
    Taxi();

    ~Taxi();

    Interface::Location giveLocation() const;

    void move(Interface::Location loc);

    bool isRemoved() const;

    void remove();

    std::string getName() const;

    std::vector<std::shared_ptr<Interface::IPassenger> > getPassengers() const;

    void addPassenger(std::shared_ptr<Interface::IPassenger> passenger);

    void removePassenger(std::shared_ptr<Interface::IPassenger> passenger);

    int getSpeed();

    double getCostPerTick();

    int getMaxPromilleLevel();

private:
    Interface::Location location_;
    std::string name_;
    int speed_;
    double costPerTick_;
    int maxPromilleLevel_;

};



#endif // TAXI_HH
