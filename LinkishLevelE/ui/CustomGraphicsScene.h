#ifndef LEGRAPHICSSCENE_H
#define LEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "CustomGraphicsView.h"
#include "CustomGraphicsItem.h"
#include "../level/Level.h"

#define ADJUST_OBJECT_RECT          5
#define ADJUST_OBJECT_RECT_CHILD    7

#define SIZE_OBJECT_TEXT_BASE              8

#define WIDTH_OBJECT_PEN            2
#define WIDTH_OBJECT_PEN_CHILD      2
#define WIDTH_LINE_PEN              2
//#define COLOR_OBJECT_PEN          QColor(56,93,157)
#define COLOR_OBJECT_PEN            QColor(Qt::white)
#define COLOR_OBJECT_PEN_CHILD      QColor(56,93,157)
#define COLOR_OBJECT_TEXT           QColor(157,37,27)
//#define COLOR_OBJECT_BRUSH        QColor(79,129,188)
#define COLOR_OBJECT_BRUSH          QColor(Qt::white)
//#define COLOR_LINE_PEN            QColor(79,129,188)
#define COLOR_LINE_PEN              QColor(Qt::white)
#define RECT_OBJECT_START           10
#define SCENE_GRID_X                10
#define SCENE_GRID_Y                10

typedef enum E_ITEM_DATA
{
    UNIQUE_ID = 0
} ItemData;

typedef enum E_NODE_DISPLAY_MODE
{
    NODE_NUMBERS,
    NODE_RINGS,
    NODE_DISPLAY_MODES
} NodeDisplayMode;

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomGraphicsScene(QWidget *parent = 0);

    void initialize(QString, QString);
    CustomGraphicsItem* addLevelObject(QString identifier = "", QPoint position = QPoint(0,0));

    void setNodeDisplayMode();
    void showCartesian(bool show = true);

    void removeLevelObject(QGraphicsItem*);
    void removeAllLevelLinks();
    void removeLevelLinks(QGraphicsItem*);
    void removeAllLevelNodes();
    void removeLevelNodes(QGraphicsItem*);

    void constructSceneFromLevel(Level&);

    void sceneRectChanged(const QRectF &rect);

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

    void toLevel(Level&);
    void clearScene();
    void moveConnectionsOnMouseDrag();

    void setLevelName(QString levelName) { m_levelName = levelName; }
    QString getLevelName() { return m_levelName; }
    void setPackName(QString packName) { m_packName = packName; }
    QString getPackName() { return m_packName; }

    void setView(CustomGraphicsView* gv);
private:
    bool m_enableSnapping;
    bool m_drawLink;
    int m_idCount;

    NodeDisplayMode m_nodeDisplayMode;

    QString m_levelName;
    QString m_packName;

    QPointF m_pointFirst;

    QGraphicsLineItem *line;
    QGraphicsLineItem *line2;
    QGraphicsLineItem* line3;
    QGraphicsLineItem* line4;

    QGraphicsLineItem* m_connection;
    QGraphicsTextItem* m_cursorPos;
    CustomGraphicsView* m_gv;

    CustomGraphicsItem* m_connectionSource;
    CustomGraphicsItem* m_selectedItem;

    QList<QGraphicsItem*> m_selectedItems;

    QList<QGraphicsLineItem*> m_sceneLinks;
    QMap<QString, CustomGraphicsItem*> m_items;
    QList<QGraphicsLineItem*> m_sceneGrids;
signals:
    
public slots:
    
};

#endif // LEGRAPHICSSCENE_H
