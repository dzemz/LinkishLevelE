#include "LevelEditor.h"
#include "ui_leveleditor.h"

#include "ui/CustomGraphicsView.h"
#include "ui/CustomTreeWidgetLayers.h"

#include <QToolButton>
#include <algorithm>
#include <QGraphicsView>
#include <QMessageBox>
#include <QToolBar>
#include <QSlider>
#include <QLabel>

static LevelEditor* mw = 0;

LevelEditor::LevelEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelEditor)
{
    ui->setupUi(this);
    mw = this;
}

LevelEditor* LevelEditor::getInstance()
{
    return mw;
}

LevelEditor::~LevelEditor()
{
    delete ui;
}

void LevelEditor::initialize()
{
    createFolders();
    loadFonts();
    setupMenubar();
    setupToolbar();
    setupProperties();
    setupLevels();
    setupGraphicsScene();
    setupGraphicsView();
    setupLayers();
    setupStatusBar();
    connectSignals();
}

void LevelEditor::createFolders()
{
    if(!QDir("data").exists())
        QDir().mkdir("data");
    if(!QDir("data/levels").exists())
        QDir("data").mkdir("levels");
    if(!QDir("data/levels_screenies").exists())
        QDir("data").mkdir("levels_screenies");
}

void LevelEditor::loadFonts()
{
    QFontDatabase fontDatabase;
    fontDatabase.addApplicationFont(":/fonts/RAZER.ttf");
    fontDatabase.addApplicationFont(":/fonts/RAZEROBLIQUE.ttf");
    fontDatabase.families();
}

void LevelEditor::setupMenubar()
{

}

void LevelEditor::setupToolbar()
{

}

void LevelEditor::setupProperties()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, ui->tabwidgetProperties->widget(0));
    layout->setMargin(0);
    m_customTreeWidgetProperties = new CustomTreeWidgetProperties();
    m_customTreeWidgetProperties->initialize();
    layout->addWidget(m_customTreeWidgetProperties);
}

void LevelEditor::setupLayers()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, ui->tabwidgetLayers->widget(0));
    layout->setMargin(0);
    m_customTreeWidgetLayers = new CustomTreeWidgetLayers();
    m_customTreeWidgetLayers->initialize();
    layout->addWidget(m_customTreeWidgetLayers);
}

void LevelEditor::setupLevels()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, ui->widgetLevels);
    layout->setMargin(0);
    layout->setSpacing(0);

    QToolBar* levelToolBar = new QToolBar();
    levelToolBar->setOrientation(Qt::Vertical);
    levelToolBar->setMovable(false);

    m_addPack = new QAction(this);
    m_addPack->setIcon(QIcon(":icons/images/Inbox Full.png"));
    m_addPack->setToolTip("Add Pack");
    levelToolBar->addAction(m_addPack);

    m_removePack = new QAction(this);
    m_removePack->setIcon(QIcon(":icons/images/Inbox.png"));
    m_removePack->setToolTip("Remove Pack");
    levelToolBar->addAction(m_removePack);

    levelToolBar->addSeparator();

    m_addLevel = new QAction(this);
    m_addLevel->setIcon(QIcon(":icons/images/Note-Add.png"));
    m_addLevel->setToolTip("Add Level");
    levelToolBar->addAction(m_addLevel);

    m_removeLevel = new QAction(this);
    m_removeLevel->setIcon(QIcon(":icons/images/Note-Remove.png"));
    m_removeLevel->setToolTip("Remove Level");
    levelToolBar->addAction(m_removeLevel);

    levelToolBar->addSeparator();

    m_expandAll = new QAction(this);
    m_expandAll->setIcon(QIcon(":icons/images/Node Select All.png"));
    m_expandAll->setToolTip("Expand All");
    levelToolBar->addAction(m_expandAll);

    m_collapseAll = new QAction(this);
    m_collapseAll->setIcon(QIcon(":icons/images/Node Select.png"));
    m_collapseAll->setToolTip("Collapse All");
    levelToolBar->addAction(m_collapseAll);

    levelToolBar->addSeparator();

    m_openGallery = new QAction(this);
    m_openGallery->setIcon(QIcon(":icons/images/Images.png"));
    m_openGallery->setToolTip("Open Gallery");

    m_openGallery->setEnabled(false);
    levelToolBar->addAction(m_openGallery);

    layout->addWidget(levelToolBar);

    m_customTreeWidgetLevels = new CustomTreeWidgetLevels();
    layout->addWidget(m_customTreeWidgetLevels);
    m_customTreeWidgetLevels->populate();
}

