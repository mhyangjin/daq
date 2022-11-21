//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : ConfigLoader
//   Author     : mhjin julu1@naver.com
//   Class Def  : ConfigLoader
//======================================================================*/
#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include "init.h"
#include <yaml-cpp/yaml.h>
#include <QMap>
#include <QString>
#include <QMap>

class ConfigLoader {
public:
    ConfigLoader();
    ~ConfigLoader();
    void saveConfig();

    QString getRvizConfig();
    QString getRecordConfig();
    QString getScriptConfig();
    QMap<QString, QString> getlaunchers();
    QMap<QString, QString> getnodes();
    void setRvizConfig(QString);
    void setRecordConfig(QString);
    void setScriptConfig(QString);
private:
    void loadConfig();

private:
    const string configFileName="./config.yml";
    QString rvizDir;
    QString RecordDir;
    QString ScriptDir;
    QMap<QString, QString> launchers;
    QMap<QString, QString> nodes;
};

#endif
