//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : ConfigLoader
//======================================================================*/
#include "ConfigLoader.h"

ConfigLoader::ConfigLoader(){

}

ConfigLoader::~ConfigLoader() {

}
void ConfigLoader::saveConfig() {

}
QString ConfigLoader::getRvizConfig() {
    return configMap.find("rviz").value();
}
QString ConfigLoader::getScriptConfig() {
    return configMap.find("script").value();
}
QString ConfigLoader::getRecordConfig() {
    return configMap.find("record").value();
}
void ConfigLoader::loadConfig() {

}