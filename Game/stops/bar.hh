#ifndef BAR_HH
#define BAR_HH

#include "interfaces/istop.hh"
#include "interfaces/ivehicle.hh"
#include "core/location.hh"
#include "interfaces/ipassenger.hh"
#include "actors/passenger.hh"
#include "interfaces/istop.hh"

#include <QString>
#include <set>



class Bar : public Interface::IStop
{
public:
    Bar();
    ~Bar();

    Interface::Location getLocation() const;
    QString getName() const;
    void setLocation(const Interface::Location &location);
    void setName(const QString &name);


    //void removePassenger(const std::weak_ptr<Interface::IPassenger> passenger){};

    unsigned int getId() const {return 0;}

    std::vector<std::shared_ptr<Interface::IPassenger>> getPassengers() const
    {
        std::vector<std::shared_ptr<Interface::IPassenger>> nullreturn;
        return nullreturn;
    }

private:
    Interface::Location location_;
    QString name_;


};

#endif // BAR_HH
