//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : configration settion을 위한 dialog window
//======================================================================*/
#ifndef DIALOGCONFIG_H
#define DIALOGCONFIG_H

#include <QDialog>
#include "ConfigLoader.h"

namespace Ui {
class DialogConfig;
}

class DialogConfig : public QDialog
{
    Q_OBJECT
    public slots:
    void setRvizDir();
    void setRecordDir();
    void setScriptDir();
    void accept();
public:
    explicit DialogConfig(QWidget *parent = nullptr);
    ~DialogConfig();

private:
    Ui::DialogConfig *ui;
    ConfigLoader config;
};

#endif // DIALOGCONFIG_H