void LevelEditor::setupGraphicsView()
{
    m_tabWidgetGraphicsView = ui->tabWidgetGraphicsView;

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, ui->widgetToolbar);
    layout->setMargin(0);
    layout->setSpacing(0);

    QToolBar* levelToolBar = new QToolBar();
    levelToolBar->setOrientation(Qt::Horizontal);
    levelToolBar->setMovable(false);
    levelToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    levelToolBar->addWidget(spacer);

    m_nodeRingsNum = new QAction(this);
    m_nodeRingsNum->setText("Number/Rings");
    levelToolBar->addAction(m_nodeRingsNum);

    m_clearConnections = new QAction(this);
    m_clearConnections->setText("Clear Connections");

    levelToolBar->addAction(m_clearConnections);
    levelToolBar->addSeparator();

    m_clearLevel = new QAction(this);
    m_clearLevel->setText("Clear Level");
    levelToolBar->addAction(m_clearLevel);

    m_saveLevel = new QAction(this);
    m_saveLevel->setText("Save Level");
    levelToolBar->addAction(m_saveLevel);

    m_playLevel = new QAction(this);
    m_playLevel->setText("Play Level");

    levelToolBar->addAction(m_playLevel);
    levelToolBar->addSeparator();

    m_screenCap = new QAction(this);
    m_screenCap->setText("Screen Capture");

    levelToolBar->addAction(m_screenCap);
    levelToolBar->addSeparator();

    QAction* m_zoom = new QAction(this);
    m_zoom->setText("Zoom");

    levelToolBar->addAction(m_zoom);

    m_hSlider = new QSlider();
    m_hSlider->setOrientation(Qt::Horizontal);
    m_hSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_hSlider->setValue(50);
    m_hSlider->setPageStep(10);
    m_hSlider->setSingleStep(10);
    m_hSlider->setTickInterval(10);
    m_hSlider->setMaximum(100);
    m_hSlider->setMinimum(1);
    m_hSlider->setTickPosition(QSlider::TicksBelow);
    levelToolBar->addWidget(m_hSlider);

    levelToolBar->addSeparator();

    m_cursor = new QLabel(this);
    m_cursor->setText("   0,0");
    m_cursor->setMinimumWidth(100);
    levelToolBar->addWidget(m_cursor);

    QWidget* spacer2 = new QWidget();
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    levelToolBar->addWidget(spacer2);
    layout->addWidget(levelToolBar);
}

void LevelEditor::setupGraphicsScene()
{
    QGraphicsView *gv = ui->graphicsviewLevel;

    m_customGraphicsScene = new CustomGraphicsScene(this);

    m_customGraphicsScene->setSceneRect(0,0,0,0);

    gv->setBackgroundBrush(QBrush(QImage(":images/Background.png")));
    gv->setScene(m_customGraphicsScene);
    gv->centerOn(0,0);
    gv->setInteractive(false);
    gv->setDragMode(QGraphicsView::NoDrag);
}

void LevelEditor::setupStatusBar()
{
    m_statusBar = ui->statusBar;
}

