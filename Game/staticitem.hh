#ifndef STATICITEM_HH
#define STATICITEM_HH
#include "graphics/simpleactoritem.hh"
#include "interfaces/istop.hh"
#include <QObject>

class StaticItem : public CourseSide::SimpleActorItem
{
public:
    StaticItem(int x, int y, int type, std::shared_ptr<QImage> icon, std::shared_ptr<Interface::IStop> place);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
/*signals:
    void itemClicked(std::shared_ptr<Interface::IStop> place);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*event) override;*/
private:
    std::shared_ptr<QImage> icon_;
    std::shared_ptr<Interface::IStop> place_;

};

#endif // STATICITEM_HH
