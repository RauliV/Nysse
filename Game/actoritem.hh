#ifndef ACTORITEM_HH
#define ACTORITEM_HH
#include "graphics/simpleactoritem.hh"
#include "actors/player.hh"
#include "interfaces/iactor.hh"


class ActorItem : public CourseSide::SimpleActorItem
{
public:
    ActorItem(int x, int y, int type, const std::shared_ptr<QImage> icon, std::shared_ptr<Interface::IActor> actor);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void updateCoords();


private:
std::shared_ptr<QImage> icon_;
std::shared_ptr<Interface::IActor> actor_;

};

#endif // ACTORITEM_HH
