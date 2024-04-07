#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <fstream>
#include <iostream>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QQmlEngine>
#include <armordata.h>
#include <armorsortfilter.h>

class AppController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool saveIsLoaded READ saveIsLoaded NOTIFY loadedSaveChanged)
    Q_PROPERTY(QString saveName MEMBER saveName NOTIFY saveNameChanged)
    Q_PROPERTY(QList<QString> recentSaveNames MEMBER recentSaveNames NOTIFY recentSaveNamesChanged)
    Q_PROPERTY(bool sortIsAsc MEMBER sortIsAsc NOTIFY sortDirectionChanged)
    Q_PROPERTY(bool unsavedChanges MEMBER unsavedChanges NOTIFY unsavedChangesStateChanged)
    Q_PROPERTY(QString theme MEMBER theme NOTIFY themeChanged)
    Q_PROPERTY(QString saveFileExtension MEMBER saveFileExtension CONSTANT)

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    // MODEL METHODS.
    Q_INVOKABLE ArmorSortFilter *getArmorData() const;
    Q_INVOKABLE ArmorSortFilter *getNewSaveArmorData() const;
    Q_INVOKABLE void clearNewSaveArmorData();

    // SAVE FILE METHODS.
    Q_INVOKABLE bool createNewSave(QString name);
    Q_INVOKABLE bool loadSave(QUrl filePath);
    Q_INVOKABLE bool loadRecentSave(QString saveName);
    Q_INVOKABLE bool saveCurrentSave();
    Q_INVOKABLE bool saveExists(QString saveName);
    // Class q_property definitions are given getters that return based on class state.
    Q_INVOKABLE bool saveIsLoaded();
    Q_INVOKABLE QString getSaveName();
    Q_INVOKABLE QList<QString> getRecentSaveNames();

    // APP CONFIG METHODS.
    bool loadAppConfig(QString filePath);
    bool addLocalSaveToAppConfig(QString saveName);
    bool removeLocalSaveFromAppConfig(QString saveName);
    bool setMostRecentlyAccessedSave(QString saveName);
    bool setAppConfigField(QString fieldName, QString newValue);

    // SORT METHODS.
    // Main armor list.
    Q_INVOKABLE QString currentSortType() const;
    Q_INVOKABLE void setSortType(QString sortType);
    Q_INVOKABLE void setSortDirection(bool ascending);
    Q_INVOKABLE void setSortSearchFilter(QString newSortString);
    // New save armor list.
    Q_INVOKABLE QString newSaveCurrentSortType() const;
    Q_INVOKABLE void newSaveSetSortType(QString sortType);
    Q_INVOKABLE void newSaveSetSortDirection(bool ascending);
    Q_INVOKABLE void newSaveSetSortSearchFilter(QString newSortString);

    // MODIFY ARMOR METHODS.
    // Default to modifying the main dataset. Additional parameters can be set
    // to instead run these methods on the secondary set for new save files.
    Q_INVOKABLE bool increaseArmorLevel(QString armorName, bool useNewSaveData = false);
    Q_INVOKABLE bool decreaseArmorLevel(QString armorName, bool useNewSaveData = false);
    Q_INVOKABLE bool toggleArmorUnlock(QString armorName, bool useNewSaveData = false);

    // APPLICATION SETTINGS METHODS.
    // Designed to be called from the Qt level, handle inputs and config files.
    Q_INVOKABLE bool setAppTheme(QString themeName, bool setDefaults = false);

    // Q_PROPERTY OBJECTS.
    QString saveName = "";
    QList<QString> recentSaveNames = QList<QString>();
    bool sortIsAsc = true;
    bool unsavedChanges = false;
    // In cases where appconfig cannot be parsed for theming info, default theme details are set here.
    QString theme = "System";
    QString saveFileExtension = ".save";

private:
    QString _loadedSavePath = "";
    QString _loadedAppConfigPath = "";
    ArmorSortFilter *_armorData;
    ArmorSortFilter *_newSaveArmorData;

signals:
    void loadedSaveChanged(bool saveIsLoaded);
    void saveNameChanged(QString saveName);
    void recentSaveNamesChanged();
    void sortDirectionChanged();
    void unsavedChangesStateChanged();
    void themeChanged(QString themeName);
};

#endif // APPCONTROLLER_H