void LevelEditor::connectSignals()
{
    //add/remove packs
    connect(m_addPack, SIGNAL(triggered()), SLOT(addPackButtonReleased()));
    connect(m_removePack, SIGNAL(triggered()), SLOT(removePackButtonReleased()));

    //add/remove levels
    connect(m_addLevel, SIGNAL(triggered()), SLOT(addLevelButtonReleased()));
    connect(m_removeLevel, SIGNAL(triggered()), SLOT(removeLevelButtonReleased()));

    //expand/collapse
    connect(m_expandAll, SIGNAL(triggered()), SLOT(expandAllButtonReleased()));
    connect(m_collapseAll, SIGNAL(triggered()), SLOT(collapseAllButtonReleased()));

    //open gallery
    connect(m_openGallery, SIGNAL(triggered()), SLOT(openGalleryButtonReleased()));

    //tab widget events
    connect(m_tabWidgetGraphicsView, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
    connect(m_tabWidgetGraphicsView, SIGNAL(tabCloseRequested(int)), this, SLOT(closeLevel(int)));

    //graphics view events
    connect(m_nodeRingsNum, SIGNAL(triggered()), this, SLOT(setNodeDisplayMode()));

    connect(m_clearConnections, SIGNAL(triggered()), this, SLOT(clearLevelConnections()));
    connect(m_clearLevel, SIGNAL(triggered()), this, SLOT(clearLevel()));
    connect(m_saveLevel, SIGNAL(triggered()), this, SLOT(saveLevel()));
    connect(m_playLevel, SIGNAL(triggered()), this, SLOT(playLevel()));
    connect(m_screenCap, SIGNAL(triggered()), this, SLOT(exportLevelToImageAtIndex()));
    connect(m_hSlider, SIGNAL(sliderMoved(int)), this, SLOT(zoomLevel(int)));
    connect(m_hSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomLevel(int)));

    //file menu
    connect(ui->actionNew_Level, SIGNAL(triggered()), this, SLOT(newLevel()));
    connect(ui->actionNew_Pack, SIGNAL(triggered()), this, SLOT(newPack()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveLevel()));
    connect(ui->actionSave_All, SIGNAL(triggered()), this, SLOT(saveAllLevels()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeLevel()));
    connect(ui->actionClose_All, SIGNAL(triggered()), this, SLOT(closeAllLevels()));
    connect(ui->actionClose_Others, SIGNAL(triggered()), this, SLOT(closeOtherLevels()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quitEditor()));

    //edit menu
    connect(ui->actionSelect_All, SIGNAL(triggered(bool)), this, SLOT(selectAllObjects()));
    //level menu
    connect(ui->actionClear_Connections, SIGNAL(triggered()), this, SLOT(clearLevelConnections()));
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearLevel()));
    connect(ui->actionPlay, SIGNAL(triggered()), this, SLOT(playLevel()));

    //window menu
    connect(ui->actionLevel_Library, SIGNAL(triggered(bool)), this, SLOT(showLevelLibrary(bool)));
    connect(ui->actionLevel_Properties, SIGNAL(triggered(bool)), this, SLOT(showLevelProperties(bool)));

    connect(ui->dockWidgetLevelBrowser, SIGNAL(visibilityChanged(bool)), this, SLOT(visibilityChangedDockWidgetLevelBrowser(bool)));
    connect(ui->dockwidgetLayers, SIGNAL(visibilityChanged(bool)), this, SLOT(visibilityChangedDockWidgetLayers(bool)));
}


void LevelEditor::setStatusBarMessage(QString message)
{
    m_statusBar->showMessage(message);
}

void LevelEditor::resetStatusBarMessage(QString message)
{
    message = "Ready";
    m_statusBar->showMessage(message);
}

CustomGraphicsView* LevelEditor::getCurrentGraphicsView()
{
    QString levelName = m_tabWidgetGraphicsView->tabText(m_tabWidgetGraphicsView->currentIndex());
    QString level = levelName.split(".")[0];

    return m_tabWidgetGraphicsView->currentWidget()->findChild<CustomGraphicsView*>("graphicsView_"+ level);
}

CustomGraphicsScene* LevelEditor::getCurrentScene()
{
    CustomGraphicsView* gv = getCurrentGraphicsView();
    if(gv)
        return dynamic_cast<CustomGraphicsScene*>(getCurrentGraphicsView()->scene());
    return 0;
}

bool LevelEditor::addLevelPack(QString packName)
{
    LevelPack pack;
    m_packs[packName] = pack;

    if(!QDir("data/levels/"+packName).exists())
        QDir("data/levels").mkdir(packName);

    return true;
}

