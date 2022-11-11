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
    pub = rospy.Publisher('diagnostic', sensor_status, queue_size=10)
    rate = rospy.Rate(1) # 10hz
    status = sensor_status()
    count = 1

    for topic in topics:
        if topic == '/usb_cam_1/image_raw':
            status.seq = count
            status.stamp = rospy.Time.now()
            status.sensor_name = "USB_CAM_1"
            status.condition = 1
            pub.publish(status)
        elif topic == '/usb_cam_2/image_raw':
            status.seq = count
            status.stamp = rospy.Time.now()
            status.sensor_name = "USB_CAM_2"
            status.condition = 0
            pub.publish(status)
    count += 1

    rate.sleep()

def check_topic():
    global topic
    rospy.init_node('check_topic', anonymous=True)

    for topic in topics:
        rospy.Subscriber(topic, rospy.AnyMsg, diagnostic)

    rospy.spin()

if __name__ == '__main__':
    check_topic()