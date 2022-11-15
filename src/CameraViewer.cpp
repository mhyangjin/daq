//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/
#include "CameraViewer.h"
#include <rviz/display.h>
#include "DaqCameraDisplay.h"

CameraViewer::CameraViewer(Ui::DaqMain* ui, QString _rvizName, QString _title)
:DAQViz(ui, _title),
rvizName(_rvizName)
{
    loadConfig(rvizName, &config);
    if ( !config.isValid()) {
        exit(-1);
    } 
     
    rviz::Config childConfig=config.mapGetChild("Visualization Manager");
    if ( childConfig.isValid()) {
        cout <<"showRviz:Visualization Manager is Valid! : "<< qPrintable(rvizName) <<endl;
    }

    buildDisplay( &childConfig  );
    
}

CameraViewer::~CameraViewer() {
}

void CameraViewer::buildDisplay(rviz::Config* config) {
    for (int i=0; i<3; i++) {
        panels[i]= new rviz::RenderPanel();  
        managers[i]= new rviz::VisualizationManager(panels[i]);  

        rviz::Config camera_config   = config->listChildAt(i);
        displays[i]=new DaqCameraDisplay(panels[i]);
        displays[i]->load(camera_config);
        managers[i]-> addDisplay(displays[i], true);
        managers[i] ->initialize();

        titleLabels[i] = new QLabel();
        titleLabels[i]->setText(cameraTitles[i]);
        titleLabels[i]->setMaximumSize(10000,20);
        titleLabels[i]->adjustSize();
        titleLabels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);    //display_layout.addWidget(&title);
        titleLabels[i]->setAlignment(Qt::AlignCenter);
        titleLabels[i]->hide();
        panels[i]->hide();
    }
}

void CameraViewer::showWindow() {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,1);

    for (int i=0; i<3; i++) {
        switch (i) {
            case 0:            
                ui->rviz_layout->addWidget( titleLabels[i]  ,1,1 );
                ui->rviz_layout->addWidget( panels[i]       ,2,1 );
                break;
            case 1:
                ui->rviz_layout->addWidget( titleLabels[i]  ,3,0 );
                ui->rviz_layout->addWidget( panels[i]       ,4,0 );
                break;
            case 2:
                ui->rviz_layout->addWidget( titleLabels[i]  ,3,2 );
                ui->rviz_layout->addWidget( panels[i]       ,4,2 );
                break;
        }
        titleLabels[i]->show();
        managers[i]->startUpdate();
        panels[i]->show();
    }
    DAQViz::title->show();
    ui->rviz_layout->update();    
}

void CameraViewer::showWindow(int xpos, int ypos) {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,1);

    for (int i=0; i<3; i++) {
        switch (i) {
            case 0:            
                ui->rviz_layout->addWidget( titleLabels[i]  , xpos,1 );
                ui->rviz_layout->addWidget( panels[i]       ,xpos+1,1 );
                break;
            case 1:
                ui->rviz_layout->addWidget( titleLabels[i]  ,xpos,0 );
                ui->rviz_layout->addWidget( panels[i]       ,xpos+1,0 );
                break;
            case 2:
                ui->rviz_layout->addWidget( titleLabels[i]  ,xpos,2 );
                ui->rviz_layout->addWidget( panels[i]       ,xpos+1,2 );
                break;
        }
        titleLabels[i]->show();
        managers[i]->startUpdate();
        panels[i]->show();
    }
    DAQViz::title->show();
    ui->rviz_layout->update();    
}

void CameraViewer::closeWindow(){
    DAQViz::buttonState=ButtonState::OFF;
    DAQViz::title->hide();
    for (int i=0; i<3; i++) {
        panels[i]->hide();
        managers[i]->stopUpdate();
        ui->rviz_layout->removeWidget( panels[i]        );
        ui->rviz_layout->removeWidget( titleLabels[i]   );
        titleLabels[i]->hide();   
    }
    DAQViz::title->hide();
    ui->rviz_layout->removeWidget(DAQViz::title);
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

