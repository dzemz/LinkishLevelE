#ifndef CUSTOMTREEWIDGETLEVELS_H
#define CUSTOMTREEWIDGETLEVELS_H

#include <QTreeWidget>

class CustomTreeWidgetLevels : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CustomTreeWidgetLevels(QWidget *parent = 0);

    void initialize();
    void connectSignals();

    void refresh();
    void populate();

    bool isPackNameValid(QString);
    bool isLevelNameValid(QString);

    void addPackButtonReleased(QWidget*);
    void removePackButtonReleased();

    void addLevelButtonReleased(QWidget*);
    void removeLevelButtonReleased();

    QTreeWidgetItem* addPackToTree(QString);
    QTreeWidgetItem* addLevelToTree(QTreeWidgetItem*, QString);
private:
    int selectedPack;

signals:
public slots:
    void itemClicked(QTreeWidgetItem *, int);
    void itemDoubleClicked(QTreeWidgetItem *, int);
    void openContextMenu(QPoint);
};

#endif // CUSTOMTREEWIDGETLEVELS_H
