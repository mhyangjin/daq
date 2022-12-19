#!/usr/bin/env python
import rospy
import sys
from std_msgs.msg import String
from daq.msg import Car,Can
import random

def talker():
    pub = rospy.Publisher('/can', Car, queue_size=10)
    rospy.init_node('car', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    #rand_status =random.randrange(0,2)
    rand_status=1
    count=1
    while not rospy.is_shutdown():
        can_msg=Can()
        car_msg=Car()
        car_msg.veh_speed=random.randrange(0,10000)
        car_msg.yaw_rate=random.randrange(0,10000)
        car_msg.lon_accel=random.randrange(0,10000)
        car_msg.lat_accel=random.randrange(0,10000)
        can_msg.car=car_msg
        pub.publish(can_msg)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
