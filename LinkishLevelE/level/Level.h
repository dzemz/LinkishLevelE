#ifndef LELEVEL_H
#define LELEVEL_H

#include <QString>
#include <QVector2D>
#include <vector>
#include <QMap>
#include <QStringList>

class LevelObject
{
public:
    LevelObject(){}

    const QString& getName() { return m_name; }
    void setName(QString name) { m_name = name; }
    QPoint& getPosition() { return m_position; }
    void setPosition(QPoint position) { m_position = position; }
    QStringList getLinks() { return m_links; }

    QString toString();
    void fromString(QString levelObject);

    void addLink(QString link) { m_links << link; }
    void removeLink();
    void removeAllLinks();

protected:
    QString m_name;
    QPoint m_position;
    QStringList m_links;
};


class Level
{
public:
    Level();
    ~Level();

    QString addObject(QString, LevelObject&);
    void deleteObject(QString);
    void deleteAllObjects();

    QString getName() { return m_name; }
    void setName(QString levelName) { m_name = levelName; }

    QMap<QString, LevelObject>& getObjects() { return m_levelObjects; }
    LevelObject& getObject(QString name) { return m_levelObjects[name]; }
    bool fromFile(QString);
    bool toFile(QString);
    QString toString();

private:
    QString m_name;
    QMap<QString, LevelObject> m_levelObjects;
};

class LevelPack
{
public:
    LevelPack();
    ~LevelPack();

    QString getName() { return m_name; }

    bool levelExists(QString levelName) { return !(m_levels.find(levelName) == m_levels.end()); }
    void setName(QString name) { m_name = name; }

    void addLevel(Level level)
    {
        m_levels[level.getName()] = level;
    }

    void removeLevel(QString);
    void renameLevel(QString, QString);
    void renameLevels(QString, QString);

    Level& getLevel(QString levelName) { return m_levels[levelName]; }
    void setLevel(QString name, Level level) { m_levels[name] = level; }
    QMap<QString, Level>& getLevels() { return m_levels; }

private:
    QString m_name;
    QMap<QString, Level> m_levels;

};

#endif // LELEVEL_H
