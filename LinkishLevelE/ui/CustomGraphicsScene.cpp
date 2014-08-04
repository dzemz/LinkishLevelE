#include "CustomGraphicsScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QList>
#include <QObject>
#include <QPointF>
#include "../LevelEditor.h"
#include <QRegExp>

CustomGraphicsScene::CustomGraphicsScene(QWidget *parent) :
    QGraphicsScene(parent)
{

}

void CustomGraphicsScene::initialize(QString packName, QString levelName)
{
    m_enableSnapping = false;
    m_drawLink = false;
    m_idCount = 1;
    m_nodeDisplayMode = NODE_NUMBERS;

    m_levelName = levelName;
    m_packName = packName;

    m_pointFirst = QPointF(0,0);
    m_connection = 0;
    m_connectionSource = 0;
    m_selectedItem = 0;
    m_gv = 0;
    m_cursorPos = 0;

    //x,y axis
    QPen pen;

    pen.setWidthF(2);
    pen.setStyle(Qt::DashLine);

    line = addLine(QLineF(0,-1500,0,1500), QPen(pen));
    line2 = addLine(QLineF(-1500,0,1500,0), QPen(pen));
    line->setZValue(10);
    line2->setZValue(10);
    line->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    line2->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    QPen pen2;
    pen2.setWidthF(1);
    pen2.setStyle(Qt::DashLine);

    //device markers
#if !IS_LANDSCAPE
    for(int i=0; i<2; i++)
    {
        if ( i==0 )
            continue;
        line3 = addLine(QLineF(320*i, -1500, 320*i, 1500), QPen(pen2));
        line4 = addLine(QLineF(-1500, 480*i, 1500, 480*i), QPen(pen2));
    }
#else
    for(int i=-2; i<3; i++)
    {
        if (i == 0)
            continnue;
        line3 = addLine(QLineF(480 + 480*i, -1500, 480 + 480*i, 1500), QPen(pen2));
        line4 = addLine(QLineF(-1500,320 + 320*i,1500, 320 + 320*i), QPen(pen2));
    }
#endif

    line3->setZValue(10);
    line4->setZValue(10);

    setSceneRect(-20,-20,340,500);
    setObjectName("graphicsScene_" + levelName);

    QGraphicsEllipseItem* scenePoint;
    for(int i=1; i <= 3 ; i++)
    {
        for(int j=1; j <= 3 ; j++)
        {
            QPen pen3;
            pen3.setWidthF(1);
            pen3.setColor(QColor(Qt::white));
            scenePoint = addEllipse(-2,-2,4,4,pen3,QBrush(QColor(Qt::white)));
            scenePoint->setPos(i*80, j*120);
            scenePoint->setZValue(0);
            scenePoint->setFlag(QGraphicsItem::ItemIgnoresTransformations);

        }
    }

    //background image
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(QPixmap("data/textures/linkish_bg2.png"));
    item->setZValue(-1);
    item->setOpacity(1);
    this->addItem(item);
}

void CustomGraphicsScene::setView(CustomGraphicsView *gv)
{
    m_gv = gv;
}

void CustomGraphicsScene::sceneRectChanged(const QRectF &rect)
{
    QGraphicsScene::sceneRectChanged(rect);
}

void CustomGraphicsScene::constructSceneFromLevel(Level& level)
{
    QMap<QString, LevelObject> objects = level.getObjects();
    QMap<QString, LevelObject>::Iterator it;

    QMap<QString, int> linkMap;

    int count = objects.count();

    bool **ary = new bool*[count];
    for(int i = 0; i < count; ++i) {
        ary[i] = new bool[count];
    }

    for(int i=0;i<count;++i)
        for(int j=0;j<count;j++)
            ary[i][j] = false;

    int i=0;
    for( it = objects.begin(); it != objects.end(); ++it)
    {
        LevelObject object = (it).value();
        addLevelObject(object.getName(),object.getPosition());
        linkMap[object.getName()] = i;
        ++i;
    }

    for(it = objects.begin(); it != objects.end(); ++it)
    {
        LevelObject object = (it).value();
        foreach(QString link, object.getLinks())
        {
            int source = linkMap[object.getName()];
            int dest = linkMap[link];

            if(!ary[source][dest])
            {
                LevelObject destination = level.getObject(link);

                QPen pen;
                pen.setWidthF(WIDTH_LINE_PEN);
                pen.setColor(COLOR_LINE_PEN);

                QGraphicsLineItem* li = addLine(QLineF(object.getPosition(),destination.getPosition()), pen);
                li->setZValue(0);

                li->setData(UNIQUE_ID, "link:" + object.getName() + ":" + destination.getName());
                li->setFlag(QGraphicsItem::ItemIsSelectable);
                li->setFlag(QGraphicsItem::ItemIsMovable, false);
                li->setFlag(QGraphicsItem::ItemIsFocusable, false);

                m_sceneLinks.push_back(li);

                ary[source][dest] = true;
                ary[dest][source] = true;

                m_items[object.getName()]->addLink(m_items[destination.getName()]);
                m_items[destination.getName()]->addLink(m_items[object.getName()]);
            }
        }
    }

    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"objects", QString::number(m_items.count()));
    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"linksTotal", QString::number(m_sceneLinks.count()));

    qDebug() << "Constructing scene from " << level.getName() ;
    for(int i = 0; i < count; ++i) {
        delete [] ary[i];
    }
    delete [] ary;
}

