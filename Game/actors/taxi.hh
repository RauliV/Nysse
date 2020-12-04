#ifndef TAXI_HH
#define TAXI_HH


#include "interfaces/ivehicle.hh"
#include "interfaces/ipassenger.hh"
#include "QImage"
#include "QString"
#include "memory"

class Taxi : public Interface::IVehicle
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

    std::shared_ptr<QImage> getIcon();

private:
    Interface::Location location_;
    std::string name_;
    int speed_;
    double costPerTick_;
    int maxPromilleLevel_;
    QString iconFile = ":/graphics/taxi_icon.png";


};



#endif // TAXI_HH
