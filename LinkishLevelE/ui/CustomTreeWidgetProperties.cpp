#include "CustomTreeWidgetProperties.h"
#include <QDebug>

CustomTreeWidgetProperties::CustomTreeWidgetProperties(QWidget *parent) :
    QTreeWidget(parent)
{

}

void CustomTreeWidgetProperties::initialize()
{
    setObjectName(QStringLiteral("treeWidgetProperties"));
    setAlternatingRowColors(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setColumnCount(2);    
    setColumnWidth(0, 150);
    QStringList list;
    list << "Property" << "Value";
    setHeaderLabels(list);

    m_currentType = PropertyType(-1);


}

void CustomTreeWidgetProperties::setContent(PropertyType type, QString property, QString value)
{
    if(m_currentType != type)
    {
        this->clear();
        if(type == E_NODES)
        {
            QTreeWidgetItem* position = new QTreeWidgetItem(this);
            position->setText(0, "position");
            position->setText(1, "(0,0)");
            QTreeWidgetItem* links = new QTreeWidgetItem(this);
            links->setText(0, "links");
            links->setText(1, "0");
        } else if (type == E_LEVEL)
        {
            QTreeWidgetItem* objects = new QTreeWidgetItem(this);
            objects->setText(0, "objects");
            objects->setText(1, "0");
            QTreeWidgetItem* links = new QTreeWidgetItem(this);
            links->setText(0, "linksTotal");
            links->setText(1, "0");
        }

        m_currentType = type;
    }

    for( int i = 0; i < topLevelItemCount(); ++i )
    {
       QTreeWidgetItem *item = topLevelItem( i );
       if(item->text(0) == property)
           item->setText(1, value);
    }
}

void CustomTreeWidgetProperties::setContent(QStringList properties, QStringList values)
{

}