CustomGraphicsItem* CustomGraphicsScene::addLevelObject(QString identifier, QPoint position)
{
    if (identifier.isEmpty())
    {
        do
        {
            identifier = "orb_" + QString::number(m_idCount);
            m_idCount++;
        }
        while(m_items.find(identifier) != m_items.end());
    }

    CustomGraphicsItem* cgi = new CustomGraphicsItem();
    cgi->initialize(identifier, position);
    cgi->setNodeDisplayMode(m_nodeDisplayMode);
    cgi->setParent(this);

    //add to m_items
    m_items[identifier] = cgi;
    //add to scene
    addItem(cgi);

    return cgi;
}

void CustomGraphicsScene::removeLevelObject(QGraphicsItem* item)
{
    //Remove item in Scene
    //If item is a line
    QString uniqueIdentifier = item->data(UNIQUE_ID).toString();

    if(uniqueIdentifier.contains("link"))
    {
        //Get Nodes
        QString node1 = uniqueIdentifier.split(":")[1];
        QString node2 = uniqueIdentifier.split(":")[2];

        m_items[node1]->removeLink(m_items[node2]);
        m_items[node2]->removeLink(m_items[node1]);

        //Remove Link
        foreach(QGraphicsLineItem* link, m_sceneLinks)
        {
            if(link == item)
            {
                m_sceneLinks.removeOne(link);
                break;
            }
        }
        removeItem(item);

        //Show unsave mark
        LevelEditor::getInstance()->showUnsaveMark();
    }
    else if (uniqueIdentifier.contains("node"))
    {
        //cast to CustomGraphicsItem
        CustomGraphicsItem* node = dynamic_cast<CustomGraphicsItem*>(item);

        //remove its rings
        node->removeRing();

        //remove as ring to other nodes
        foreach(CustomGraphicsItem* other, node->getLinks())
        {
            other->removeLink(node);
        }

        //remove the link line
        foreach(QGraphicsLineItem* link, m_sceneLinks)
        {

            QString uniqueIdentifier = link->data(UNIQUE_ID).toString();
            QRegExp rx("link:" + node->getName() + ":[a-z0-9_]+");
            QRegExp rx2("link:[a-z0-9_]+:" + node->getName());

            if(rx.exactMatch(uniqueIdentifier) || rx2.exactMatch(uniqueIdentifier))
            {
                removeItem(link);
                m_sceneLinks.removeOne(link);
                m_sceneLinks.removeOne(link);
            }
        }
        removeItem(item);

        //Show unsave mark
        LevelEditor::getInstance()->showUnsaveMark();
    }

    //Remove item in layers
    LAYERS()->deleteLayer(item->data(UNIQUE_ID).toString());
    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"objects", QString::number(m_items.count()));
    qDebug() << "Removed: " << item->data(UNIQUE_ID).toString();
}

void CustomGraphicsScene::setNodeDisplayMode()
{
    int mode = (int)m_nodeDisplayMode;
    ++mode %= (int)NODE_DISPLAY_MODES;
    m_nodeDisplayMode = (NodeDisplayMode)mode;

    foreach(CustomGraphicsItem* item, m_items)
    {
        item->setNodeDisplayMode(m_nodeDisplayMode);
        item->removeRing();
        item->addRing();
    }
}

void CustomGraphicsScene::showCartesian(bool show)
{
    if(show)
    {
        line->show();
        line2->show();
        line3->show();
        line4->show();
        return;
    }
    line->hide();
    line2->hide();
    line3->hide();
    line4->hide();
}

void CustomGraphicsScene::removeAllLevelLinks()
{
    QList<QGraphicsItem*> sceneItems = items();

    foreach(QGraphicsItem* sceneItem, sceneItems)
    {
        removeLevelLinks(sceneItem);
    }
}

