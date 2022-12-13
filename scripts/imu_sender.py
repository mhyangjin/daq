#!/usr/bin/env python
import rospy
import sys
from sensor_msgs.msg  import Imu
import random

def talker():
    pub = rospy.Publisher('/gps/imu', Imu, queue_size=10)
    rospy.init_node('gps', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    #rand_status =random.randrange(0,2)
    rand_status=1
    count=1
    while not rospy.is_shutdown():
        imu_msg=Imu()
        pub.publish(imu_msg)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
