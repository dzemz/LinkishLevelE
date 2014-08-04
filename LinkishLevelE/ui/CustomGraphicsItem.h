#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include "../level/Level.h"
#include <QGraphicsEllipseItem>

class CustomGraphicsItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit CustomGraphicsItem(QObject *parent = 0);

    void initialize(QString, QPointF);

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void setNodeDisplayMode(int mode);

    bool addLink(CustomGraphicsItem*);
    void removeLink(CustomGraphicsItem*);
    void addRing();
    void removeRing();

    void toLevelObject(LevelObject&);

    QString getName() { return m_name; }
    QList<CustomGraphicsItem*>& getLinks() { return m_links; }

private:
    bool m_drag;
    bool m_snapToGrid;
    int m_rings;
    int m_nodeDisplayMode;

    Qt::MouseButton m_mouseButton;
    QPointF m_oldPoint;
    QPointF m_pressPoint;
    QPointF m_diffPoint;
    QString m_name;

    QList<CustomGraphicsItem*> m_links;
signals:
    
public slots:

};

#endif // CUSTOMGRAPHICSITEM_H
