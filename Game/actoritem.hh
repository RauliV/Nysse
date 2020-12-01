#ifndef ACTORITEM_HH
#define ACTORITEM_HH
#include "graphics/simpleactoritem.hh"
#include "actors/player.hh"

class ActorItem : public CourseSide::SimpleActorItem
{
public:
    ActorItem(int x, int y, int type, QString iconPath);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
QString iconPath_;
};

#endif // ACTORITEM_HH
