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

def usb_cam_1_status(s):
    usb_cam_1_pub = rospy.Publisher('usb_cam_1_status', sensor_status, queue_size=10)
    status = sensor_status()
    status.sensor_name = "USB_CAM_1"
    status.condition = 1

    usb_cam_1_pub.publish(status)

def usb_cam_2_status(d):
    usb_cam_2_pub = rospy.Publisher('usb_cam_2_status', sensor_status, queue_size=10)
    status = sensor_status()
    status.sensor_name = "USB_CAM_2"
    status.condition = 0

    usb_cam_2_pub.publish(status)

def check_topic():
    rospy.init_node('check_topic', anonymous=True)

    for topic in topics:
        rospy.Subscriber(topic, rospy.AnyMsg)
        if topic == '/usb_cam_1/image_raw':
            check_usb_cam_1 = rospy.Subscriber('/usb_cam_1/image_raw', Image)
            print(check_usb_cam_1)
            if check_usb_cam_1 == True:
                print("USB_CAM_1_OK")
            elif check_usb_cam_1 == False:
                print("USB_CAM_1_Fail")
        elif topic == '/usb_cam_2/image_raw':
            check_usb_cam_2 = bool(rospy.Subscriber('/usb_cam_2/image_raw', Image))
            if check_usb_cam_2 == True:
                print(check_usb_cam_2)
                print("USB_CAM_2_OK")
            elif check_usb_cam_2 == False:
                print("USB_CAM_2_Fail")

    rospy.spin()

if __name__ == '__main__':
    check_topic()