#ifndef PLAYER_HH
#define PLAYER_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"

class Player : public  Interface::IActor
{
public:
    Player();
    void destroy() override;
    void move(Interface::Location loc) override;
    Interface::Location giveLocation() const override;
    bool isDestroyed() const override;
    ~Player() override;

    bool spendCash(int amount);
    bool withdrawCash(int amount);
    int getCash();
    int getBank();

    void drink(int amount);
    void soberUp(int amount);
    int getDrunkness();

    void setIdle(bool state);
    bool isIdle();



private:
    int cash_;
    int drunkness_;
    int bank_;
    Interface::Location loc_;
    bool idle_ = true;
};

#endif // PLAYER_HH
