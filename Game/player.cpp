 #include "player.hh"

player::player()
{

}

void player::move(Interface::Location loc)
{
    loc_ = loc;
}

Interface::Location player::giveLocation() const
{
   return loc_;
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

void player::setIdle(bool state)
{
    idle_ = state;
}

bool player::isIdle()
{
    return idle_;
}
