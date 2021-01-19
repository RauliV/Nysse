#include "player.hh"
#include "setboard.hh"

Player::Player(std::string name, std::string colour):
    name_(name),
    colour_(colour)

{
    cash_ = 20;
    bank_ = 100;
    drunkness_ = 0;
    currentSteps_ = 0;
    routeVector_ = {};
}

void Player::remove()
{

}

void Player::move(Interface::Location loc)
{
    loc_ = loc;
}

Interface::Location Player::giveLocation() const
{
    return loc_;
}

bool Player::isRemoved() const
{
    return false;
}

Player::~Player()
{

}

bool Player::spendCash(double amount)
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

bool Player::withdrawCash(int amount)
{
    if(amount < bank_)
    {
        bank_ -= amount;
        cash_ += amount;
        return true;
    }
    else
    {
        return false;
    }
}

int Player::getCash()
{
    return cash_;
}

int Player::getBank()
{
    return bank_;
}

void Player::drink(int amount)
{
    drunkness_ += amount;
}

void Player::soberUp(int amount)
{
    drunkness_ -= amount;
}

int Player::getDrunkness()
{
    return drunkness_;
}

void Player::setIdle(bool state)
{
    idle_ = state;
}

bool Player::isIdle()
{
    return idle_;
}

std::string Player::getColour()
{
    return colour_;
}

std::string Player::getName()
{
    return name_;
}

void Player::getInVechile(std::shared_ptr <Interface::IVehicle> vehicle)
{
    inVehicle_ = vehicle;
}

std::shared_ptr<Interface::IVehicle> Player::inWhichVehicle ()
{
    return inVehicle_;
}

void Player::setChosenLocation (Interface::Location loc)
{

    chosenLocation_ = loc;
}

Interface::Location Player::getChosenLocation ()
{
    return chosenLocation_;
}

void Player::setRouteVector (std::shared_ptr<std::vector<Interface::Location>> vec)
{
    routeVector_ = vec;
}

std::shared_ptr<std::vector<Interface::Location>> Player::getRouteVector ()
{
    //Jos nyssessä vektori = bussivektori
    return routeVector_;
}

void Player::takeStep ()
{
    //kävellen
    if (inVehicle_ == nullptr)
    {
        currentSteps_  ++;
    }
    else
    {
        if (getSubClass(inVehicle_) == "nysse")
        {
            std::shared_ptr<Scooter> vehc = std::dynamic_pointer_cast<Scooter> (inVehicle_);
            currentSteps_ = currentSteps_ + 4;
        }

        else if (inVehicle_->getName() == "scooter")
        {
            std::shared_ptr<Scooter> vehc = std::dynamic_pointer_cast<Scooter> (inVehicle_);
            currentSteps_ = currentSteps_ + vehc->getSpeed();
            this->spendCash(vehc->getCostPerTick());
        }

        else if (inVehicle_->getName() == "taxi")
        {
            std::shared_ptr<Taxi> vehc = std::dynamic_pointer_cast<Taxi> (inVehicle_);
            currentSteps_ = currentSteps_ + vehc->getSpeed();
            this->spendCash(vehc->getCostPerTick());
        }
    }
}

int Player::getCurrentSteps ()
{
    return currentSteps_;
}


void Player::resetRoute ()
{
    currentSteps_ = 0;
    routeVector_ = {};
    Interface::Location nLoc(0,0);
    chosenLocation_ = nLoc;

}

void Player::exitBar()
{
    isInBar_ = false;
}

void Player::enterBar()
{
    isInBar_ = true;
}

bool Player::isInBar()
{
    return isInBar_;
}
