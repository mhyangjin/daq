#!/usr/bin/env python
import rospy
import rostopic
from diagnostic.msg import Sensor_status

topics = [
        '/usb_cam_1/image_raw',
        '/usb_cam_2/image_raw',
        ]

rt = rostopic.ROSTopicHz(-1)

def check_hz():
    rospy.init_node('check_rostopic_hz', anonymous=False)

    pub = rospy.Publisher('diagnostic', Sensor_status, queue_size=10)
    monitor = Sensor_status()
    count = 1

    while not rospy.is_shutdown():
        for topic in topics:
            rospy.Subscriber(topic, rospy.AnyMsg, rt.callback_hz, callback_args=topic)
            rospy.sleep(0.5)

            # check USB_CAM_1
            if topic == '/usb_cam_1/image_raw':
                cam_1_hz = bool(rt.get_hz(topic))
                if cam_1_hz == True:
                    # print("USB_CAM_1 GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "USB_CAM_1"
                    monitor.status = 1
                    pub.publish(monitor)
                elif cam_1_hz == False:
                    # print("USB_CAM_1 BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "USB_CAM_1"
                    monitor.status = 0
                    pub.publish(monitor)

            # check USB_CAM_2
            elif topic == '/usb_cam_2/image_raw':
                cam_2_hz = bool(rt.get_hz(topic))
                if cam_2_hz == True:
                    # print("USB_CAM_2 GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "USB_CAM_2"
                    monitor.status = 1
                    pub.publish(monitor)
                elif cam_2_hz == False:
                    # print("USB_CAM_2 BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "USB_CAM_2"
                    monitor.status = 0
                    pub.publish(monitor)
        
        count += 1
    
    rospy.spin()

if __name__ == '__main__':
    try:
        check_hz()
    except rospy.ROSInitException:
        pass