#include "bar.hh"

Bar::Bar()
{

}

Bar::~Bar()
{

}

Interface::Location Bar::getLocation() const{
    return location_;
}

QString Bar::getName() const
{return "";}

void Bar::setLocation(const Interface::Location &location)
{
    location_ = location;
}

void Bar::setName(const QString &name)
{
    QString empty = name;
}


