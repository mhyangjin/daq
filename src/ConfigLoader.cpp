//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : ConfigLoader
//======================================================================*/
#include "ConfigLoader.h"
#include "YmlLoader.h"
#include <string.h>
#include <fstream>

ConfigLoader::ConfigLoader(){
    try {
        YAML::Node _rootNode=YAML::LoadFile(configFileName);
        YAML::Node rvizNode=_rootNode["rviz"];
        rvizDir=QString::fromStdString(rvizNode.as<string>());

        YAML::Node recordNode=_rootNode["record"];
        RecordDir=QString::fromStdString(recordNode.as<string>());

        YAML::Node scriptNode=_rootNode["script"];
        ScriptDir=QString::fromStdString(scriptNode.as<string>());


        YAML::Node launchNode=_rootNode["launchs"];
        for (size_t i=0; i< launchNode.size(); i++) {
            QString name=QString::fromStdString(launchNode[i]["Name"].as<string>());
            QString file=QString::fromStdString(launchNode[i]["File"].as<string>());
            launchers.insert(name, file);
        }

        YAML::Node nodesNode=_rootNode["nodes"];
        for (size_t i=0; i< nodesNode.size(); i++) {
            QString name=QString::fromStdString(nodesNode[i]["Name"].as<string>());
            QString file=QString::fromStdString(nodesNode[i]["File"].as<string>());
            nodes.insert(name, file);
        }
    }
    catch (const YAML::BadFile& e) {
        ROS_INFO("Configfille is not exist. generate default configfile ");
        generateConfig();
    }
    catch ( ...) {
        ROS_INFO("Unkown Exception. generate default configfile ");
        generateConfig();
    }
}

ConfigLoader::~ConfigLoader() {

}

void ConfigLoader::generateConfig() {
    rvizDir="./rvizs";
    RecordDir="/home/jiat/Data";
    ScriptDir="./scripts";

    launchers.insert("novatel_oem7_driver", "oem7_net.launch");
    launchers.insert("ouster_ros","64ch.launch");
    launchers.insert("usb_cam","cameras.launch");
    launchers.insert("velodyne_pointcloud","16ch.launch");
    nodes.insert("daq", "jiat_diagnostic.py");
    nodes.insert("solati", "solati_decode");
    saveConfig();
}
void ConfigLoader::saveConfig() {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "launchs";
    emitter << YAML::Value<< YAML::BeginSeq;
    
    for (auto iter=launchers.constBegin(); iter != launchers.constEnd(); ++iter) {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Name";
        emitter << YAML::Value << iter.key().toStdString();
        emitter << YAML::Key << "File";
        emitter << YAML::Value << iter.value().toStdString();
        emitter << YAML::EndMap;
    }
    emitter << YAML::EndSeq;
    emitter << YAML::Key << "nodes";
    emitter << YAML::Value<< YAML::BeginSeq;
    for (auto iter=nodes.constBegin(); iter != nodes.constEnd(); ++iter) {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Name";
        emitter << YAML::Value << iter.key().toStdString();
        emitter << YAML::Key << "File";
        emitter << YAML::Value << iter.value().toStdString();
        emitter << YAML::EndMap;
    }
    emitter <<  YAML::EndSeq;
    emitter << YAML::Key << "rviz";
    emitter << YAML::Value << rvizDir.toStdString();
    emitter << YAML::Key << "record";
    emitter << YAML::Value << RecordDir.toStdString();
    emitter << YAML::Key << "script";
    emitter << YAML::Value << ScriptDir.toStdString();
    emitter << YAML::EndMap;

    ofstream fout(configFileName);

    fout<<emitter.c_str()<<endl;
    fout.close();
}
void ConfigLoader::setRvizConfig(QString _rvizDir) {
    rvizDir=_rvizDir;
}
void ConfigLoader::setRecordConfig(QString _recordDir) {
    RecordDir=_recordDir;
}
void ConfigLoader::setScriptConfig(QString _scriptDir) {
    ScriptDir=_scriptDir;
}
QString ConfigLoader::getRvizConfig() {

    return rvizDir;
}

QString ConfigLoader::getRecordConfig() {
    return RecordDir;
}

QString ConfigLoader::getScriptConfig() {
    return ScriptDir;
}
QMap<QString, QString> ConfigLoader::getlaunchers() {
    return launchers;
}
QMap<QString, QString> ConfigLoader::getnodes() {
    return nodes;
}
