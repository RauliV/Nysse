#ifndef LOCATIONITEM_HH
#define LOCATIONITEM_HH

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

#include "interfaces/istop.hh"

const int WIDTH = 15;
const int HEIGHT = 15;

class LocationItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit LocationItem(QObject *parent = nullptr, int x = 0, int y = 0, int type = 2, std::shared_ptr<QImage> icon = nullptr, std::shared_ptr<Interface::IStop> place = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCoord(int x, int y);
signals:
    void itemClicked(std::shared_ptr<Interface::IStop> place);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*event);
private:
    int x_;
    int y_;
    int type_;
    void emitSignal(std::shared_ptr<Interface::IStop> place);
    std::shared_ptr<QImage> icon_;
    std::shared_ptr<Interface::IStop> place_;
};

#endif // LOCATIONITEM_HH
