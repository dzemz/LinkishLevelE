#ifndef CUSTOMTREEWIDGETLAYERS_H
#define CUSTOMTREEWIDGETLAYERS_H

#include <QTreeWidget>

class CustomTreeWidgetLayers : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CustomTreeWidgetLayers(QWidget *parent = 0);
    
    void initialize();
    void connectSignals();
    void addLayer(QString layerName, QString links="0");
    void updateLayer(QString layerName, QString links = "0");
    void deleteLayer(QString layerName);

private:
    QTabWidget* m_tabWidget;
signals:
    
public slots:
    void itemClicked(QTreeWidgetItem *item, int column);
    void itemDoubleClicked(QTreeWidgetItem *item, int column);
};

#endif // CUSTOMTREEWIDGETLAYERS_H
