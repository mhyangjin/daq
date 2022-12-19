//======================================================================*/
//   Create Date: 2022/11/12
//   ClassName  : CanSubscribers
//   Author     : mhjin julu1@naver.com
//   Class Def  : 모든 topic을 모두 sub하기 위한 클래스
//                ros::spin() thread를 block하고 대기하여, 여러개의 topic을
//                함께 sub할 수 없다.
//                multi-thread여야 하기 때문에 ros::spiner를 사용한다.
//======================================================================*/
#include "CanSubscribers.h"
#include <sstream>

CanSubscribers::CanSubscribers(QString _topicName,ros::MultiThreadedSpinner* _spiner)
:spiner(_spiner),
topicName(_topicName)
{
    subscriber = nodeHandle.subscribe("/can", 100, &CanSubscribers::subscribeCallBack,this );
    this->start();
}

void CanSubscribers::run() {
    spiner->spin();
}

void CanSubscribers::subscribeCallBack(const daq::Can& messages) {
    //ROS_DEBUG("CAR  SIZE : %d, RADAR SIZE: %d", sizeof(messages.car), sizeof(messages.radar));
    stringstream  ss;
    if ( topicName.contains("car") ) {
        daq::Car car_msg=messages.car;
        ss<<car_msg;
    }
    else if ( topicName.contains("radar") ) {
        daq::Radar radar_msg=messages.radar;
        ss<<radar_msg;
    }
    
    QString _data=QString::fromStdString(ss.str());
    Q_EMIT SignalsSlot::dataUpdated(_data);
}
