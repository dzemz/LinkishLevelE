#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T22:28:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LinkishLevelE
TEMPLATE = app


SOURCES += main.cpp\
    level/Level.cpp \
    LevelEditor.cpp \
    ui/CustomTreeWidgetProperties.cpp \
    ui/CustomTreeWidgetLayers.cpp \
    ui/CustomGraphicsScene.cpp \
    ui/CustomTreeWidgetLevels.cpp \
    ui/CustomTabWidgetGraphicsView.cpp \
    ui/CustomGraphicsItem.cpp \
    ui/CustomGraphicsView.cpp \
    ui/CustomDialogGallery.cpp

HEADERS  += \
    level/Level.h \
    LevelEditor.h \
    ui/CustomTreeWidgetProperties.h \
    ui/CustomTreeWidgetLayers.h \
    ui/CustomGraphicsScene.h \
    ui/CustomTreeWidgetLevels.h \
    ui/CustomTabWidgetGraphicsView.h \
    ui/CustomGraphicsItem.h \
    ui/CustomGraphicsView.h \
    ui/CustomDialogGallery.h

FORMS    += \
    leveleditor.ui

OTHER_FILES +=

RESOURCES += \
    icons.qrc \
    images.qrc \
    fonts.qrc
