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

rt = rostopic.ROSTopicHz(-1)

def initMonitorRostopic():
    global rt

    rospy.init_node('diagnostic', anonymous=True)

    # for topic in topics:
    #     rospy.Subscriber(topic, rospy.AnyMsg, rt.callback_hz, callback_args=topic, tcp_nodelay=False)
    #     print("subscribed to [%s]" % topic)
    #     if topic == '/usb_cam_1/image_raw':
    #         rt.get_hz('/usb_cam_1/image_raw')
    #     elif topic == '/usb_cam_2/image_raw':
    #         rt.get_hz('/usb_cam_2/image_raw')

    rospy.Subscriber('/usb_cam_2/image_raw', Image, rt.callback_hz, callback_args='/usb_cam_2/image_raw')
    rospy.sleep(1)
    hz = rt.get_hz('/usb_cam_2/image_raw')
    print(hz[0])
    
    rospy.spin()

if __name__ == '__main__':
    initMonitorRostopic()