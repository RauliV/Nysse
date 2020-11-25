#ifndef PLAYER_HH
#define PLAYER_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"

class player : public  Interface::IActor
{
public:
    player();
    //void destroy() override;
    void move(Interface::Location loc) override;
    Interface::Location giveLocation() const override;
    //bool isDestroyed() const override;
    //~player() override;

    bool spendCash(int amount);
    void withdrawCash(int amount);
    int getCash();

    void drink(int amount);
    void soberUp(int amount);
    int getDrunkness();

    void setIdle(bool idle);
    bool isIdle();



private:
    int cash_;
    int drunkness_;
    Interface::Location loc_;
    bool idle_ = true;
};

#endif // PLAYER_HH
