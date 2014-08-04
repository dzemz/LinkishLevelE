#include "CustomGraphicsItem.h"
#include "CustomGraphicsScene.h"
#include "CustomTreeWidgetProperties.h"
#include "../LevelEditor.h"

#include <QDebug>
#include <QRect>
#include <QGraphicsTextItem>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QFont>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

CustomGraphicsItem::CustomGraphicsItem(QObject *parent) :
    QGraphicsEllipseItem(0)
{
}

void CustomGraphicsItem::initialize(QString uniqueIdentifier, QPointF pos)
{
    m_rings = 0;
    m_name = uniqueIdentifier;
    m_nodeDisplayMode = 0;

    QPen pen;
    pen.setWidthF(WIDTH_OBJECT_PEN);
    pen.setColor(COLOR_OBJECT_PEN);

    setPen(pen);
    setBrush(QBrush(COLOR_OBJECT_BRUSH));
    setRect(-RECT_OBJECT_START/2,-RECT_OBJECT_START/2,RECT_OBJECT_START,RECT_OBJECT_START);
    setPos(pos);
    setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsScenePositionChanges );

    setZValue(1);
    setToolTip(uniqueIdentifier);

    setData(0, "node:" + uniqueIdentifier);
}

void CustomGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_oldPoint = pos();
    m_pressPoint = event->scenePos();
    m_diffPoint = pos() - event->scenePos();
    m_mouseButton = event->button();


    QGraphicsEllipseItem::mousePressEvent(event);
}

void CustomGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouseButton = Qt::NoButton;
    m_snapToGrid = false;
    m_pressPoint = m_oldPoint = m_diffPoint = QPointF(0,0);

    QGraphicsEllipseItem::mouseReleaseEvent(event);

    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_NODES, "position", QString::number(pos().x()) + "," + QString::number(pos().y()));
    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_NODES, "links", QString::number(m_links.count()));
}

void CustomGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseDoubleClickEvent(event);
}

void CustomGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_mouseButton == Qt::RightButton)
    {

    }
    else if (m_mouseButton == Qt::LeftButton)
    {
        this->setPos(event->scenePos() + m_diffPoint);
    }


    QGraphicsEllipseItem::mouseMoveEvent(event);

    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_NODES, "position", QString::number(pos().x()) + "," + QString::number(pos().y()));
    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_NODES, "links", QString::number(m_links.count()));

}

void CustomGraphicsItem::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case 16777248:  //left shift key
        {
            m_snapToGrid = true;

            m_oldPoint = pos();
        }
        break;
        case 16777249 : //left control key
        {

        }
        break;
    }
    QGraphicsEllipseItem::keyPressEvent(event);
}

void CustomGraphicsItem::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case 16777248:  //left shift key
        {
            m_snapToGrid = false;
        }
        break;
        case 16777249 : //left control key
        {

        }
        break;
    }
    QGraphicsEllipseItem::keyReleaseEvent(event);
}

