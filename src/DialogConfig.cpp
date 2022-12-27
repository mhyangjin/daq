//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : configration settion을 위한 dialog window
//======================================================================*/
#include "DialogConfig.h"
#include "ui_DialogConfig.h"
#include <QFileDialog>

static ConfigLoader config;
DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    ui->label_record->setText(config.getRecordConfig());
    ui->label_rviz->setText(config.getRvizConfig());
    ui->label_script->setText(config.getScriptConfig());
    connect(ui->btn_record,SIGNAL(clicked()), this, SLOT(setRecordDir()));
    connect(ui->btn_rviz, SIGNAL(clicked()), this, SLOT(setRvizDir()));
    connect(ui->btn_script, SIGNAL(clicked()), this, SLOT(setScriptDir()));
}

DialogConfig::~DialogConfig()
{
    delete ui;
}

void DialogConfig::setRvizDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open rviz Directory", config.getRvizConfig(), QFileDialog::ShowDirsOnly);
    ui->label_rviz->setText(dir);
}

void DialogConfig::setScriptDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open Script Directory", config.getScriptConfig(), QFileDialog::ShowDirsOnly);
    ui->label_script->setText(dir);
}

void DialogConfig::setRecordDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open record Directory", config.getRecordConfig(), QFileDialog::ShowDirsOnly);
    ui->label_record->setText(dir);
}
void DialogConfig::accept() {
    config.saveConfig();
    close();

}
