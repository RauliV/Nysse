#include "player.hh"

player::player()
{

}

void player::move(Interface::Location loc)
{

}

bool player::spendCash(int amount)
{
    if(amount < cash_){
        cash_ -= amount;
        return true;
    }
    //Not enough money on player for the payment
    else{
        return false;
    }
}

void player::withdrawCash(int amount)
{
    cash_ += amount;
}

void player::drink(int amount)
{
    drunkness_ += amount;
}

void player::soberUp(int amount)
{
    drunkness_ -= amount;
}
