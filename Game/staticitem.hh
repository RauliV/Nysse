#ifndef STATICITEM_HH
#define STATICITEM_HH
#include "graphics/simpleactoritem.hh"
#include "interfaces/istop.hh"


class StaticItem : public CourseSide::SimpleActorItem
{
public:
    StaticItem(int x, int y, int type, std::shared_ptr<QImage> icon, std::shared_ptr<Interface::IStop> place);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    std::shared_ptr<QImage> icon_;
    std::shared_ptr<Interface::IStop> place_;
};

#endif // STATICITEM_HH