bool LevelEditor::removeLevelPack(QString packName)
{
    QString pack = packName.split(".")[0];

    //delete all levels from pack
    QMap<QString, Level> levels = m_packs[pack].getLevels();
    QMap<QString, Level>::Iterator it = levels.begin();

    for(;it != levels.end(); ++it)
        removeLevel(packName,it.key() + ".lvl");

    //delete pack from m_packs
    QMap<QString, LevelPack>::Iterator it2 = m_packs.begin();
    for(; it2 != m_packs.end(); ++it2)
    {
        if(it2.key() == pack)
        {
            m_packs.erase(it2);
            break;
        }
    }

    //delete directory
    bool ret = QDir("data/levels/"+pack).removeRecursively();
    if(!ret)
    {
        QMessageBox::warning(this, tr("Level Editor"), "Error deleting directory.", QMessageBox::Ok);
        return false;
    }

    return true;
}

bool LevelEditor::renameLevelPack(QString oldName, QString newName)
{
    QString oldPack = oldName.split(".")[0];
    QString newPack = newName.split(".")[0];

    if(!packExists(newName))
    {
        for(int i=0; i<m_tabWidgetGraphicsView->count(); ++i)
        {
            if(m_tabWidgetGraphicsView->tabText(i).startsWith(oldPack + "_"))
            {
                closeLevel(i);
            }
        }

        //Rename directory


        bool ret = QDir("data/levels").rename(oldPack,newPack);

        bool ret2 = false;



        QStringList list = QDir("data/levels/" + newPack).entryList(QStringList("*.lvl"), QDir::Files, QDir::Name);

        foreach(QString levelName, list)
        {
            QString temp = levelName.mid(oldPack.length());
            ret2 = QDir("data/levels/"+newPack).rename(levelName, newPack + temp);

            if (!ret2)
                break;
        }

        if(!ret)
        {
            QMessageBox::warning(this, tr("Level Editor"), "Error renaming directory", QMessageBox::Ok);
            return false;
        }

        if(!ret2)
        {
            QMessageBox::warning(this, tr("Level Editor"), "Error renaming file", QMessageBox::Ok);
            return false;
        }



        //Rename in m_packs
        QMap<QString, LevelPack>::Iterator it = m_packs.begin();
        for(;it != m_packs.end(); ++it)
        {
            if (it.key() == oldPack)
            {
                m_packs[newPack] = it.value();
                m_packs[newPack].setName(newPack);
                m_packs.erase(it);
                break;
            }
        }

        m_packs[newPack].renameLevels(oldPack, newPack);

        return true;
    }
    else
    {
       QMessageBox::warning(this, tr("Level Editor"), newName + " is already taken.", QMessageBox::Ok);
    }
    return false;
}

bool LevelEditor::exportToImage(QString packName, QString levelName)
{
    QString pack = packName.split(".")[0];
    QString level = levelName.split(".")[0];

    QMap<QString, Level> levels;
    if(levelName == "")
    {
       levels = m_packs[pack].getLevels();
    } else
    {
        Level l = m_packs[pack].getLevel(level);
        levels[level] = l;
    }

    QMap<QString, Level>::Iterator it = levels.begin();

    for(; it != levels.end(); ++it)
    {
        level = it.value().getName();

        CustomGraphicsView* gv = new CustomGraphicsView();
        gv->initialize(pack, level);

        CustomGraphicsScene* gs = new CustomGraphicsScene(gv);
        gs->initialize(pack, level);
        gs->setSceneRect(0,0,320,480);

        Level l = LevelEditor::getInstance()->getLevel(pack, level);

        gs->constructSceneFromLevel(l);
        gv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gv->setScene(gs);
        gs->showCartesian(false);

        if(!QDir("data/levels_screenies/" + pack).exists())
            QDir("data/levels_screenies").mkdir(pack);

        if(QDir("data/levels_screenies/" + pack).exists())
        {
            QPixmap pix = gv->grab(QRect(1,1,320, 480));
            //pix = pix.scaled(QSize(120, 180));
            bool ret = pix.save("data/levels_screenies/" + pack + "/" + level + ".png", "PNG", 50);
            if(ret)
                setStatusBarMessage("Screen capture success");
            else
                setStatusBarMessage("Screen capture failed");
        }

        gs->showCartesian(true);

        gs->clear();
        delete gs;
        delete gv;

    }

    return true;
}