void CustomGraphicsScene::removeLevelLinks(QGraphicsItem* item)
{
    //Remove item in Scene
    //If item is a line
    QString uniqueIdentifier = item->data(UNIQUE_ID).toString();

    if(uniqueIdentifier.contains("link"))
    {
        //Get Nodes
        QString node1 = uniqueIdentifier.split(":")[1];
        QString node2 = uniqueIdentifier.split(":")[2];

        m_items[node1]->removeLink(m_items[node2]);
        m_items[node2]->removeLink(m_items[node1]);

        //Update Item in CustomTreeWidgetLayers
        LAYERS()->updateLayer("node:" + m_items[node1]->getName(), QString::number(m_items[node1]->getLinks().count()));
        LAYERS()->updateLayer("node:" + m_items[node2]->getName(), QString::number(m_items[node2]->getLinks().count()));

        //Remove Link in m_sceneLinks
        foreach(QGraphicsLineItem* link, m_sceneLinks)
        {
            if(link == item)
            {
                m_sceneLinks.removeOne(link);
                break;
            }
        }

        //Remove QGraphicsLineItem in scene
        removeItem(item);

        //Show unsave mark
        LevelEditor::getInstance()->showUnsaveMark();

        qDebug() << "Removed: " << item->data(UNIQUE_ID).toString();
    }

    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"linksTotal", QString::number(m_sceneLinks.count()));
}

void CustomGraphicsScene::removeAllLevelNodes()
{
    QList<QGraphicsItem*> sceneItems = items();

    foreach(QGraphicsItem* sceneItem, sceneItems)
    {
        removeLevelNodes(sceneItem);
    }
}

