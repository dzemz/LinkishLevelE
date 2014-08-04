#include "Level.h"
#include <QFile>
#include <QDebug>
#include <QDir>

LevelPack::LevelPack()
{

}

LevelPack::~LevelPack()
{

}

void LevelPack::removeLevel(QString level)
{
    QMap<QString, Level>::Iterator it = m_levels.begin();
    for (; it != m_levels.end(); ++it)
    {
        if(it.key() == level)
        {
            m_levels.erase(it);
            break;
        }
    }
}

void LevelPack::renameLevel(QString oldName, QString newName)
{
    QMap<QString, Level>::Iterator it = m_levels.begin();
    for (; it != m_levels.end(); ++it)
    {
        if(it.key() == oldName)
        {
            m_levels[newName] = m_levels[oldName];
            m_levels[newName].setName(newName);
            m_levels.erase(it);
            break;
        }
    }
}

void LevelPack::renameLevels(QString oldPack, QString newPack)
{
    QMap<QString, Level> newLevels;

    QMap<QString, Level>::Iterator it = m_levels.begin();
    for(; it != m_levels.end(); ++it)
    {
        QString temp = it.key();
        QString newKey = temp.mid(oldPack.length());
        newKey = newPack + newKey;

        newLevels[newKey] = it.value();
    }

    m_levels.clear();
    m_levels = newLevels;
}


Level::Level()
{
}

Level::~Level()
{


}

QString Level::addObject(QString uniqueName, LevelObject& object)
{
    m_levelObjects[uniqueName] = object;
    return uniqueName;
}

bool Level::fromFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file:" << fileName;
        return false;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString l =  in.readLine();
        if(l.isEmpty())
            continue;

        LevelObject obj;
        obj.fromString(l);
        m_levelObjects[obj.getName()] = obj;
    }

    file.close();

    return true;
}

bool Level::toFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error writing to file:" << fileName;
        return false;
    }

    QTextStream out(&file);

    out << toString();

    qDebug() << "Writing to file success:" << fileName;
    return true;
}

QString Level::toString()
{
    QString level;
    foreach(LevelObject object, m_levelObjects)
    {
        level += object.toString();
    }

    return level;
}

QString LevelObject::toString()
{
    QString toString = getName();
    toString += ":";
    toString += QString::number(getPosition().x()) + "," + QString::number(getPosition().y());
    toString += ":";

    foreach(QString link, getLinks())
    {
        toString += link + ",";
    }
    toString += "\n";

    return toString;
}

void LevelObject::fromString(QString levelObject)
{
    QStringList properties = levelObject.split(":");
    m_name = properties[0];

    QStringList position = properties[1].split(",");
    m_position = QPoint(position[0].toFloat(),position[1].toFloat());

    QStringList links = properties[2].split(",");
    foreach(QString link, links)
        if(!link.isEmpty())
            m_links.append(link);
}
