#!/usr/bin/env python
import rospy
import sys
from std_msgs.msg import String
import Sensor_status
import random

def talker():
    pub = rospy.Publisher('diagnostic', Sensor_status, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1) # 10hz
    #rand_status =random.randrange(0,2)
    rand_status=1
    count=1
    while not rospy.is_shutdown():
        fcam_msg = Sensor_status()
        fcam_msg.seq = count
        fcam_msg.stamp = rospy.Time.now()
        fcam_msg.sensor_name = "Front_Camera"
        fcam_msg.status = rand_status
        pub.publish(fcam_msg)
        
        rcam_msg = Sensor_status()
        rcam_msg.seq = count
        rcam_msg.stamp = rospy.Time.now()
        rcam_msg.sensor_name = "Right_Camera"
        rcam_msg.status = rand_status
        pub.publish(rcam_msg)

        lcam_msg = Sensor_status()
        lcam_msg.seq = count
        lcam_msg.stamp = rospy.Time.now()
        lcam_msg.sensor_name = "Left_Camera"
        lcam_msg.status = rand_status
        pub.publish(lcam_msg)

        tLi_msg = Sensor_status()
        tLi_msg.seq = count
        tLi_msg.stamp = rospy.Time.now()
        tLi_msg.sensor_name = "Top_LiDAR"
        tLi_msg.status = rand_status
        pub.publish(tLi_msg)

        rLi_msg = Sensor_status()
        rLi_msg.seq = count
        rLi_msg.stamp = rospy.Time.now()
        rLi_msg.sensor_name = "Right_LiDAR"
        rLi_msg.status = rand_status
        pub.publish(rLi_msg)

        LLi_msg = Sensor_status()
        LLi_msg.seq = count
        LLi_msg.stamp = rospy.Time.now()
        LLi_msg.sensor_name = "Left_LiDAR"
        LLi_msg.status = rand_status
        pub.publish(LLi_msg)

        gps_msg = Sensor_status()
        gps_msg.seq = count
        gps_msg.stamp = rospy.Time.now()
        gps_msg.sensor_name = "GPS"
        gps_msg.status = rand_status
        pub.publish(gps_msg)

        imu_msg = Sensor_status()
        imu_msg.seq = count
        imu_msg.stamp = rospy.Time.now()
        imu_msg.sensor_name = "IMU"
        imu_msg.status = rand_status
        pub.publish(imu_msg)

        can_msg = Sensor_status()
        can_msg.seq = count
        can_msg.stamp = rospy.Time.now()
        can_msg.sensor_name = "CAN"
        can_msg.status = 1
        pub.publish(can_msg)

        count +=1;
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