void CustomGraphicsScene::removeLevelNodes(QGraphicsItem* item)
{
    //Remove item in Scene
    QString uniqueIdentifier = item->data(UNIQUE_ID).toString();

    if (uniqueIdentifier.contains("node"))
    {
        //cast to CustomGraphicsItem
        CustomGraphicsItem* node = dynamic_cast<CustomGraphicsItem*>(item);

        //remove its rings
        node->removeRing();

        //remove as ring to other nodes
        foreach(CustomGraphicsItem* other, node->getLinks())
        {
            other->removeLink(node);

            //Update Item in CustomTreeWidgetLayers
            LAYERS()->updateLayer("node:" + other->getName(), QString::number(other->getLinks().count()));
        }

        //remove the link line
        foreach(QGraphicsLineItem* link, m_sceneLinks)
        {

            QString uniqueIdentifier = link->data(UNIQUE_ID).toString();
            QRegExp rx("link:" + node->getName() + ":[a-z0-9_]+");
            QRegExp rx2("link:[a-z0-9_]+:" + node->getName());

            if(rx.exactMatch(uniqueIdentifier) || rx2.exactMatch(uniqueIdentifier))
            {
                removeItem(link);
                m_sceneLinks.removeOne(link);
                m_sceneLinks.removeOne(link);
            }
        }
        removeItem(item);

        //delete item from m_items
        QMap<QString, CustomGraphicsItem*>::Iterator it = m_items.begin();
        for(; it != m_items.end(); ++it)
        {
            if(it.value() == node)
            {
                m_items.erase(it);
                break;
            }
        }

        //Remove item in layers
        LAYERS()->deleteLayer(item->data(UNIQUE_ID).toString());

        //Display changes in properties
        PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"objects", QString::number(m_items.count()));
        PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"linksTotal", QString::number(m_sceneLinks.count()));

        //Show unsave mark
        LevelEditor::getInstance()->showUnsaveMark();

        qDebug() << "Removed: " << item->data(UNIQUE_ID).toString();
    }
}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {

    }
    else
    {
        moveConnectionsOnMouseDrag();
    }

    if (m_drawLink && m_connection)
    {
        m_connection->setLine(m_pointFirst.x(), m_pointFirst.y(), event->scenePos().x(),event->scenePos().y());

    }
    //if(m_cursorPos)
    //    m_cursorPos->setPlainText("x,y:(" + QString::number((int)event->scenePos().x()) + "," + QString::number((int)event->scenePos().y()) + ")");
    LevelEditor::getInstance()->setCursorText(event->scenePos().x(), event->scenePos().y());

    update();
    QGraphicsScene::mouseMoveEvent(event);
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


    m_selectedItems = this->items(event->scenePos());
    foreach(QGraphicsItem* item, m_selectedItems)
    {
        if (item->data(UNIQUE_ID).isValid())
        {
            if(item->data(UNIQUE_ID).toString().contains("node"))
            {
                m_selectedItem = dynamic_cast<CustomGraphicsItem*>(item);
                m_selectedItem->setZValue(2);
                break;
            }
            else if(item->data(UNIQUE_ID).toString().contains("link"))
            {

            }
        }
    }

    if (m_selectedItem->data(0).isValid())
    {
        if(m_selectedItem->data(UNIQUE_ID).toString().contains("node"))
            m_pointFirst = QPointF(m_selectedItem->sceneBoundingRect().center());
    }

    //Mouse press to create line
    if (event->button() == Qt::RightButton)
    {
        if (m_selectedItem->data(0).isValid())
        {
            QPen pen;
            pen.setWidth(WIDTH_LINE_PEN);
            pen.setColor(COLOR_LINE_PEN);

            m_connection = addLine(m_pointFirst.x(), m_pointFirst.y(), event->scenePos().x(), event->scenePos().y(), pen);
            m_connection->setZValue(0);
            m_connectionSource = m_selectedItem;
            m_drawLink = true;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //m_selectedItem = dynamic_cast<CustomGraphicsItem*>(itemAt(event->scenePos(), m_gv->transform()));
    m_selectedItems = this->items(event->scenePos());

    foreach(QGraphicsItem* item, m_selectedItems)
    {
        if (item->data(UNIQUE_ID).isValid())
        {
            if(item->data(UNIQUE_ID).toString().contains("node"))
            {
                m_selectedItem = dynamic_cast<CustomGraphicsItem*>(item);
                break;
            }
            else if (item->data(UNIQUE_ID).toString().contains("link"))
            {
                continue;
            }
        }

        m_selectedItem = dynamic_cast<CustomGraphicsItem*>(item);
    }

    //Mouse Release to create line
    if (event->button() == Qt::RightButton)
    {
        if (m_drawLink && m_connection)
        {
            if (m_selectedItem->data(0).isValid())
            {
                //Add connection to source and receiver
                //source should not be the same as selected
                //To Do: only one connection is allowed between two nodes

                if (m_connectionSource != m_selectedItem)
                {
                    if(m_connectionSource->addLink(m_selectedItem))
                    {
                        m_selectedItem->addLink(m_connectionSource);

                        //Assign identifier to line
                        QString lineIdentifier = "link:" + m_connectionSource->getName() + ":" + m_selectedItem->getName();
                        m_connection->setData(UNIQUE_ID, lineIdentifier);
                        m_connection->setFlag(QGraphicsItem::ItemIsSelectable);
                        m_connection->setFlag(QGraphicsItem::ItemIsMovable, false);
                        m_connection->setFlag(QGraphicsItem::ItemIsFocusable, false);

                        //Update connectionSource Item in CustomTreeWidgetLayers
                        LAYERS()->updateLayer("node:" + m_connectionSource->getName(), QString::number(m_connectionSource->getLinks().count()));

                        //Update connectionSource Item in CustomTreeWidgetLayers
                        LAYERS()->updateLayer("node:" + m_selectedItem->getName(), QString::number(m_selectedItem->getLinks().count()));

                        //Show changes in properties
                        PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"objects", QString::number(m_items.count()));

                        //Show unsave mark
                        LevelEditor::getInstance()->showUnsaveMark();
                    }
                    else
                    {
                        removeItem(m_connection);
                    }
                }
            }
            else
            {
                //Add object in graphics scene
                //Add connection to source and receiver
                CustomGraphicsItem* newItem = addLevelObject("", event->scenePos().toPoint());

                if (newItem)
                {
                    QString uniqueIdentifier = newItem->data(UNIQUE_ID).toString();
                    m_connectionSource->addLink(newItem);
                    newItem->addLink(m_connectionSource);

                    //Assign identifier to line
                    QString lineIdentifier = "link:" + m_connectionSource->getName() + ":" + newItem->getName();
                    m_connection->setData(UNIQUE_ID, lineIdentifier);
                    m_connection->setFlag(QGraphicsItem::ItemIsSelectable);
                    m_connection->setFlag(QGraphicsItem::ItemIsMovable, false);
                    m_connection->setFlag(QGraphicsItem::ItemIsFocusable, false);

                    //Update connectionSource Item in CustomTreeWidgetLayers
                    LAYERS()->updateLayer("node:" + m_connectionSource->getName(), QString::number(m_connectionSource->getLinks().count()));

                    //Add Item as layer in CustomTreeWidgetLayers
                    LAYERS()->addLayer(uniqueIdentifier, QString::number(newItem->getLinks().count()));

                    //Show changes in properties
                    PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"objects", QString::number(m_items.count()));

                    //Show unsave mark
                    LevelEditor::getInstance()->showUnsaveMark();
                }

                update();
            }
            m_drawLink = false;
            m_sceneLinks.push_back(m_connection);
        }
    }else
    {
        if(m_selectedItem->data(0).isValid())
        {
            if(m_selectedItem->data(UNIQUE_ID).toString().contains("node"))
                m_selectedItem->setZValue(1);

            if(m_pointFirst != QPointF(m_selectedItem->sceneBoundingRect().center()))
            {
                //Show unsave mark
                LevelEditor::getInstance()->showUnsaveMark();
            }
        }
        {
            PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"objects", QString::number(m_items.count()));
            PROPERTIES()->setContent(CustomTreeWidgetProperties::E_LEVEL,"linksTotal", QString::number(m_sceneLinks.count()));
        }
    }
    m_selectedItem = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void CustomGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case 16777248:  //left shift key
        {
            m_enableSnapping = true;
        }
        break;
        case 16777249 : //left control key
        {

        }
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void CustomGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case 32:
        {
#if !IS_LANDSCAPE
        LevelEditor::getInstance()->getCurrentGraphicsView()->centerOn(160,-240);
#else
        LevelEditor::getInstance()->getGraphicsView()->centerOn(240, -160);
#endif
        }
        break;
        case 16777223:
        {
            QList<QGraphicsItem*> sceneItems = selectedItems();

            foreach(QGraphicsItem* sceneItem, sceneItems)
            {
                removeLevelLinks(sceneItem);
            }

            foreach(QGraphicsItem* sceneItem, sceneItems)
            {
                removeLevelNodes(sceneItem);
            }
        }
        case 16777248:  //right shift key
        {
            m_enableSnapping = false;
        }
        break;
        case 16777249 : //right control key
        {

        }
        break;
    }

    QGraphicsScene::keyReleaseEvent(event);
}

void CustomGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_selectedItem = 0;
    m_selectedItems = this->items(event->scenePos());

    foreach(QGraphicsItem* item, m_selectedItems)
    {
        if (item->data(UNIQUE_ID).isValid())
        {
            if(item->data(UNIQUE_ID).toString().contains("node"))
            {
                m_selectedItem = dynamic_cast<CustomGraphicsItem*>(item);
                break;
            }
            else if (item->data(UNIQUE_ID).toString().contains("link"))
            {
                continue;
            }
        }

        m_selectedItem = dynamic_cast<CustomGraphicsItem*>(item);
    }


    if (!m_selectedItem->data(0).isValid())
    {
        //Add object in graphics scene
        CustomGraphicsItem* newItem = addLevelObject("", event->scenePos().toPoint());

        //Add Item as layer in CustomTreeWidgetLayers
        if(newItem)
        {
            QString uniqueIdentifier = newItem->data(UNIQUE_ID).toString();
            LAYERS()->addLayer(uniqueIdentifier, QString::number(newItem->getLinks().count()));
        }

        update();
    }

    QGraphicsScene::mouseDoubleClickEvent(event);
}

void CustomGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
}

void CustomGraphicsScene::toLevel(Level& level)
{
    level.setName(m_levelName);
    foreach(CustomGraphicsItem* sceneItem, m_items)
    {
        LevelObject lo;
        sceneItem->toLevelObject(lo);
        level.addObject(sceneItem->getName(), lo);
    }
}

void CustomGraphicsScene::clearScene()
{
    clear();
}

void CustomGraphicsScene::moveConnectionsOnMouseDrag()
{
    foreach(QGraphicsItem* item, this->selectedItems())
    {
        if (item->data(UNIQUE_ID).isValid())
        {
            if (!item->data(UNIQUE_ID).toString().contains("node"))
                continue;

            CustomGraphicsItem* gi = dynamic_cast<CustomGraphicsItem*>(item);
            QList<CustomGraphicsItem*> connections = gi->getLinks();
            foreach(CustomGraphicsItem* connection, connections)
            {
                const QString lineIdentifier = QString("link:" + gi->getName() + ":" + connection->getName());
                const QString lineIdentifier2 = QString("link:" + connection->getName() + ":" + gi->getName());

                foreach(QGraphicsLineItem* sceneLine, m_sceneLinks)
                {
                    if(sceneLine->data(0).toString() == lineIdentifier ||
                            sceneLine->data(0).toString() == lineIdentifier2)
                    {
                        QLineF line = QLineF(QPointF(gi->sceneBoundingRect().center()),QPointF(connection->sceneBoundingRect().center()));

                        sceneLine->setLine(line);
                    }
                }
            }
        }
    }
}
