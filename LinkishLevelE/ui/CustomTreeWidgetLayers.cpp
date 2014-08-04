#include "CustomTreeWidgetLayers.h"
#include "CustomGraphicsScene.h"
#include "../LevelEditor.h"
#include <QGraphicsItem>
#include <QGraphicsView>

CustomTreeWidgetLayers::CustomTreeWidgetLayers(QWidget *parent) :
    QTreeWidget(parent)
{

}

void CustomTreeWidgetLayers::initialize()
{
    setObjectName(QStringLiteral("lwObjects"));
    setAlternatingRowColors(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setColumnWidth(0, 150);
    setColumnCount(2);
    QStringList list;
    list << "Objects" << "Links";
    setHeaderLabels(list);

    m_tabWidget = LevelEditor::getInstance()->getCustomTabWigetGraphicsView();

    connectSignals();
}

void CustomTreeWidgetLayers::connectSignals()
{
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(itemClicked(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));
}

void CustomTreeWidgetLayers::addLayer(QString layerName, QString links)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(this);
    item->setIcon(0, QIcon(":icons/images/Soccer Ball.png"));
    item->setText(0, layerName);
    item->setText(1, links);
}

void CustomTreeWidgetLayers::updateLayer(QString layerName, QString links)
{
    QList<QTreeWidgetItem*> items = findItems(layerName,Qt::MatchExactly);
    if(items.size() != 0)
        items[0]->setText(1, links);
}

void CustomTreeWidgetLayers::deleteLayer(QString layerName)
{
    QList<QTreeWidgetItem*> items = findItems(layerName,Qt::MatchExactly);

    if (items.size() != 0)
        delete items[0];
}

void CustomTreeWidgetLayers::itemClicked(QTreeWidgetItem *item, int column)
{
    int index = m_tabWidget->currentIndex();

    QStringList nameList = m_tabWidget->tabText(index).split(".");
    QString levelName = nameList[0];
    CustomGraphicsView* gv = m_tabWidget->currentWidget()->findChild<CustomGraphicsView*>("graphicsView_"+ levelName);

    CustomGraphicsScene* gs;
    QList<QGraphicsItem*> sceneItems;
    //Get graphics scene
    if (gv)
    {
        gs = dynamic_cast<CustomGraphicsScene*>(gv->scene());
        if (gs)
        {
            sceneItems = gs->items();
            foreach(QGraphicsItem* sceneItem, sceneItems)
            {
                if  (item->text(column) == sceneItem->data(UNIQUE_ID).toString())
                    sceneItem->setSelected(true);
                else
                    sceneItem->setSelected(false);

            }
        }
    }
}

void CustomTreeWidgetLayers::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int index = m_tabWidget->currentIndex();

    QStringList nameList = m_tabWidget->tabText(index).split(".");
    QString levelName = nameList[0];
    CustomGraphicsView* gv = m_tabWidget->currentWidget()->findChild<CustomGraphicsView*>("graphicsView_"+ levelName);

    CustomGraphicsScene* gs;
    QList<QGraphicsItem*> sceneItems;

    //Get graphics scene
    if (gv)
    {
        gs = dynamic_cast<CustomGraphicsScene*>(gv->scene());
        if (gs)
        {
            sceneItems = gs->items();
            foreach(QGraphicsItem* sceneItem, sceneItems)
            {
                if  (item->text(column) == sceneItem->data(UNIQUE_ID).toString())
                {
                    sceneItem->setSelected(true);
                    gv->centerOn(sceneItem->sceneBoundingRect().center());
                }
            }
        }
    }
}