bool LevelEditor::addLevelToLevelPack(QString packName, QString levelName, bool fromFile)
{
    bool ret = true;
    Level level;

    if(fromFile)
        ret = level.fromFile("data/levels/"+packName+"/"+levelName);

    level.setName(levelName.split(".")[0]);

    if (ret)
        m_packs[packName].addLevel(level);

    return ret;
}

bool LevelEditor::addLevelTab(QString packName, QString levelName)
{
    for(int i=0; i<m_tabWidgetGraphicsView->count(); ++i)
    {
        if(m_tabWidgetGraphicsView->tabText(i) == levelName)
        {
            m_tabWidgetGraphicsView->setCurrentIndex(i);
            return true;
        }
    }

    QStringList nameList = levelName.split(".");
    QString name = nameList[0];

    nameList = packName.split(".");
    QString pack = nameList[0];

    QWidget* newTab = new QWidget(m_tabWidgetGraphicsView);
    newTab->setAttribute(Qt::WA_DeleteOnClose, true);
    newTab->setObjectName(pack+ ":" + name);

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, newTab);
    layout->setMargin(0);

    CustomGraphicsView* customGraphicsView = new CustomGraphicsView();
    customGraphicsView->initialize(pack, name);

    CustomGraphicsScene* customGraphicsScene = new CustomGraphicsScene(customGraphicsView);
    customGraphicsScene->initialize(pack, name);

    qDebug() << pack << name;
    Level l = LevelEditor::getInstance()->getLevel(pack,name);
    customGraphicsScene->constructSceneFromLevel(l);

    customGraphicsView->setScene(customGraphicsScene);
    customGraphicsScene->setView(customGraphicsView);

    layout->addWidget(customGraphicsView);

    if (m_tabWidgetGraphicsView->addTab(newTab, levelName) >= 0 )
    {
        if (m_tabWidgetGraphicsView->tabText(0) == "")
            m_tabWidgetGraphicsView->removeTab(0);
        m_tabWidgetGraphicsView->setCurrentWidget(newTab);
        m_tabWidgetGraphicsView->setTabsClosable(true);

        return true;
    }

    return false;
}

//Signals
void LevelEditor::addPackButtonReleased()
{
    m_customTreeWidgetLevels->addPackButtonReleased(this);
}

void LevelEditor::removePackButtonReleased()
{
    m_customTreeWidgetLevels->removePackButtonReleased();
}

void LevelEditor::addLevelButtonReleased()
{
    m_customTreeWidgetLevels->addLevelButtonReleased(this);
}

void LevelEditor::removeLevelButtonReleased()
{
    m_customTreeWidgetLevels->removeLevelButtonReleased();
}

void LevelEditor::expandAllButtonReleased()
{
    m_customTreeWidgetLevels->expandAll();
}

void LevelEditor::collapseAllButtonReleased()
{
    m_customTreeWidgetLevels->collapseAll();
}

void LevelEditor::openGalleryButtonReleased()
{
    if(!m_customDialogGallery)
    {
        m_customDialogGallery = new CustomDialogGallery();
        m_customDialogGallery->initialize();

    } else
    {
        m_customDialogGallery->raise();
    }

    m_customDialogGallery->refresh();
    m_customDialogGallery->show();

    m_customDialogGallery->setFocus();
}

