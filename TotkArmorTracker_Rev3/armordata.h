#ifndef ARMORDATA_H
#define ARMORDATA_H

#include <fstream>
#include <iostream>
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QVariant>
#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>
#include <armor.h>
#include <helper.cpp>

using namespace rapidxml;

class ArmorData : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ArmorRoles {
        NameRole = Qt::UserRole + 1,
        SetNameRole,
        SetDescRole,
        PassiveBonusRole,
        SetBonusRole,
        LevelRole
    } ArmorRoles;

    ArmorData(QObject *parent = nullptr);

    // QAbstractListModel required methods.
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // Armor list methods.
    bool loadArmorDataFromFile(QString armorFilePath);
    void addArmor(Armor armor);

private:
    QList<Armor> _mDatas = QList<Armor>();
    QObject *_parent;
};

#endif // ARMORDATA_H
