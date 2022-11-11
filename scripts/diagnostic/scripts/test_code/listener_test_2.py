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

def diagnostic(msg):
    for topic in topics:
        if topic == '/usb_cam_1/image_raw':
            usb_cam_1_pub = rospy.Publisher('usb_cam_1_status', sensor_status, queue_size=10)
            status = sensor_status()
            status.sensor_name = "USB_CAM_1"
            status.condition = 1
            usb_cam_1_pub.publish(status)
        elif topic == '/usb_cam_2/image_raw':
            usb_cam_2_pub = rospy.Publisher('usb_cam_2_status', sensor_status, queue_size=10)
            status = sensor_status()
            status.sensor_name = "USB_CAM_2"
            status.condition = 0
            usb_cam_2_pub.publish(status)

def check_topic():
    global topic
    rospy.init_node('check_topic', anonymous=True)

    for topic in topics:
        rospy.Subscriber(topic, rospy.AnyMsg, diagnostic)

    rospy.spin()

if __name__ == '__main__':
    check_topic()