#include "locationitem.hh"


LocationItem::LocationItem(QObject *parent, int x, int y, int type, std::shared_ptr<QImage> icon, std::shared_ptr<Interface::IStop> place) : QObject(parent), x_(x), y_(y), type_(type), icon_(icon), place_(place)
{
    setPos(mapToParent(x_, y_));
    this->setEnabled(true);
}

QRectF LocationItem::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
}

void LocationItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    QBrush brush;
    if(icon_== nullptr)
    {
        brush = Qt::black;
        painter->setBrush(brush);
        painter->drawEllipse(bounds);
    }
    else
    {
        painter->drawImage(bounds, *icon_);
        this->setToolTip(place_->getName());

    }
}

void LocationItem::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

void LocationItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
        QGraphicsItem::mousePressEvent(event);
        emit itemClicked(place_);
}
