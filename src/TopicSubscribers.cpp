//======================================================================*/
//   Create Date: 2022/11/12
//   ClassName  : TopicSubscribers
//   Author     : mhjin julu1@naver.com
//   Class Def  : 모든 topic을 모두 sub하기 위한 클래스
//                ros::spin() thread를 block하고 대기하여, 여러개의 topic을
//                함께 sub할 수 없다.
//                multi-thread여야 하기 때문에 ros::spiner를 사용한다.
//======================================================================*/
#include "TopicSubscribers.h"
#include <sstream>

template <class T>
TopicSubscribers<T>::TopicSubscribers(QString _topicName,ros::MultiThreadedSpinner* _spiner)
:spiner(_spiner),
topicName(_topicName)
{
    //ros::start();
    SignalsSlot::qstringList.insertRows(0, 1);
    subscriber = nodeHandle.subscribe(qPrintable(topicName), 100, &TopicSubscribers<T>::subscribeCallBack,this );
    this->start();

}

template <class T>
void TopicSubscribers<T>::run() {
    spiner->spin();
}

template <class T>
void TopicSubscribers<T>::subscribeCallBack(const typename T::ConstPtr& messages) {
    stringstream  ss;
    ss<<*messages;
    QString _data=QString::fromStdString(ss.str());
    QVariant new_data(_data);
    SignalsSlot::qstringList.setData(SignalsSlot::qstringList.index(SignalsSlot::qstringList.rowCount()-1), new_data);
 //   Q_EMIT SignalsSlot::dataUpdated();
}

//template class를 사용할때 명시적으로 타입을 선언하지 않으면 binary link 시점에 에러가 발생한다.
//C++  compiler 문제.
template class TopicSubscribers<sensor_msgs::NavSatFix>;
template class TopicSubscribers<sensor_msgs::Imu>;
template class TopicSubscribers<daq::Radar>;
template class TopicSubscribers<daq::Car>;
template class TopicSubscribers<daq::Sensor_status>;