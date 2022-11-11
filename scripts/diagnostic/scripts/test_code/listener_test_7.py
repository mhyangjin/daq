#!/usr/bin/env python
import rospy
import rostopic
from sensor_msgs.msg import Image
from std_msgs.msg import String, Int8
from diagnostic.msg import sensor_status

topics = [
        '/usb_cam_1/image_raw',
        '/usb_cam_2/image_raw',
        ]

rt = rostopic.ROSTopicHz(-1)

# def usb_cam_1_status(s):
#     usb_cam_1_pub = rospy.Publisher('usb_cam_1_status', sensor_status, queue_size=10)
#     status = sensor_status()
#     status.sensor_name = "USB_CAM_1"
#     status.condition = 1

#     usb_cam_1_pub.publish(status)

# def usb_cam_2_status(d):
#     usb_cam_2_pub = rospy.Publisher('usb_cam_2_status', sensor_status, queue_size=10)
#     status = sensor_status()
#     status.sensor_name = "USB_CAM_2"
#     status.condition = 0

#     usb_cam_2_pub.publish(status)

def check_hz():
    rospy.init_node('check_hz', anonymous=True)

    for topic in topics:
        rospy.Subscriber(topic, rospy.AnyMsg, rt.callback_hz, callback_args=topic)
        rospy.sleep(1)
        if topic == '/usb_cam_1/image_raw':
            cam_1_hz = rt.get_hz(topic)
            print(cam_1_hz)
        elif topic == '/usb_cam_2/image_raw':
            cam_2_hz = rt.get_hz(topic)
            print(cam_2_hz)

    rospy.spin()

if __name__ == '__main__':
    check_hz()