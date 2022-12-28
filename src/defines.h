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

enum SensorMode {
    SENSOR=0,
    REPLAY=1
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

//all view 일경우만 적용됨
enum FRAME_NAME {
    F_CAMERA=0,          //초당 frame 수, default=30으로 세팅하려면 0
    F_LIDAR_TOP,       //초당 frame 수, default=30으로 세팅하려면 0
    F_LIDAR_SIDE,      //초당 frame 수, default=30으로 세팅하려면 0
    F_RADAR,           //signal interval 개수. N개중 1개만 display.  모두 일 경우 0
    F_GPS,             //signal interval 개수. N개중 1개만 display.  모두 일 경우 0
    F_CAR,             //signal interval 개수. N개중 1개만 display.  모두 일 경우 0
    F_IMU              //signal interval 개수. N개중 1개만 display.  모두 일 경우 0
};

const int FRAME_CNT[7] = {
    10, //  FRAME_CNT[F_CAMERA]       :초당 frame 수, default=30으로 세팅하려면 0
    10, //  FRAME_CNT[F_LIDAR_TOP]    :초당 frame 수, default=30으로 세팅하려면 0
    10, //  FRAME_CNT[F_LIDAR_SIDE]   :초당 frame 수, default=30으로 세팅하려면 0
    0, //  FRAME_CNT[F_RADAR]        :signal interval 개수. N개중 1개만 display.  모두 일 경우 0
    0, //  FRAME_CNT[F_GPS]          :signal interval 개수. N개중 1개만 display.  모두 일 경우 0
    0, //  FRAME_CNT[F_CAR]          :signal interval 개수. N개중 1개만 display.  모두 일 경우 0
    0  //  FRAME_CNT[F_IMU]          :signal interval 개수. N개중 1개만 display.  모두 일 경우 0
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