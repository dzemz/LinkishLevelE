#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QLabel>

#include "ui/CustomGraphicsScene.h"
#include "ui/CustomTreeWidgetLayers.h"
#include "ui/CustomTreeWidgetLevels.h"
#include "ui/CustomTabWidgetGraphicsView.h"
#include "ui/CustomTreeWidgetProperties.h"
#include "ui/CustomDialogGallery.h"

#include "level/Level.h"

#define PROPERTIES() LevelEditor::getInstance()->getCustomTreeWidgetProperties()
#define LAYERS() LevelEditor::getInstance()->getCustomTreeWidgetLayer()
#define CURRENT_SCENE() LevelEditor::getInstance()->getCurrentScene()
#define CURRENT_VIEW() LevelEditor::getInstance()->getCurrentGraphicsView()

#define IS_LANDSCAPE 0

namespace Ui {

class LevelEditor;
}

class LevelEditor : public QMainWindow
{
    Q_OBJECT

private:
    int currentLevel;

    CustomDialogGallery* m_customDialogGallery = 0;
    CustomGraphicsScene* m_customGraphicsScene;
    CustomTreeWidgetLayers* m_customTreeWidgetLayers;
    CustomTreeWidgetLevels* m_customTreeWidgetLevels;
    CustomTabWidgetGraphicsView* m_customTabWidgetGraphicsView;
    CustomTreeWidgetProperties* m_customTreeWidgetProperties;

    QStatusBar* m_statusBar;
    QTabWidget* m_tabWidgetGraphicsView;

    QMap<QString, LevelPack> m_packs;

    QAction* m_addPack;
    QAction* m_removePack;
    QAction* m_addLevel;
    QAction* m_removeLevel;
    QAction* m_expandAll;
    QAction* m_collapseAll;
    QAction* m_openGallery;

    QAction* m_nodeRingsNum;
    QAction* m_clearConnections;
    QAction* m_clearLevel;
    QAction* m_saveLevel;
    QAction* m_playLevel;
    QAction* m_screenCap;
    QSlider* m_hSlider;
    QLabel* m_cursor;

public:
    explicit LevelEditor(QWidget *parent = 0);
    static LevelEditor* getInstance();
    ~LevelEditor();

    void initialize();
    void createFolders();
    void loadFonts();
    void setStatusBarMessage(QString);
    void connectSignals();

    QMap<QString, LevelPack>& getPacks() { return m_packs; }
    bool packExists(QString packName) { return !(m_packs.find(packName) == m_packs.end());}
    bool levelExists(QString packName, QString levelName) { return m_packs[packName].levelExists(levelName); }

    bool addLevelToLevelPack(QString, QString, bool fromFile = false);

    bool addLevelTab(QString, QString);
    Level& getLevel(QString packName, QString levelName) { return m_packs[packName].getLevel(levelName); }

    bool addLevel(QString, QString);
    bool removeLevel(QString, QString);
    bool renameLevel(QString, QString, QString);

    bool addLevelPack(QString);
    bool removeLevelPack(QString);
    bool renameLevelPack(QString, QString);

    bool exportToImage(QString, QString levelName = "");

    CustomGraphicsScene* getCurrentScene();
    CustomGraphicsView* getCurrentGraphicsView();
    CustomGraphicsScene* getGraphicsScene() { return m_customGraphicsScene; }
    CustomTreeWidgetLayers* getCustomTreeWidgetLayer() { return m_customTreeWidgetLayers; }
    CustomTreeWidgetLevels* getCustomTreeWidgetLevel() { return m_customTreeWidgetLevels; }
    CustomTreeWidgetProperties* getCustomTreeWidgetProperties() { return m_customTreeWidgetProperties; }
    QTabWidget* getCustomTabWigetGraphicsView() { return m_tabWidgetGraphicsView; }
    QSlider* getZoomSlider() { return m_hSlider; }

    Ui::LevelEditor* getUI() { return ui; }

private:
    void setupMenubar();
    void setupToolbar();
    void setupProperties();
    void setupLayers();
    void setupLevels();
    void setupGraphicsView();
    void setupGraphicsScene();
    void setupStatusBar();

public:
    Ui::LevelEditor *ui;

public slots:
    //level library
    void addPackButtonReleased();
    void removePackButtonReleased();

    void addLevelButtonReleased();
    void removeLevelButtonReleased();

    void expandAllButtonReleased();
    void collapseAllButtonReleased();
    void openGalleryButtonReleased();

    //tabwidget graphicsview
    void currentTabChanged(int);

    //buttons below tabwidget
    void setNodeDisplayMode();

    void clearLevelConnections();
    void clearLevel();
    void playLevel();

    void exportLevelToImageAtIndex(int index = -1, bool autoCapture = false);

    void zoomLevel(int);
    void setCursorText(int,int);

    //file menu
    void newLevel();
    void newPack();
    void saveLevel(int index = -1);
    void saveAllLevels();
    void closeLevel(int index = -1);
    void closeAllLevels();
    void closeOtherLevels();
    void quitEditor();

    //edit menu
    void selectAllObjects();

    //window menu
    void showLevelLibrary(bool);
    void showLevelProperties(bool);

    void showUnsaveMark();

    void visibilityChangedDockWidgetLevelBrowser(bool);
    void visibilityChangedDockWidgetLayers(bool);

    void resetStatusBarMessage(QString);

};

#endif // MAINWINDOW_H
