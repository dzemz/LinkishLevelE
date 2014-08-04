#include "CustomDialogGallery.h"
#include "../LevelEditor.h"

#include <QBoxLayout>
#include <QTreeWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

CustomDialogGallery::CustomDialogGallery(QWidget* parent) : QDialog(parent)
{

}

void CustomDialogGallery::initialize()
{
    setWindowFlags(windowFlags() | Qt::Widget | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    setWindowTitle("Level Gallery");

    setGeometry(250, 50, 640 + 300, 650);

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout->setMargin(0);

    m_treeWidget = new QTreeWidget();
    m_treeWidget->setColumnCount(1);
    m_treeWidget->setAlternatingRowColors(true);

    QStringList list;
    list << "Packs";
    m_treeWidget->setHeaderLabels(list);

    layout->addWidget(m_treeWidget);

    m_gv = new QGraphicsView();
    layout->addWidget(m_gv);

    QGraphicsScene* gs = new QGraphicsScene();
    gs->setSceneRect(5, 5, 1240, 1240);

    m_gv->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_gv->setDragMode(QGraphicsView::ScrollHandDrag);

    m_gv->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing);

    m_gv->setBackgroundBrush(QBrush(Qt::gray));
    m_gv->setScene(gs);
    m_gv->centerOn(0,0);
    layout->setStretch(0, 0);
    layout->setStretch(1, 1);

    connectSignals();
}

void CustomDialogGallery::connectSignals()
{
    connect(m_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));
}

void CustomDialogGallery::refresh()
{
    m_treeWidget->clear();
    m_gv->scene()->clear();

    QMap<QString, LevelPack> packs = LevelEditor::getInstance()->getPacks();
    QMap<QString, LevelPack>::Iterator it = packs.begin();

    for(; it != packs.end(); ++it)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(m_treeWidget);
        item->setText(0, it.key() + ".pak");
    }
}

void CustomDialogGallery::itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    m_gv->scene()->clear();
    m_gv->scene()->update();
    m_gv->update();
    drawImagesInPack(item->text(0));
}

void CustomDialogGallery::drawImagesInPack(QString packName)
{
    QString pack = packName.split(".")[0];
    QString dir = "data/levels_screenies/" + pack;

    if(QDir(dir).exists())
    {
        QStringList images = QDir(dir).entryList(QStringList("*.png"), QDir::Files, QDir::Name);

        for(int i=0; i<images.length(); ++i)
        {
            for(int j=0; j<images.length()-1; ++j)
            {
                if(images[j].length() > images[j+1].length())
                {
                    QString temp = images[j+1];
                    images[j+1] = images[j];
                    images[j] = temp;
                }
            }
        }

        int column = 0;
        int row = 0;
        foreach(QString image, images)
        {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
            item->setPixmap(QPixmap(dir + "/" + image));
            item->setZValue(-1);
            item->setOpacity(1);
            //item->setScale(0.4);

            if(column == 8)
            {
                column = 0;
                row++;
            }
            item->setPos(item->sceneBoundingRect().width() * column + (5*column), item->sceneBoundingRect().height() * row + (5*row));

            column++;

            m_gv->scene()->addItem(item);
        }
    }
}
