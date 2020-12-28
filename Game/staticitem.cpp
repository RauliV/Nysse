#include "staticitem.hh"




StaticItem::StaticItem( int x, int y, int type, std::shared_ptr<QImage> icon, std::shared_ptr<Interface::IStop> place)
    : CourseSide::SimpleActorItem{x,y,type}
{

    icon_  = icon;
    place_ = place;
    this->setEnabled(true);
}

void StaticItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void StaticItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    emitSignal(place_);

}

void StaticItem::emitSignal(std::shared_ptr<Interface::IStop> place)
{
   //emit itemClicked(place);
}

