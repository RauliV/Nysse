#ifndef STATICITEM_HH
#define STATICITEM_HH
#include "graphics/simpleactoritem.hh"
#include "interfaces/istop.hh"
#include <QObject>

class StaticItem :  public QObject, public CourseSide::SimpleActorItem
{
   //Q_OBJECT
    //Q_INTERFACES(SimpleActorItem)
public:
    StaticItem( int x = 0, int y = 0, int type = 2, std::shared_ptr<QImage> icon = nullptr, std::shared_ptr<Interface::IStop> place = nullptr);
    virtual ~StaticItem(){};

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void itemClicked(std::shared_ptr<Interface::IStop> place);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*event) override;
private:
    void emitSignal(std::shared_ptr<Interface::IStop> place);
    std::shared_ptr<QImage> icon_;
    std::shared_ptr<Interface::IStop> place_;

};

#endif // STATICITEM_HH
