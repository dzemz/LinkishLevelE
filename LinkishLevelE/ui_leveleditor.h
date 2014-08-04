/********************************************************************************
** Form generated from reading UI file 'leveleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVELEDITOR_H
#define UI_LEVELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LevelEditor
{
public:
    QAction *actionPack;
    QAction *actionLevel;
    QAction *actionPlay;
    QAction *actionClear;
    QAction *actionHide_Connections;
    QAction *actionClear_Connections;
    QAction *actionLevel_Library;
    QAction *actionLevel_Properties;
    QAction *actionNew_Level;
    QAction *actionSave;
    QAction *actionSave_All;
    QAction *actionClose;
    QAction *actionClose_All;
    QAction *actionClose_Others;
    QAction *actionExit;
    QAction *actionNew_Pack;
    QAction *actionSelect_All;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidgetGraphicsView;
    QWidget *tabGraphicsView;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsviewLevel;
    QWidget *widgetToolbar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuLevel;
    QMenu *menuWindow;
    QDockWidget *dockwidgetLayers;
    QWidget *dockWidgetContentsLayers;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabwidgetProperties;
    QWidget *tabProperties;
    QTabWidget *tabwidgetLayers;
    QWidget *tabLayers;
    QDockWidget *dockWidgetLevelBrowser;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *widgetLevels;

    void setupUi(QMainWindow *LevelEditor)
    {
        if (LevelEditor->objectName().isEmpty())
            LevelEditor->setObjectName(QStringLiteral("LevelEditor"));
        LevelEditor->resize(960, 640);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LevelEditor->sizePolicy().hasHeightForWidth());
        LevelEditor->setSizePolicy(sizePolicy);
        LevelEditor->setMinimumSize(QSize(0, 15));
        LevelEditor->setMaximumSize(QSize(16777215, 16777215));
        LevelEditor->setAutoFillBackground(false);
        LevelEditor->setDocumentMode(true);
        actionPack = new QAction(LevelEditor);
        actionPack->setObjectName(QStringLiteral("actionPack"));
        actionLevel = new QAction(LevelEditor);
        actionLevel->setObjectName(QStringLiteral("actionLevel"));
        actionPlay = new QAction(LevelEditor);
        actionPlay->setObjectName(QStringLiteral("actionPlay"));
        actionClear = new QAction(LevelEditor);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionHide_Connections = new QAction(LevelEditor);
        actionHide_Connections->setObjectName(QStringLiteral("actionHide_Connections"));
        actionClear_Connections = new QAction(LevelEditor);
        actionClear_Connections->setObjectName(QStringLiteral("actionClear_Connections"));
        actionLevel_Library = new QAction(LevelEditor);
        actionLevel_Library->setObjectName(QStringLiteral("actionLevel_Library"));
        actionLevel_Library->setCheckable(true);
        actionLevel_Library->setChecked(true);
        actionLevel_Properties = new QAction(LevelEditor);
        actionLevel_Properties->setObjectName(QStringLiteral("actionLevel_Properties"));
        actionLevel_Properties->setCheckable(true);
        actionLevel_Properties->setChecked(true);
        actionNew_Level = new QAction(LevelEditor);
        actionNew_Level->setObjectName(QStringLiteral("actionNew_Level"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/images/Document.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Level->setIcon(icon);
        actionSave = new QAction(LevelEditor);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/images/Floppy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSave_All = new QAction(LevelEditor);
        actionSave_All->setObjectName(QStringLiteral("actionSave_All"));
        actionClose = new QAction(LevelEditor);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/images/Close Square.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon2);
        actionClose_All = new QAction(LevelEditor);
        actionClose_All->setObjectName(QStringLiteral("actionClose_All"));
        actionClose_Others = new QAction(LevelEditor);
        actionClose_Others->setObjectName(QStringLiteral("actionClose_Others"));
        actionExit = new QAction(LevelEditor);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionNew_Pack = new QAction(LevelEditor);
        actionNew_Pack->setObjectName(QStringLiteral("actionNew_Pack"));
        actionSelect_All = new QAction(LevelEditor);
        actionSelect_All->setObjectName(QStringLiteral("actionSelect_All"));
        centralWidget = new QWidget(LevelEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tabWidgetGraphicsView = new QTabWidget(centralWidget);
        tabWidgetGraphicsView->setObjectName(QStringLiteral("tabWidgetGraphicsView"));
        tabWidgetGraphicsView->setTabShape(QTabWidget::Rounded);
        tabWidgetGraphicsView->setIconSize(QSize(16, 16));
        tabWidgetGraphicsView->setDocumentMode(true);
        tabWidgetGraphicsView->setTabsClosable(false);
        tabWidgetGraphicsView->setMovable(true);
        tabGraphicsView = new QWidget();
        tabGraphicsView->setObjectName(QStringLiteral("tabGraphicsView"));
        horizontalLayout = new QHBoxLayout(tabGraphicsView);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsviewLevel = new QGraphicsView(tabGraphicsView);
        graphicsviewLevel->setObjectName(QStringLiteral("graphicsviewLevel"));
        graphicsviewLevel->setMouseTracking(true);
        QBrush brush(QColor(225, 225, 225, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsviewLevel->setBackgroundBrush(brush);
        graphicsviewLevel->setRenderHints(QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        graphicsviewLevel->setDragMode(QGraphicsView::ScrollHandDrag);

        horizontalLayout->addWidget(graphicsviewLevel);

        tabWidgetGraphicsView->addTab(tabGraphicsView, QString());

        verticalLayout_4->addWidget(tabWidgetGraphicsView);

        widgetToolbar = new QWidget(centralWidget);
        widgetToolbar->setObjectName(QStringLiteral("widgetToolbar"));
        sizePolicy.setHeightForWidth(widgetToolbar->sizePolicy().hasHeightForWidth());
        widgetToolbar->setSizePolicy(sizePolicy);
        widgetToolbar->setMinimumSize(QSize(0, 35));
        widgetToolbar->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_4->addWidget(widgetToolbar);

        verticalLayout_4->setStretch(0, 1);
        LevelEditor->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LevelEditor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setAutoFillBackground(false);
        LevelEditor->setStatusBar(statusBar);
        menuBar = new QMenuBar(LevelEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 21));
        menuBar->setNativeMenuBar(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuLevel = new QMenu(menuBar);
        menuLevel->setObjectName(QStringLiteral("menuLevel"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        LevelEditor->setMenuBar(menuBar);
        dockwidgetLayers = new QDockWidget(LevelEditor);
        dockwidgetLayers->setObjectName(QStringLiteral("dockwidgetLayers"));
        sizePolicy.setHeightForWidth(dockwidgetLayers->sizePolicy().hasHeightForWidth());
        dockwidgetLayers->setSizePolicy(sizePolicy);
        dockwidgetLayers->setMinimumSize(QSize(133, 288));
        dockwidgetLayers->setBaseSize(QSize(262, 640));
        dockwidgetLayers->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockwidgetLayers->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContentsLayers = new QWidget();
        dockWidgetContentsLayers->setObjectName(QStringLiteral("dockWidgetContentsLayers"));
        sizePolicy.setHeightForWidth(dockWidgetContentsLayers->sizePolicy().hasHeightForWidth());
        dockWidgetContentsLayers->setSizePolicy(sizePolicy);
        dockWidgetContentsLayers->setBaseSize(QSize(262, 640));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContentsLayers);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabwidgetProperties = new QTabWidget(dockWidgetContentsLayers);
        tabwidgetProperties->setObjectName(QStringLiteral("tabwidgetProperties"));
        tabwidgetProperties->setDocumentMode(false);
        tabwidgetProperties->setTabsClosable(false);
        tabProperties = new QWidget();
        tabProperties->setObjectName(QStringLiteral("tabProperties"));
        tabwidgetProperties->addTab(tabProperties, QString());

        verticalLayout_2->addWidget(tabwidgetProperties);

        tabwidgetLayers = new QTabWidget(dockWidgetContentsLayers);
        tabwidgetLayers->setObjectName(QStringLiteral("tabwidgetLayers"));
        tabwidgetLayers->setDocumentMode(false);
        tabLayers = new QWidget();
        tabLayers->setObjectName(QStringLiteral("tabLayers"));
        tabwidgetLayers->addTab(tabLayers, QString());

        verticalLayout_2->addWidget(tabwidgetLayers);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 2);
        dockwidgetLayers->setWidget(dockWidgetContentsLayers);
        LevelEditor->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockwidgetLayers);
        dockWidgetLevelBrowser = new QDockWidget(LevelEditor);
        dockWidgetLevelBrowser->setObjectName(QStringLiteral("dockWidgetLevelBrowser"));
        sizePolicy.setHeightForWidth(dockWidgetLevelBrowser->sizePolicy().hasHeightForWidth());
        dockWidgetLevelBrowser->setSizePolicy(sizePolicy);
        dockWidgetLevelBrowser->setMinimumSize(QSize(264, 300));
        dockWidgetLevelBrowser->setBaseSize(QSize(0, 0));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/images/Library Occupied.png"), QSize(), QIcon::Normal, QIcon::Off);
        dockWidgetLevelBrowser->setWindowIcon(icon3);
        dockWidgetLevelBrowser->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        sizePolicy.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetLevels = new QWidget(dockWidgetContents);
        widgetLevels->setObjectName(QStringLiteral("widgetLevels"));
        sizePolicy.setHeightForWidth(widgetLevels->sizePolicy().hasHeightForWidth());
        widgetLevels->setSizePolicy(sizePolicy);
        widgetLevels->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(widgetLevels);

        dockWidgetLevelBrowser->setWidget(dockWidgetContents);
        LevelEditor->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetLevelBrowser);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuLevel->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuFile->addAction(actionNew_Level);
        menuFile->addAction(actionNew_Pack);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_All);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addAction(actionClose_All);
        menuFile->addAction(actionClose_Others);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionSelect_All);
        menuLevel->addAction(actionPlay);
        menuLevel->addAction(actionClear);
        menuLevel->addSeparator();
        menuLevel->addAction(actionClear_Connections);
        menuWindow->addAction(actionLevel_Library);
        menuWindow->addAction(actionLevel_Properties);

        retranslateUi(LevelEditor);

        tabWidgetGraphicsView->setCurrentIndex(0);
        tabwidgetProperties->setCurrentIndex(0);
        tabwidgetLayers->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LevelEditor);
    } // setupUi

    void retranslateUi(QMainWindow *LevelEditor)
    {
        LevelEditor->setWindowTitle(QApplication::translate("LevelEditor", "LevelE", 0));
        actionPack->setText(QApplication::translate("LevelEditor", "Pack", 0));
        actionLevel->setText(QApplication::translate("LevelEditor", "Level", 0));
        actionPlay->setText(QApplication::translate("LevelEditor", "Play", 0));
        actionClear->setText(QApplication::translate("LevelEditor", "Clear", 0));
        actionHide_Connections->setText(QApplication::translate("LevelEditor", "Hide Connections", 0));
        actionClear_Connections->setText(QApplication::translate("LevelEditor", "Clear Connections", 0));
        actionLevel_Library->setText(QApplication::translate("LevelEditor", "Level Library", 0));
        actionLevel_Properties->setText(QApplication::translate("LevelEditor", "Level Properties", 0));
        actionNew_Level->setText(QApplication::translate("LevelEditor", "New Level", 0));
        actionNew_Level->setShortcut(QApplication::translate("LevelEditor", "F2", 0));
        actionSave->setText(QApplication::translate("LevelEditor", "Save", 0));
        actionSave->setShortcut(QApplication::translate("LevelEditor", "Ctrl+S", 0));
        actionSave_All->setText(QApplication::translate("LevelEditor", "Save All", 0));
        actionSave_All->setShortcut(QApplication::translate("LevelEditor", "Ctrl+Shift+S", 0));
        actionClose->setText(QApplication::translate("LevelEditor", "Close", 0));
        actionClose->setShortcut(QApplication::translate("LevelEditor", "Ctrl+W", 0));
        actionClose_All->setText(QApplication::translate("LevelEditor", "Close All", 0));
        actionClose_All->setShortcut(QApplication::translate("LevelEditor", "Ctrl+Shift+W", 0));
        actionClose_Others->setText(QApplication::translate("LevelEditor", "Close Others", 0));
        actionExit->setText(QApplication::translate("LevelEditor", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("LevelEditor", "Ctrl+Q", 0));
        actionNew_Pack->setText(QApplication::translate("LevelEditor", "New Pack", 0));
        actionNew_Pack->setShortcut(QApplication::translate("LevelEditor", "F3", 0));
        actionSelect_All->setText(QApplication::translate("LevelEditor", "Select All", 0));
        actionSelect_All->setShortcut(QApplication::translate("LevelEditor", "Ctrl+A", 0));
#ifndef QT_NO_TOOLTIP
        graphicsviewLevel->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        tabWidgetGraphicsView->setTabText(tabWidgetGraphicsView->indexOf(tabGraphicsView), QString());
#ifndef QT_NO_STATUSTIP
        statusBar->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        menuFile->setTitle(QApplication::translate("LevelEditor", "File", 0));
        menuEdit->setTitle(QApplication::translate("LevelEditor", "Edit", 0));
        menuLevel->setTitle(QApplication::translate("LevelEditor", "Level", 0));
        menuWindow->setTitle(QApplication::translate("LevelEditor", "Window", 0));
#ifndef QT_NO_STATUSTIP
        dockwidgetLayers->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        dockwidgetLayers->setWindowTitle(QApplication::translate("LevelEditor", "Level", 0));
        tabwidgetProperties->setTabText(tabwidgetProperties->indexOf(tabProperties), QApplication::translate("LevelEditor", "Properties", 0));
        tabwidgetLayers->setTabText(tabwidgetLayers->indexOf(tabLayers), QApplication::translate("LevelEditor", "Layers", 0));
        dockWidgetLevelBrowser->setWindowTitle(QApplication::translate("LevelEditor", "Level Library", 0));
    } // retranslateUi

};

namespace Ui {
    class LevelEditor: public Ui_LevelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELEDITOR_H
