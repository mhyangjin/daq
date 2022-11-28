#!/usr/bin/env python
import rospy
import rostopic
from daq.msg import Sensor_status

topics = [
        '/front_camera/image_raw',
        '/right_camera/image_raw',
        '/left_camera/image_raw',
        '/os_cloud_node/points',
        '/right_velodyne/velodyne_points',
        '/left_velodyne/velodyne_points',
        '/gps/fix',
        '/gps/imu',
        '/can'
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
            rospy.sleep(0.1)

            # check Front_Camera
            if topic == '/front_camera/image_raw':
                front_camera_check = bool(rt.get_hz(topic))
                if front_camera_check == True:
                    # print("Front_Camera GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Front_Camera"
                    monitor.status = 1
                    pub.publish(monitor)
                elif front_camera_check == False:
                    # print("Front_Camera BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Front_Camera"
                    monitor.status = 0
                    pub.publish(monitor)

            # check Right_Camera
            elif topic == '/right_camera/image_raw':
                right_camera_check = bool(rt.get_hz(topic))
                if right_camera_check == True:
                    # print("Right_Camera GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Right_Camera"
                    monitor.status = 1
                    pub.publish(monitor)
                elif right_camera_check == False:
                    # print("Right_Camera BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Right_Camera"
                    monitor.status = 0
                    pub.publish(monitor)

            # check Left_Camera
            elif topic == '/left_camera/image_raw':
                left_camera_check = bool(rt.get_hz(topic))
                if left_camera_check == True:
                    # print("Left_Camera GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Left_Camera"
                    monitor.status = 1
                    pub.publish(monitor)
                elif left_camera_check == False:
                    # print("left_Camera BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Left_Camera"
                    monitor.status = 0
                    pub.publish(monitor)

            # check Top_LiDAR
            elif topic == '/os_cloud_node/points':
                top_lidar_check = bool(rt.get_hz(topic))
                if top_lidar_check == True:
                    # print("Top_LiDAR GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Top_LiDAR"
                    monitor.status = 1
                    pub.publish(monitor)
                elif top_lidar_check == False:
                    # print("Top_LiDAR BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Top_LiDAR"
                    monitor.status = 0
                    pub.publish(monitor)

            # check Right_LiDAR
            elif topic == '/right_velodyne/velodyne_points':
                right_lidar_check = bool(rt.get_hz(topic))
                if right_lidar_check == True:
                    # print("Right_LiDAR GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Right_LiDAR"
                    monitor.status = 1
                    pub.publish(monitor)
                elif right_lidar_check == False:
                    # print("Right_LiDAR BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Right_LiDAR"
                    monitor.status = 0
                    pub.publish(monitor)

            # check Left_LiDAR
            elif topic == '/left_velodyne/velodyne_points':
                left_lidar_check = bool(rt.get_hz(topic))
                if left_lidar_check == True:
                    # print("Left_LiDAR GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Left_LiDAR"
                    monitor.status = 1
                    pub.publish(monitor)
                elif left_lidar_check == False:
                    # print("Left_LiDAR BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "Left_LiDAR"
                    monitor.status = 0
                    pub.publish(monitor)

            # check GPS
            elif topic == '/gps/fix':
                gps_check = bool(rt.get_hz(topic))
                if gps_check == True:
                    # print("GPS GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "GPS"
                    monitor.status = 1
                    pub.publish(monitor)
                elif gps_check == False:
                    # print("GPS BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "GPS"
                    monitor.status = 0
                    pub.publish(monitor)

            # check IMU
            elif topic == '/gps/imu':
                imu_check = bool(rt.get_hz(topic))
                if imu_check == True:
                    # print("IMU GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "IMU"
                    monitor.status = 1
                    pub.publish(monitor)
                elif imu_check == False:
                    # print("IMU BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "IMU"
                    monitor.status = 0
                    pub.publish(monitor)

            # check CAN
            elif topic == '/can':
                can_check = bool(rt.get_hz(topic))
                if can_check == True:
                    # print("CAN GOOD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "CAN"
                    monitor.status = 1
                    pub.publish(monitor)
                elif can_check == False:
                    # print("CAN BAD")
                    monitor.seq = count
                    monitor.stamp = rospy.Time.now()
                    monitor.sensor_name = "CAN"
                    monitor.status = 0
                    pub.publish(monitor)
        
        count += 1
    
    rospy.spin()

if __name__ == '__main__':
    try:
        check_hz()
    except rospy.ROSInitException:
        pass