QVariant CustomGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(m_snapToGrid)
    {
        QPoint newPoint = value.toPoint();

        if (change == ItemPositionChange && scene()) {
            //if (newPoint.y() != m_oldPoint.y())
            //    newPoint.setY(m_oldPoint.y());
            int modX = (int)(newPoint.x()) % SCENE_GRID_X;
            if (modX <= (int)SCENE_GRID_X/2)
                newPoint.setX(newPoint.x()- modX);
            else
                newPoint.setX(newPoint.x()- modX + SCENE_GRID_X);

            int modY = (int)(newPoint.y()) % SCENE_GRID_Y;
            if (modY <= (int)SCENE_GRID_Y/2)
                newPoint.setY(newPoint.y()- modY);
            else
                newPoint.setY(newPoint.y()- modY + SCENE_GRID_Y);

            return newPoint;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void CustomGraphicsItem::setNodeDisplayMode(int mode)
{
    m_nodeDisplayMode = mode;
}

bool CustomGraphicsItem::addLink(CustomGraphicsItem* toItem)
{
    //check if connection already exists
    if(!m_links.isEmpty())
    {
        foreach(CustomGraphicsItem* link, m_links)
        {
            if(toItem == link)
                return false;
        }
    }

    m_links.push_back(toItem);
    QRectF rect = this->rect();
    rect.adjust(-ADJUST_OBJECT_RECT, -ADJUST_OBJECT_RECT, ADJUST_OBJECT_RECT, ADJUST_OBJECT_RECT);
    setRect(rect);
    ++m_rings;
    addRing();

    return true;
}

void CustomGraphicsItem::removeLink(CustomGraphicsItem* other)
{
     foreach(CustomGraphicsItem* link, m_links)
     {
        if (link->getName() == other->getName())
        {
            m_links.removeOne(link);
            break;
        }
     }

     removeRing();
     --m_rings;
     QRectF rect = this->rect();
     rect.adjust(ADJUST_OBJECT_RECT, ADJUST_OBJECT_RECT, -ADJUST_OBJECT_RECT, -ADJUST_OBJECT_RECT);
     setRect(rect);
     addRing();
}

void CustomGraphicsItem::addRing()
{
    if(m_nodeDisplayMode == (int)NODE_NUMBERS)
    {
        QPen pen;
        pen.setWidthF(WIDTH_OBJECT_PEN_CHILD);
        pen.setColor(COLOR_OBJECT_PEN_CHILD);

        if(m_rings > 0)
        {
            QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
            QRectF rect = this->rect();

            if(m_rings == 1)

                rect.adjust(2,2,-2,-2);
            else
                rect.adjust(3,3,-3,-3);
            item->setRect(rect);
            item->setPen(pen);
            item->setBrush(QBrush(COLOR_OBJECT_BRUSH));
            item->setParentItem(this);

            QGraphicsTextItem *rings = new QGraphicsTextItem();
            rings->setPlainText(QString::number(m_rings));
            rings->setDefaultTextColor(COLOR_OBJECT_TEXT);
            int adjust = 2;
            if(m_rings >= 3)
                adjust = 4;
            rings->setFont(QFont("Razer Regular", SIZE_OBJECT_TEXT_BASE + (m_rings*4)));
            rings->setParentItem(this);

            rings->setPos(-rings->sceneBoundingRect().width()/2, -rings->sceneBoundingRect().height()/2 - adjust);
        }
    }
    else if (m_nodeDisplayMode == (int)NODE_RINGS)
    {
        for(int i=0; i<m_rings;i++)
        {
            QPen pen;
            pen.setWidthF(WIDTH_OBJECT_PEN);
            pen.setColor(COLOR_OBJECT_PEN_CHILD);

            QGraphicsEllipseItem* item = new QGraphicsEllipseItem();
            QRectF rect = this->rect();
            rect.adjust(ADJUST_OBJECT_RECT*i,ADJUST_OBJECT_RECT*i,-ADJUST_OBJECT_RECT*i,-ADJUST_OBJECT_RECT*i);
            item->setRect(rect);
            item->setPen(pen);
            item->setBrush(QBrush(COLOR_OBJECT_BRUSH));
            item->setParentItem(this);
        }
    }
}

void CustomGraphicsItem::removeRing()
{
    foreach(QGraphicsItem* item, childItems())
    {
        item->setParentItem(NULL);
        CustomGraphicsScene* gs = dynamic_cast<CustomGraphicsScene*>(this->parent());
        gs->removeItem(item);
    }
}

void CustomGraphicsItem::toLevelObject(LevelObject& levelObject)
{
    levelObject.setName(m_name);

    levelObject.setPosition(sceneBoundingRect().center().toPoint());
    foreach(CustomGraphicsItem* link, m_links)
    {
        levelObject.addLink(link->m_name);
    }
}