void LevelEditor::currentTabChanged(int index)
{
    QStringList nameList = m_tabWidgetGraphicsView->tabText(index).split(".");
    QString levelName = nameList[0];
    QGraphicsView* gv = m_tabWidgetGraphicsView->currentWidget()->findChild<QGraphicsView*>("graphicsView_"+ levelName);

    CustomGraphicsScene* gs;
    QList<QGraphicsItem*> sceneItems;
    QList<QString> sceneItemNames;
    QList<int> sceneItemLinks;

    //Get graphics scene
    if (gv)
    {
        //set zoom value
        m_hSlider->setValue(gv->transform().m11() * 50);

        gs = dynamic_cast<CustomGraphicsScene*>(gv->scene());
        if (gs)
        {
            sceneItems = gs->items();
            foreach(QGraphicsItem* sceneItem, sceneItems)
            {
                if(sceneItem->data(UNIQUE_ID).isValid())
                {
                    QString data = sceneItem->data(UNIQUE_ID).toString();
                    if(data.contains("node"))
                    {
                        CustomGraphicsItem* item = dynamic_cast<CustomGraphicsItem*>(sceneItem);
                        QString layerName = data + ":" + QString::number(item->getLinks().count());
                        sceneItemNames << layerName;
                    }
                }
            }
        }
    }

    //Clear Items in Layers
    LevelEditor::getInstance()->getCustomTreeWidgetLayer()->clear();

    //Add Items to Layers
    qSort(sceneItemNames);
    foreach(QString sceneItemName, sceneItemNames)
    {
        QString temp = sceneItemName;
        QStringList tempList = temp.split(":");
        QString name = tempList[0] + ":" + tempList[1];
        LevelEditor::getInstance()->getCustomTreeWidgetLayer()->addLayer(name,tempList[2]);
    }
}

bool LevelEditor::addLevel(QString packName, QString levelName)
{
    QString pack = packName.split(".")[0];
    QString level = (levelName.split("."))[0];
    if (!levelExists(pack, level))
    {
        QFile file("data/levels/"+pack+"/"+levelName);
        bool ret = file.open(QIODevice::ReadWrite);
        if(!ret)
        {
            QMessageBox::warning(this, tr("Level Editor"), "Error creating file.", QMessageBox::Ok);
            return false;
        }
        file.close();

        addLevelToLevelPack(packName,levelName);
        addLevelTab(packName, levelName);
        return true;
    }
    else
    {
        QMessageBox::warning(this, tr("Level Editor"), levelName + " is already taken.", QMessageBox::Ok);
    }


    return false;
}

bool LevelEditor::removeLevel(QString packName, QString levelName)
{
    QString pack = packName.split(".")[0];
    QString level = (levelName.split("."))[0];

    //remove dir
    int ret = QDir("data/levels/"+pack).remove(levelName);
    if(!ret)
    {
        QMessageBox::warning(this, tr("Level Editor"), "Error deleting file", QMessageBox::Ok);
        return false;
    }

    //remove level in packs
    m_packs[pack].removeLevel(level);

    //check if level tab is open
    int tabIndex = -1;
    for(int i=0; i<m_tabWidgetGraphicsView->count(); ++i) {
        if(m_tabWidgetGraphicsView->tabText(i) == levelName)
        {
            tabIndex = i;
            break;
        }
    }

    //remove graphics view, graphics scene
    if(tabIndex>-1)
    {
        QGraphicsView* gv = m_tabWidgetGraphicsView->widget(tabIndex)->findChild<QGraphicsView*>("graphicsView_"+ level);

        QGraphicsScene* gs = gv->scene();
        gs->clear();
        delete gs;
        delete gv;
    }

    //remove level tab
    if(tabIndex > -1)
        m_tabWidgetGraphicsView->widget(tabIndex)->close();

    setStatusBarMessage(levelName + "... Removed");
    return true;
}

