#ifndef PLAYER_HH
#define PLAYER_HH

#include "interfaces/iactor.hh"
#include "core/location.hh"

class player : public Interface::IActor
{
public:
    player();

    void move(Interface::Location loc) override;

    void destroy() override;

    Interface::Location giveLocation() const override;

    void spendCash(int price);

    void withdrawCash(int amount);

    void drink(int amount);

    void soberUp();

private:
    Interface::Location loc_;
    int cash_;
    int drunkness_;
};



#endif // PLAYER_HH
