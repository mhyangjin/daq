//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : RvizViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : .rviz file을 읽어서 rviz::Config로 만든 후 VisualizationManager
//                를 통해 GUI로 보내기 위한  class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#include "RvizViewer.h"

RvizViewer::RvizViewer(Ui::DaqMain* ui, QString _rvizName,QString _title)
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
    panel_->initialize(manager->getSceneManager(), manager);
    manager->initialize();  
    manager->load(childConfig);
    //DAQViz::display_layout.addWidget(panel_);
    //panel_->hide();
}

RvizViewer::~RvizViewer() {
}

void RvizViewer::showWindow() {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,0);
    ui->rviz_layout->addWidget(panel_,1,0);
    manager->startUpdate();
    DAQViz::title->show();
    panel_->show();
    ui->rviz_layout->update();
    
}


void RvizViewer::showWindow(int xpos, int ypos) {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title, xpos-1, ypos);
    ui->rviz_layout->addWidget(panel_, xpos, ypos);
    manager->startUpdate();
    DAQViz::title->show();
    panel_->show();
    ui->rviz_layout->update();
}

void RvizViewer::closeWindow(){
    DAQViz::buttonState=ButtonState::OFF;
    DAQViz::title->hide();
    panel_->hide();
    manager->stopUpdate();
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(panel_);
    ui->rviz_layout->update();
    
}



void RvizViewer::loadConfig( QString rvizFileName,rviz::Config *config) {
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

void RvizViewer::loadNodes(YAML::Node* node, rviz::Config* config) {
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

void RvizViewer::printNodes(YAML::Node* node) {
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

void RvizViewer::printConfig(rviz::Config* config) {
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