bool LevelEditor::renameLevel(QString packName, QString oldName, QString newName)
{
    QString pack = packName.split(".")[0];
    QString oldLevel = oldName.split(".")[0];
    QString newLevel = newName.split(".")[0];

    if(!levelExists(pack, newName))
    {
        //rename in directory
        bool ret = QDir("data/levels/"+pack).rename(oldName,newName);
        if (!ret)
        {
            QMessageBox::warning(this, tr("Level Editor"), "Error renaming file", QMessageBox::Ok);
            return false;
        }

        //rename in levelpack
        //Rename in m_packs
        m_packs[pack].renameLevel(oldLevel,newLevel);

        //rename tab, graphicsView, graphicsScene if it is opened
        QString tabName = pack+":"+oldLevel;
        QWidget* tab = m_tabWidgetGraphicsView->findChild<QWidget*>(tabName);
        if (tab)
        {
            int thisTabIndex = m_tabWidgetGraphicsView->indexOf(tab);

            QGraphicsView* gv = tab->findChild<QGraphicsView*>("graphicsView_"+ oldLevel);
            gv->setObjectName("graphicsView_"+ newLevel);
            CustomGraphicsScene* gs = dynamic_cast<CustomGraphicsScene*>(gv->scene());
            gs->setObjectName("graphicsScene_" + newLevel);
            gs->setLevelName(newLevel);
            tab->setObjectName(pack+":"+newLevel);
            m_tabWidgetGraphicsView->setTabText(thisTabIndex, newName);
        }
        return true;
    }
    else
    {
       QMessageBox::warning(this, tr("Level Editor"), newName + " is already taken.", QMessageBox::Ok);
    }

    return false;
}

void LevelEditor::setNodeDisplayMode()
{
    CustomGraphicsScene* gs = CURRENT_SCENE();
    if(gs)
    {
        gs->setNodeDisplayMode();
    }
}

void LevelEditor::clearLevelConnections()
{
    CustomGraphicsScene* gs = CURRENT_SCENE();
    if(gs)
    {
        gs->removeAllLevelLinks();
    }
}

void LevelEditor::clearLevel()
{
    CustomGraphicsScene* gs = CURRENT_SCENE();
    if(gs)
    {
        gs->removeAllLevelLinks();
        gs->removeAllLevelNodes();
    }

}

void LevelEditor::playLevel()
{
}

void LevelEditor::exportLevelToImageAtIndex(int index, bool autoCapture)
{
    CustomGraphicsView* gv = CURRENT_VIEW();
    if(gv)
    {
        CustomGraphicsScene* gs = dynamic_cast<CustomGraphicsScene*>(gv->scene());
        if(gs)
        {
            QString pack = gs->getPackName();
            QString level = gs->getLevelName();

            qreal m11 = gv->transform().m11();
            gv->setTransform(QTransform::fromScale(1,1));
            gs->showCartesian(false);

            if(!QDir("data/levels_screenies/" + pack).exists())
                QDir("data/levels_screenies").mkdir(pack);

            if(QDir("data/levels_screenies/" + pack).exists())
            {
                QPoint p = gv->mapFromScene(QPoint(1,1));
                QPixmap pix = gv->grab(QRect(p.x(),p.y(),320, 480));
                //pix = pix.scaled(QSize(160, 240));
                bool ret = pix.save("data/levels_screenies/" + pack + "/" + level + ".png", "PNG", 50);

                QString message = "creen capture";
                if(autoCapture)
                    message.insert(0, "Auto s");
                else
                    message.insert(0, "S");

                message += ret ? " success" : "failed";

                setStatusBarMessage(message);
            }

            gs->showCartesian(true);
            gv->setTransform(QTransform::fromScale(m11,m11));
        }
    }
}

void LevelEditor::zoomLevel(int value)
{
    QGraphicsView* gv = CURRENT_VIEW();
    if(gv)
        gv->setTransform(QTransform::fromScale(value/50.0f,value/50.0f));
}

void LevelEditor::setCursorText(int x, int y)
{
    m_cursor->setText("   " + QString::number(x) + "," + QString::number(y));
}

void LevelEditor::newLevel()
{
    m_customTreeWidgetLevels->addLevelButtonReleased(this);
}

void LevelEditor::newPack()
{
    m_customTreeWidgetLevels->addPackButtonReleased(this);
}

void LevelEditor::showUnsaveMark()
{
    int currentIndex = m_tabWidgetGraphicsView->currentIndex();
    QString newText = m_tabWidgetGraphicsView->tabText(currentIndex);
    if(newText.contains("*"))
        return;
    newText += "*";
    m_tabWidgetGraphicsView->setTabText(currentIndex, newText);
}

