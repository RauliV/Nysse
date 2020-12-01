#include "atm.hh"

Atm::Atm()
{

}

Atm::~Atm()
{

}

Interface::Location Atm::getLocation() const{
    return location_;
}

QString Atm::getName() const
{return "";}

void Atm::setLocation(const Interface::Location &location)
{
    location_ = location;
}

void Atm::setName(const QString &name)
{
    QString empty = name;
}
