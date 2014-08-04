#include "CustomTreeWidgetLevels.h"
#include "../LevelEditor.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

#include <QTreeWidget>
#include <QHeaderView>

#include <QMenu>

CustomTreeWidgetLevels::CustomTreeWidgetLevels(QWidget *parent) :
    QTreeWidget(parent)
{
    initialize();
}

void CustomTreeWidgetLevels::initialize()
{
    setObjectName("treeWidgetLevels");
    setAlternatingRowColors(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setColumnCount(1);
    setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList list;
    list << "Packs & Levels";
    setHeaderLabels(list);

    connectSignals();
}

void CustomTreeWidgetLevels::connectSignals()
{
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(itemClicked(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(openContextMenu(QPoint)));
}

void CustomTreeWidgetLevels::refresh()
{

}

void CustomTreeWidgetLevels::populate()
{
    if (!QDir("data/levels").exists())
    {
        qDebug() << "CustomTreeWidgetLevels: Level folder does not exist.\n";
        return;
    }

    QStringList list = QDir("data/levels").entryList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);


    foreach(QString packName, list)
    {
        if (LevelEditor::getInstance()->addLevelPack(packName))
        {
            QTreeWidgetItem* packItem = addPackToTree(packName + ".pak");
            if (packItem)
            {
                QStringList list = QDir("data/levels/" + packName).entryList(QStringList("*.lvl"), QDir::Files, QDir::Name);

                for(int i=0; i<list.length(); ++i)
                {
                    for(int j=0; j<list.length()-1; ++j)
                    {
                        if(list[j].length() > list[j+1].length())
                        {
                            QString temp = list[j+1];
                            list[j+1] = list[j];
                            list[j] = temp;
                        }
                    }
                }

                foreach(QString levelName, list)
                {
                    if (LevelEditor::getInstance()->addLevelToLevelPack(packName,levelName, true))
                        addLevelToTree(packItem, levelName);
                }
            }
        }
    }
}

bool CustomTreeWidgetLevels::isPackNameValid(QString packName)
{
    QString pack = packName;
    return true;
}

void CustomTreeWidgetLevels::addPackButtonReleased(QWidget* parent)
{
    bool ok;
    QString packName = QInputDialog::getText(parent, tr("Add Pack"), tr("Name:"), QLineEdit::Normal, ".pak", &ok);

    if (ok && !packName.isEmpty())
    {
        if(!isPackNameValid(packName))
        {
            QMessageBox::warning(parent, tr("Level Editor"), packName + " is an invalid name.", QMessageBox::Ok);
        }

        QStringList nameList = packName.split(".");
        if (!LevelEditor::getInstance()->packExists(nameList[0]))
        {
            LevelEditor::getInstance()->addLevelPack(nameList[0]);
            addPackToTree(packName);
        }
        else
        {
            QMessageBox::warning(parent, tr("Level Editor"), packName + " is already taken.", QMessageBox::Ok);
        }
    }
}

void CustomTreeWidgetLevels::removePackButtonReleased()
{
    if(!currentItem())
        return;

    QString packName = currentItem()->text(0);

    if(packName.contains(".pak"))
    {
        if(LevelEditor::getInstance()->removeLevelPack(packName))
        {
            delete currentItem();
        }
    }

}

void CustomTreeWidgetLevels::addLevelButtonReleased(QWidget* parent)
{
    QTreeWidgetItem *parentItem;

    if(!currentItem())
        return;

    if (!currentItem()->parent())
        parentItem = currentItem();
    else
        parentItem = currentItem()->parent();

    bool ok;
    QString packName = parentItem->text(0);
    QString pack = packName.split(".")[0];

    LevelEditor* le = LevelEditor::getInstance();

    QString levelName = QInputDialog::getText(le, tr("Add Level"), "Add level to " + packName, QLineEdit::Normal, pack + "_.lvl", &ok);

    if (ok && !levelName.isEmpty())
    {
        if (LevelEditor::getInstance()->addLevel(packName, levelName))
        {
            QTreeWidgetItem* levelItem = addLevelToTree(parentItem,levelName);
            this->clearSelection();
            levelItem->setSelected(true);
        }
    }

}

void CustomTreeWidgetLevels::removeLevelButtonReleased()
{
    if(!currentItem())
        return;

    QString levelName = currentItem()->text(0);
    if(levelName.contains(".lvl"))
    {
        QString packName = currentItem()->parent()->text(0);
        if(LevelEditor::getInstance()->removeLevel(packName, levelName))
        {
            delete currentItem();
        }
    }
}

QTreeWidgetItem* CustomTreeWidgetLevels::addPackToTree(QString packName)
{
    QFont font = this->font();
    QTreeWidgetItem* packItem = new QTreeWidgetItem(this);

    packItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

    font.setBold(true);
    packItem->setFont(0, font);
    packItem->setText(0, packName);

    QTreeWidgetItem* newItem = new QTreeWidgetItem(packItem);
    newItem->setText(0, "Add new level...");

    font.setBold(false);
    font.setItalic(true);
    newItem->setFont(0, font);
    packItem->setExpanded(true);

    return packItem;
}

QTreeWidgetItem* CustomTreeWidgetLevels::addLevelToTree(QTreeWidgetItem* parent, QString levelName)
{
    QTreeWidgetItem* levelItem = new  QTreeWidgetItem();
    levelItem->setText(0, levelName);

    if (parent->childCount() > 0)
    {
        parent->insertChild(parent->childCount()-1,levelItem);
        return levelItem;
    }

    return 0;
}

void CustomTreeWidgetLevels::itemClicked(QTreeWidgetItem *item, int column)
{
    //Nothing to do here
}

void CustomTreeWidgetLevels::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->text(column) == "Add new level...")
    {
        bool ok;
        QString packName = item->parent()->text(0);
        QString pack = packName.split(".")[0];

        LevelEditor* le = LevelEditor::getInstance();

        QString levelName = QInputDialog::getText(le, tr("Add Level"), "Adding level to " + packName, QLineEdit::Normal, pack + "_.lvl", &ok);

        if (ok && !levelName.isEmpty())
        {
            if (LevelEditor::getInstance()->addLevel(packName, levelName))
            {
                QTreeWidgetItem* levelItem = addLevelToTree(item->parent(),levelName);
                this->clearSelection();
                levelItem->setSelected(true);
            }
        }
    }
    else if (item->text(column).contains(".lvl"))
    {
        QString packName = item->parent()->text(0);
        QString levelName = item->text(0);

        LevelEditor::getInstance()->addLevelTab(packName, levelName);
        this->clearSelection();
        item->setSelected(true);
    }
}