void LevelEditor::saveLevel(int index)
{
    QString tabName;
    QWidget * w;

    if(index < 0)
        index = m_tabWidgetGraphicsView->currentIndex();

    tabName = m_tabWidgetGraphicsView->tabText(index);
    w = m_tabWidgetGraphicsView->widget(index);

    QString level = tabName.replace("*", "");
    level = tabName.split(".")[0];

    QGraphicsView* gv = w->findChild<QGraphicsView*>("graphicsView_"+ level);

    CustomGraphicsScene* gs;
    if (gv)
    {
        gs = dynamic_cast<CustomGraphicsScene*>(gv->scene());
        if (gs)
        {
            QString pack = gs->getPackName();
            QString levelName = gs->getLevelName();

            Level level;
            gs->toLevel(level);

            bool ret = level.toFile("data/levels/" + pack + "/" + levelName +".lvl");
            if (ret)
            {
                QMap<QString, Level> levels = m_packs[pack].getLevels();
                QMap<QString, Level>::Iterator it = levels.begin();

                for(; it != levels.end(); ++it )
                {
                    if((it).value().getName() == levelName)
                    {
                        levels.erase(it);
                        break;
                    }
                }
                m_packs[pack].setLevel(levelName, level);

                setStatusBarMessage(levelName + "... Saved");

                m_tabWidgetGraphicsView->setTabText(index, levelName +".lvl");
            }

            exportLevelToImageAtIndex(-1, true);
        }
    }
}

void LevelEditor::saveAllLevels()
{
    for(int i=0;i<m_tabWidgetGraphicsView->count();++i)
    {
        saveLevel(i);
    }
}

void LevelEditor::closeLevel(int index)
{
    QWidget* tab;
    if(index < 0)
        index = m_tabWidgetGraphicsView->currentIndex();

    tab =  m_tabWidgetGraphicsView->widget(index);

    QString level = m_tabWidgetGraphicsView->tabText(index).split(".")[0];

    //save level before closing
    saveLevel(index);

    //remove graphics view, graphics scene
    if(tab)
    {
        QGraphicsView* gv = tab->findChild<QGraphicsView*>("graphicsView_"+ level);

        QGraphicsScene* gs = gv->scene();
        gs->clear();
        delete gs;
        delete gv;
    }

    //remove level tab
    if(tab)
        m_tabWidgetGraphicsView->widget(index)->close();
}

void LevelEditor::closeAllLevels()
{
    for(int i=0; i<m_tabWidgetGraphicsView->count(); ++i)
        closeLevel(i);
}

void LevelEditor::closeOtherLevels()
{
    QWidget* tab = m_tabWidgetGraphicsView->widget(m_tabWidgetGraphicsView->currentIndex());

    if(tab)
    {
        int index = m_tabWidgetGraphicsView->currentIndex();
        QString label = m_tabWidgetGraphicsView->tabText(index);
        m_tabWidgetGraphicsView->insertTab(0,tab,label);
        for(int i=1; i<m_tabWidgetGraphicsView->count(); ++i)
            closeLevel(i);
    }
}

void LevelEditor::quitEditor()
{
    QApplication::quit();
}

void LevelEditor::selectAllObjects()
{
    QGraphicsScene* gs=  CURRENT_SCENE();
    if(gs)
    {
        foreach(QGraphicsItem* item, gs->items())
        {
            if(item->data(UNIQUE_ID).isValid())
            {
                if((item->data(UNIQUE_ID).toString().contains("node")) ||
                    (item->data(UNIQUE_ID).toString().contains("link")))
                {
                    item->setSelected(true);
                }
            }
        }
    }
}

void LevelEditor::showLevelLibrary(bool show)
{
    if(show)
        ui->dockWidgetLevelBrowser->show();
    else
        ui->dockWidgetLevelBrowser->hide();
}

void LevelEditor::showLevelProperties(bool show)
{
    if(show)
        ui->dockwidgetLayers->show();
    else
        ui->dockwidgetLayers->hide();
}

void LevelEditor::visibilityChangedDockWidgetLevelBrowser(bool value)
{
    ui->actionLevel_Library->setChecked(value);
}

void LevelEditor::visibilityChangedDockWidgetLayers(bool value)
{
    ui->actionLevel_Properties->setChecked(value);
}


