#ifndef CUSTOMTREEWIDGETPROPERTIES_H
#define CUSTOMTREEWIDGETPROPERTIES_H

#include "../level/Level.h"
#include <QTreeWidget>

class CustomTreeWidgetProperties : public QTreeWidget
{

    Q_OBJECT
public:
    typedef enum PropertyType
    {
        E_NODES,
        E_LEVEL
    }PropertyType;

    explicit CustomTreeWidgetProperties(QWidget *parent = 0);
    void initialize();
    void setContent(PropertyType, QString, QString);
    void setContent(QStringList, QStringList);
private:
    PropertyType m_currentType;

signals:
    
public slots:
    
};

#endif // CUSTOMTREEWIDGETPROPERTIES_H
