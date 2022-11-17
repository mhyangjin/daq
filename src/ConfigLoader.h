//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : ConfigLoader
//   Author     : mhjin julu1@naver.com
//   Class Def  : ConfigLoader
//======================================================================*/
#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <QMap>
#include <QString>
#include "init.h"

class ConfigLoader {
public:
    ConfigLoader();
    ~ConfigLoader();
    void saveConfig();

    QString getRvizConfig();
    QString getScriptConfig();
    QString getRecordConfig();
private:
    void loadConfig();

private:
    const QString configFileName="daq.ini";
    QMap<QString, QString> configMap;
};

#endif
