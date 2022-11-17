//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : configration settion을 위한 dialog window
//======================================================================*/
#include "DialogConfig.h"
#include "ui_DialogConfig.h"
#include <QFileDialog>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    connect(ui->btn_record,SIGNAL(clicked()), this, SLOT(setRecordDir()));
    connect(ui->btn_script,SIGNAL(clicked()), this, SLOT(setScriptDir()));
    connect(ui->btn_rviz, SIGNAL(clicked()), this, SLOT(setRvizDir()));
}

DialogConfig::~DialogConfig()
{
    delete ui;
}

void DialogConfig::setScriptDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open script Directory", "/home/mhjin/project", QFileDialog::ShowDirsOnly);
    ui->label_script->setText(dir);
}
void DialogConfig::setRvizDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open rviz Directory", "/home/mhjin/project", QFileDialog::ShowDirsOnly);
    ui->label_rviz->setText(dir);
}
void DialogConfig::setRecordDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open record Directory", "/home/mhjin/project", QFileDialog::ShowDirsOnly);
    ui->label_record->setText(dir);
}
void DialogConfig::accept() {

}
