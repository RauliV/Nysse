#ifndef PLAYER_HH
#define PLAYER_HH
#include "scooter.hh"
#include "taxi.hh"
//#include "setboard.hh"
#include "interfaces/iactor.hh"
#include "core/location.hh"
#include "interfaces/ivehicle.hh"
#include <iostream>
#include <memory>


class Player : public  Interface::IActor
{
public:

    Player(std::string name, std::string colour);
    void remove();
    void move(Interface::Location loc) override;
    Interface::Location giveLocation() const override;
    bool isRemoved() const;
    ~Player() override;

    bool spendCash(double amount);
    bool withdrawCash(int amount);
    int getCash();
    int getBank();

    void drink(int amount);
    void soberUp(int amount);
    int getDrunkness();

    void setIdle(bool state);
    bool isIdle();

    std::string getColour();
    std::string getName();

    void getInVechile(std::shared_ptr <Interface::IVehicle> vehicle);
    std::shared_ptr <Interface::IVehicle> inWhichVehicle ();

    Interface::Location getChosenLocation();
    void setChosenLocation (Interface::Location loc);

    void setRouteVector (std::shared_ptr<std::vector<Interface::Location>> vec);
    std::shared_ptr<std::vector<Interface::Location>> getRouteVector ();
    void resetRoute ();

    void takeStep();
    int getCurrentSteps ();
    void enterBar();
    void exitBar();
    bool isInBar();





private:
    int cash_;
    int drunkness_;
    int bank_;
    Interface::Location loc_;
    bool idle_ = true;
    std::string name_;
    std::string colour_;
    std::shared_ptr <Interface::IVehicle> inVehicle_;
    Interface::Location chosenLocation_;
    int currentSteps_;
    std::shared_ptr<std::vector<Interface::Location>> routeVector_;
    bool isInBar_;


};

#endif // PLAYER_HH
