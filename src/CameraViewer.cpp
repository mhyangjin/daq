//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/
#include "CameraViewer.h"
#include "DaqCameraDisplay.h"
#include "YmlLoader.h"
#include <rviz/display.h>
#include <rviz/display_group.h>
#include <OgreRenderWindow.h>
#include <QDockWidget>

CameraViewer::CameraViewer(Ui::DaqMain* ui, QString _rvizName, QString _title)
:DAQViz(ui, _title),
rvizName(_rvizName)
{
    DAQViz::buttonState=ButtonState::OFF;
    loadConfig(rvizName, &config);
    if ( !config.isValid()) {
        exit(-1);
    } 
     
    panel_= new rviz::RenderPanel();  
    ROS_DEBUG("rviz::RenderPanel %p", panel_);
    manager= new rviz::VisualizationManager(panel_);
    panel_->initialize(manager->getSceneManager(), manager);
    manager->initialize();
    manager->load(config.mapGetChild("Visualization Manager"));
    ROS_DEBUG("----buildDisplay %s" ,qPrintable(manager->getFixedFrame()));
    buildDisplay();
    ROS_INFO("DAQ: Camera viewer is ready: %s",qPrintable(rvizName) );

}

CameraViewer::~CameraViewer() {
    delete panel_;
    delete manager;
}

void CameraViewer::buildDisplay() {
    rviz::DisplayGroup* dg=manager->getRootDisplayGroup();
    ROS_DEBUG("DisplayGroup-%d", dg->numDisplays());
    dg->setEnabled(false);
     for (int i=0; i<dg->numDisplays() && i < 3 ; i++) {
        rviz::ImageDisplay* displays=(rviz::ImageDisplay*)dg->getDisplayAt(i);
        rviz::RenderPanel* img_panel=(rviz::RenderPanel*)displays->getAssociatedWidget();
        img_panel->setWindowFlags(Qt::FramelessWindowHint);
        img_panel->setDisabled(true);
        img_panel->resize(QSize(0,0));
        ui->camera_hidden->addWidget( img_panel);
        img_panel->hide();
            
        titleLabels[i] = new QLabel();
        titleLabels[i]->setText(cameraTitles[i]);
        titleLabels[i]->setMaximumSize(10000,20);
        titleLabels[i]->adjustSize();
        titleLabels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);    
       //display_layout.addWidget(&title);
        titleLabels[i]->setAlignment(Qt::AlignCenter);
        titleLabels[i]->hide();
        
    }
}

void CameraViewer::showWindow() {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,1);
    manager->lockRender();
    rviz::DisplayGroup* dg=manager->getRootDisplayGroup();
    ROS_DEBUG(" showWindow DisplayGroup-%d", dg->numDisplays());
    dg->setEnabled(true);
    for (int i=0; i<dg->numDisplays()  && i < 3 ; i++) {
        rviz::ImageDisplay* displays=(rviz::ImageDisplay*)dg->getDisplayAt(i);
        displays->reset();
        rviz::RenderPanel* img_panel=(rviz::RenderPanel*)displays->getAssociatedWidget();
        ui->camera_hidden->removeWidget( img_panel );  
        img_panel->setEnabled(true);
        switch (i) {
            case 0:      
                ui->rviz_layout->addWidget( titleLabels[i]  ,1,1 );
                //ui->rviz_layout->addWidget( widget      ,2,1 );
                ui->rviz_layout->addWidget( img_panel       ,2,1 );
                break;
            case 1:
                ui->rviz_layout->addWidget( titleLabels[i]  ,3,0 );
                //ui->rviz_layout->addWidget( widget      ,4,0 );
                ui->rviz_layout->addWidget( img_panel       ,4,2 );
                break;
            case 2:
                ui->rviz_layout->addWidget( titleLabels[i]  ,3,2 );
                //ui->rviz_layout->addWidget( widget      ,4,2 );
                ui->rviz_layout->addWidget( img_panel       ,4,0 );
                break;
            
        }
        img_panel->show();
        img_panel->adjustSize();
        img_panel->raise();
        titleLabels[i]->show();
        
    }
    manager->unlockRender();
    manager->startUpdate();
    DAQViz::title->show();
    ui->rviz_layout->update();   
    ui->camera_hidden->update(); 
}

