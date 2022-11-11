#!/usr/bin/env python
import rospy
import rostopic
from sensor_msgs.msg import Image
from std_msgs.msg import String, Int8
from diagnostic.msg import sensor_status

topics = [
        '/usb_cam_1/image_raw',
        '/usb_cam_2/image_raw'
        ]

# def pub_diagnostic(msg):
#     pub = rospy.Publisher('diagnostic', String, Int8, queue_size=10)

#     rate = rospy.Rate(1) # 1hz

    
#     pub.publish(monitor)
#     rate.sleep()

def usb_cam_1_status(msg):
    print(msg.Image)

def usb_cam_2_status(msg):
    print(msg.Image)
    

def check_topic():
    rospy.init_node('check_topic', anonymous=True)

    for topic in topics:
        rospy.Subscriber(topic, rospy.AnyMsg)
        if topic == '/usb_cam_1/image_raw':
            rospy.Subscriber('/usb_cam_1/image_raw', Image, usb_cam_1_status)
        elif topic == '/usb_cam_2/image_raw':
            rospy.Subscriber('/usb_cam_2/image_raw', Image, usb_cam_2_status)

    rospy.spin()

if __name__ == '__main__':
    check_topic()