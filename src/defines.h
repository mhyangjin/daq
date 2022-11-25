//======================================================================*/
//   Create Date: 2022/11/1
//   ClassName  : Define
//   Author     : mhjin julu1@naver.com
//   Class Def  : labename, sensor name등 기본 설정
//======================================================================*/
#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QStringList>

enum ButtonState {
    OFF=0,
    ON=1   
};
enum AcquisitonStateEnum {
    DEFAULT=0,
    RUN,
    STOP
};

enum StsName {
    CAM_F1=0,
    CAM_S1,
    CAM_S2,
    IMU,
    CAR,
    RADAR,
    LIDAR_T1,
    LIDAR_S1,
    LIDAR_S2,
    GPS
};

// sensor 상태를 표시할 수 있는 상태 이미지 파일
//AcquisitonStateEnum enum의 순서와 1대1 mapping된다.
const QString img_source[3]={
    ":img/images/state_gray.png",
    ":img/images/state_blue.png",
    ":img/images/state_red.png"
};

const QString pubName="/diagnostic";

//const QString pubName="/diagnosticss";
#endif