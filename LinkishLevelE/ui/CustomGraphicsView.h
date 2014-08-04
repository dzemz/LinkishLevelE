#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

#define SCALE_CAP_TOP 2
#define SCALE_CAP_BOTTOM 0.02

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomGraphicsView(QWidget *parent = 0);
    
    void initialize(QString packName, QString levelName);

    void wheelEvent(QWheelEvent *event);
signals:
    
public slots:
    
};

#endif // CUSTOMGRAPHICSVIEW_H
