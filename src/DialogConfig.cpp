#include "DialogConfig.h"
#include "ui_DialogConfig.h"

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
}

DialogConfig::~DialogConfig()
{
    delete ui;
}
