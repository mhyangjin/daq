//======================================================================*/
//   Create Date: 2022/11/17
//   ClassName  : YmlLoader
//   Author     : mhjin julu1@naver.com
//   Class Def  : yml file loader
//======================================================================*/
#ifndef YMLLOADER_H
#define YMLLOADER_H
#include "init.h"
#include <QString>
#include <rviz/config.h>
#include <yaml-cpp/yaml.h>

class YmlLoader {
public:
    static void loadConfig( QString,rviz::Config*);
    //verify loading config from .rviz
    static void printConfig(rviz::Config*);
    //test reading from .rviz
    static void printNodes(YAML::Node*);
    //load config from .rviz file
    static void loadNodes(YAML::Node*, rviz::Config*);

    
};
#endif