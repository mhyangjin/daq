#!/usr/bin/env python
import rospy
import sys
from sensor_msgs.msg import NavSatFix
import random

def talker():
    pub = rospy.Publisher('/gps/fix', NavSatFix, queue_size=10)
    rospy.init_node('gps', anonymous=True)
    rate = rospy.Rate(1) # 10hz
    #rand_status =random.randrange(0,2)
    rand_status=1
    count=1
    while not rospy.is_shutdown():
        gps_msg=NavSatFix()
        pub.publish(gps_msg)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