void CameraViewer::showWindow(int xpos, int ypos) {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,1);
    manager->lockRender();
    rviz::DisplayGroup* dg=manager->getRootDisplayGroup();
    dg->setEnabled(true);
    ROS_DEBUG(" showWindow DisplayGroup-%d", dg->numDisplays());
    
    for (int i=0; i<dg->numDisplays() && i < 3 ; i++) {
        rviz::ImageDisplay* displays=(rviz::ImageDisplay*)dg->getDisplayAt(i);
        displays->reset();
        rviz::RenderPanel* img_panel=(rviz::RenderPanel*)displays->getAssociatedWidget();
        
        ui->camera_hidden->removeWidget( img_panel  );  
        img_panel->setEnabled(true);
        switch (i) {
            case 0:            
                ui->rviz_layout->addWidget( titleLabels[i]  , xpos,1 );
                //ui->rviz_layout->addWidget( docks[i]       ,xpos+1,1 );
                ui->rviz_layout->addWidget( img_panel       ,xpos+1,1 );
                break;
            case 1:
                ui->rviz_layout->addWidget( titleLabels[i]  ,xpos,0 );
                //ui->rviz_layout->addWidget( docks[i]       ,xpos+1,0 );
                ui->rviz_layout->addWidget( img_panel       ,xpos+1,2 );
                break;
            case 2:
                ui->rviz_layout->addWidget( titleLabels[i]  ,xpos,2 );
                //ui->rviz_layout->addWidget( docks[i]       ,xpos+1,2 );
                ui->rviz_layout->addWidget( img_panel       ,xpos+1,0 );
                break;
        }
        img_panel->show();
        img_panel->adjustSize();
        img_panel->raise();
        titleLabels[i]->show();
    }
    manager->unlockRender();
    manager->startUpdate();
    DAQViz::title->show();
    ui->rviz_layout->update();  
    ui->camera_hidden->update();  
}

void CameraViewer::closeWindow(){
    DAQViz::buttonState=ButtonState::OFF;
    DAQViz::title->hide();
    manager->lockRender();
    manager->stopUpdate();
    rviz::DisplayGroup* dg=manager->getRootDisplayGroup();
    dg->setEnabled(false);
    ROS_DEBUG(" closeWindow DisplayGroup-%d", dg->numDisplays());
    
    for (int i=0; i<dg->numDisplays() && i < 3 ; i++) {
        rviz::ImageDisplay* displays=(rviz::ImageDisplay*)dg->getDisplayAt(i);
        rviz::RenderPanel* img_panel=(rviz::RenderPanel*)displays->getAssociatedWidget();
        img_panel->setDisabled(true);
        img_panel->hide();
        ui->rviz_layout->removeWidget( img_panel        );
        ui->rviz_layout->removeWidget( titleLabels[i]   );
        titleLabels[i]->hide();   
        ui->camera_hidden->addWidget( img_panel );  
        
    }

    DAQViz::title->hide();
    manager->unlockRender();
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->update();
    ui->camera_hidden->update();  
}



void CameraViewer::loadConfig( QString rvizFileName,rviz::Config *config) {
    YmlLoader::loadConfig(rvizFileName, config);
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
                config->mapSetValue(QString::fromStdString(nodeStr),QString::fromStdString(valueStr));
                break;
            case YAML::NodeType::Sequence:
                childConfig=config->mapMakeChild(QString::fromStdString(nodeStr));
                
                for (size_t i=0; i< _value.size(); i++) {
                    YAML::Node arrayValue=_value[i];
                    rviz::Config seqConfig=childConfig.listAppendNew();
                    if (arrayValue.Type() == YAML::NodeType::Scalar) {
                        valueStr=arrayValue.as<string>();
                        seqConfig.setValue(QString::fromStdString(valueStr));
                    }
                    else 
                        loadNodes(&arrayValue, &seqConfig);
                }
                break;
            case YAML::NodeType::Map:

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

