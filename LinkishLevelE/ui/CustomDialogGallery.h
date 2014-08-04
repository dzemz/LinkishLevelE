#ifndef CUSTOMDIALOGGALLERY_H
#define CUSTOMDIALOGGALLERY_H

#include <QDialog>
#include <QTreeWidget>
#include <QGraphicsView>

class CustomDialogGallery : public QDialog
{
    Q_OBJECT

public:
    CustomDialogGallery(QWidget* parent = 0);

    void initialize();
    void connectSignals();
    void refresh();
    void drawImagesInPack(QString);

private:
    QTreeWidget* m_treeWidget;
    QGraphicsView* m_gv;

public slots:
    void itemDoubleClicked(QTreeWidgetItem*, int);
};

#endif // CUSTOMDIALOGGALLERY_H
