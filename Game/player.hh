#ifndef PLAYER_HH
#define PLAYER_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"

class player : public  Interface::IActor
{
public:
    player();
    //void destroy() override;
    //void move(Interface::Location loc) override;
    void spendCash(int amount);
    void withdrawCash(int amount);
    void drink(int amount);
    void soberUp(int amount);


private:
    int cash;
    int drunkness;
    Interface::Location loc;
};

#endif // PLAYER_HH