void CustomTreeWidgetLevels::openContextMenu(QPoint point)
{
    QPoint globalPos = mapToGlobal(point);

    QTreeWidgetItem* item = itemAt(point);


    if(!item)
        return;
    int showMenu = 0;
    QMenu menu;
    QString itemText = item->text(0);
    QString parentItemText;

    if (itemText.contains(".lvl"))
    {
        menu.addAction("Open");
        menu.addAction("Rename");
        menu.addAction("Screen Capture");
        menu.addSeparator();
        menu.addAction("Remove " + itemText);
        parentItemText = item->parent()->text(0);
        showMenu = 1;
    }
    else if (item->text(0).contains(".pak"))
    {
        QAction* a = menu.addAction("Rename");
        menu.addAction("Screen Capture");
        menu.addSeparator();
        menu.addAction("Remove " + itemText);
        showMenu = 2;
    }

    if (showMenu)
    {
        QAction* selectedItem = menu.exec(globalPos);
        if(!selectedItem)
            return;

        if (selectedItem->text() == "Open")
        {
            LevelEditor::getInstance()->addLevelTab(item->parent()->text(0), item->text(0));
        } else if (selectedItem->text() == "Rename")
        {
            bool ok;
            QString newName = "";
            if(showMenu == 1)
            {
                newName = QInputDialog::getText(LevelEditor::getInstance(), tr("Rename Level"), "Rename " + item->text(0), QLineEdit::Normal, parentItemText.split(".")[0] + "_.lvl", &ok);
                if(ok && !newName.isEmpty())
                {
                    if(LevelEditor::getInstance()->renameLevel(parentItemText, itemText, newName))
                    {
                        item->setText(0, newName);
                    }
                }
            }else if (showMenu == 2)
            {
                newName = QInputDialog::getText(LevelEditor::getInstance(), tr("Rename Pack"), "Rename " + item->text(0) , QLineEdit::Normal, ".pak", &ok);
                if(ok && !newName.isEmpty())
                {
                    QString oldPack = itemText.split(".")[0];
                    QString newPack = newName.split(".")[0];

                    if(LevelEditor::getInstance()->renameLevelPack(itemText, newName))
                    {
                       item->setText(0, newName);

                       for(int i=0; i<item->childCount(); ++i)
                       {
                           if(item->child(i)->text(0) != "Add new level...")
                           {
                               QString temp = item->child(i)->text(0).mid(oldPack.length());
                               item->child(i)->setText(0, newPack + temp);
                           }

                       }
                    }
                }
            }
        } else if (selectedItem->text() == "Screen Capture")
        {
            bool ret = false;
            if(showMenu == 1)
                ret = LevelEditor::getInstance()->exportToImage(parentItemText,itemText);
            else if(showMenu == 2)
                ret = LevelEditor::getInstance()->exportToImage(itemText);
        } else if (selectedItem->text() == ("Remove " + itemText))
        {
            bool ret = false;
            if(showMenu == 1)
                ret = LevelEditor::getInstance()->removeLevel(parentItemText,itemText);
            else if(showMenu == 2)
                ret = LevelEditor::getInstance()->removeLevelPack(itemText);

            if(ret)
                delete item;
        }
    }
}


