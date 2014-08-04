#include "CustomGraphicsView.h"
#include "../LevelEditor.h"

#include <QWheelEvent>
#include <QDebug>

CustomGraphicsView::CustomGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void CustomGraphicsView::initialize(QString packName, QString levelName)
{
    setObjectName("graphicsView_"+ levelName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setDragMode(QGraphicsView::RubberBandDrag);
    setTransform(QTransform::fromScale(1,1));
    setMouseTracking(true);
    setBackgroundBrush(QBrush(QImage(":images/Background.png")));
    centerOn(0,0);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing);

}

void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal scale = transform().m11();
    if(event->angleDelta().y() > 0)
    {
        scale += .1;
        if(scale > SCALE_CAP_TOP)
            scale = SCALE_CAP_TOP;
    } else
    {
        scale -= .1;
        if(scale < SCALE_CAP_BOTTOM)
            scale = SCALE_CAP_BOTTOM;

    }

    setTransform(QTransform::fromScale(scale,scale));

    LevelEditor::getInstance()->getZoomSlider()->setValue(scale * 50);
}
