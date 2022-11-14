//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/
#include "CameraViewer.h"
#include <rviz/display.h>

CameraViewer::CameraViewer(Ui::DaqMain* ui, QString _rvizName, QString _title)
:DAQViz(ui, _title),
rvizName(_rvizName)
{
    loadConfig(rvizName, &config);
    if ( !config.isValid()) {
        exit(-1);
    } 
    panel_= new rviz::RenderPanel();  
    manager= new rviz::VisualizationManager(panel_);
    
    rviz::Config childConfig=config.mapGetChild("Visualization Manager");
    if ( childConfig.isValid()) {
        cout <<"showRviz:Visualization Manager is Valid! : "<< qPrintable(rvizName) <<endl;
    }
    rviz::Display* cameraDisplay= manager->createDisplay("rviz/Image","front_camera",false);
    rviz::Config front_camera=childConfig.listChildAt(0);
    cameraDisplay->load(front_camera);

    panel_->initialize(manager->getSceneManager(), manager);
    manager->initialize();  
    //DAQViz::display_layout.addWidget(panel_);
    panel_->hide();
    //manager->load(childConfig);
}

CameraViewer::CameraViewer(Ui::DaqMain* ui, QString _rvizName, QString _title, int xpos, int ypos)
:DAQViz(ui, _title)
{
    loadConfig(rvizName, &config);
    if ( !config.isValid()) {
        exit(-1);
    }   
}

CameraViewer::~CameraViewer() {
}

void CameraViewer::clicked(){
    cout <<"CameraViewer::clicked()"<<qPrintable(rvizName)  <<endl;
    if ( DAQViz::buttonState == ButtonState::ON){
        closeWindow();
        DAQViz::buttonState=ButtonState::OFF;
    }
    else {
        showWindow();
        DAQViz::buttonState=ButtonState::ON;
    }
    
}

void CameraViewer::showWindow() {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title);
    ui->rviz_layout->addWidget(panel_);
    manager->startUpdate();
    DAQViz::title->show();
    panel_->show();
    ui->rviz_layout->update();

    
}
void CameraViewer::closeWindow(){
    DAQViz::buttonState=ButtonState::OFF;
    panel_->hide();
    DAQViz::title->hide();
    manager->stopUpdate();
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(panel_);
    ui->rviz_layout->update();
}



void CameraViewer::loadConfig( QString rvizFileName,rviz::Config *config) {
    //rviz::YamlConfigReader가 .rviz 로 저장된 yaml의 array type을 읽어오지 못해서 내부 구현 함
    /*
    rviz::YamlConfigReader config_reader;
    rviz::Config config_;
    config_reader.readFile(config_, rvizFileName);
    */
    YAML::Node _rootNode=YAML::LoadFile(qPrintable(rvizFileName));
    //printNodes(&_rootNode);
    loadNodes(&_rootNode, config);
}

void CameraViewer::loadNodes(YAML::Node* node, rviz::Config* config) {
    for(YAML::const_iterator it=node->begin(); it!=node->end(); it++) {
        YAML::Node _node=it->first;
        YAML::Node _value=it->second;
        string nodeStr=_node.as<string>();
        string valueStr;
        rviz::Config childConfig;
        switch ( _value.Type()) {
            case YAML::NodeType::Scalar: 
                valueStr=_value.as<string>();
                //cout <<"NODE:"<< nodeStr << endl;
                //cout <<"VALUE:"<< valueStr << endl;
                config->mapSetValue(QString::fromStdString(nodeStr),QString::fromStdString(valueStr));
                break;
            case YAML::NodeType::Sequence:
                //cout <<"NODE:"<< nodeStr <<"-SEQ-"<<_value.size()<< endl;
                childConfig=config->mapMakeChild(QString::fromStdString(nodeStr));
                
                for (size_t i=0; i< _value.size(); i++) {
                    YAML::Node arrayValue=_value[i];
                    rviz::Config seqConfig=childConfig.listAppendNew();
                    if (arrayValue.Type() == YAML::NodeType::Scalar) {
                        valueStr=arrayValue.as<string>();
                    //    cout<<"-" << valueStr<< endl;
                        seqConfig.setValue(QString::fromStdString(valueStr));
                    }
                    else 
                        loadNodes(&arrayValue, &seqConfig);
                }
                break;
            case YAML::NodeType::Map:
                //cout <<"NODE:"<< nodeStr <<"-map"<< endl;
                childConfig=config->mapMakeChild(QString::fromStdString(nodeStr));
                loadNodes(&_value, &childConfig);
                break;
            default :
                cout <<"NONE:"<< _node.as<string>() << endl;
        }
    }
}

void CameraViewer::printNodes(YAML::Node* node) {
    for(YAML::const_iterator it=node->begin(); it!=node->end(); it++) {
        YAML::Node _node=it->first;
        YAML::Node value=it->second;
        cout<<_node.as<string>()<< ": ";
        switch ( value.Type()) {
            case YAML::NodeType::Scalar: 
                cout << "(S)"<<value.as<string>()<<endl;
                break;
            case YAML::NodeType::Sequence:
                cout <<"  - ";
                for (size_t i=0; i< value.size(); i++) {
                    YAML::Node arrayValue=value[i];
                    if (arrayValue.Type() == YAML::NodeType::Scalar) {
                        cout << "(A)"<<arrayValue.as<string>()<<endl;
                    }
                    else 
                        printNodes(&arrayValue);
                }
                break;
            case YAML::NodeType::Map:
                printNodes(&value);
                break;
            default :
                cout <<"NONE" << endl;
        }
    }
}

void CameraViewer::printConfig(rviz::Config* config) {
    rviz::Config::MapIterator master_iter=config->mapIterator();;
    for ( ; master_iter.isValid(); master_iter.advance()) {
        QString key=master_iter.currentKey();
        cout <<  qPrintable(key)<<" : ";
        rviz::Config childConfig=master_iter.currentChild();
        switch(childConfig.getType()) {
            case rviz::Config::Type::Map:
                printConfig(&childConfig);
            break;
            case rviz::Config::Type::List:
                for (size_t i=0; i< childConfig.listLength(); i++) {
                    rviz::Config listNode =childConfig.listChildAt(i);
                    if (listNode.getType() == rviz::Config::Type::Value) {
                        cout << "-" << qPrintable(listNode.getValue().toString())<<endl;
                    }
                    else 
                        printConfig(&listNode);
                }
            break;
            case rviz::Config::Type::Value:
                cout << endl;
                cout << qPrintable(childConfig.getValue().toString())<<endl;
            break;
            defaut:
            break;

        }
    }
}
