#!/usr/bin/env python3

from os import O_NONBLOCK, O_RDONLY
import rospy
from sensor_msgs.msg import NavSatFix, Imu

import json
import datetime
import os
import errno

PIPE_NAME='sensor_status'

curr_sensor_status = {}
curr_sensor_status['USB_CAM_1'] = 0xff
curr_sensor_status['USB_CAM_2']   = 0xff

try:
    os.mkfifo(PIPE_NAME)
except OSError as oe: 
    if oe.errno != errno.EEXIST:
        raise

fifo = os.open( PIPE_NAME, O_NONBLOCK | O_RDONLY)

def delivery_report(err, msg):
    """ Called once for each message produced to indicate delivery result.
        Triggered by poll() or flush(). """
    if err is not None:
        print('Message delivery failed: {}'.format(err))
    else:
        print('Message delivered to {} [{}]'.format(msg.topic(), msg.partition()))

def readSensorStatus():
    global curr_sensor_status
    try:
        data = os.read(fifo, 200)
        if not data:
            pass
        else:
            content = data.decode("utf-8").split("\n")
            curr_sensor_status = json.loads(content[0])
            print("===== sensor_status is updated")
            # print(sensor_status)

    except OSError as e:
        if e.errno == 11:
            # grace period, first write to pipe might take some time
            # further reads after opening the file are then successful
            pass
        else:
            print(f'Exception {e}')

def makeMessage():
    msg = {}
    sensor_status = {}
    message = {}

    readSensorStatus()
    sensor_status = curr_sensor_status

    message['sensor_status'] = sensor_status

    msg['message'] = message

    values = json.dumps(msg)
    return values

def listener():
    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.

    rospy.init_node('vehicle_info', anonymous=True)

    # spin() simply keeps python from exiting until this node is stopped
    # rospy.spin()
    rate = rospy.Rate(1)    # 1Hz
    while not rospy.is_shutdown():
        rate.sleep()

        # rospy.loginfo( rospy.get_caller_id() + 'SteeringAngle=%s', cinfo.SteeringAngle)
        # rospy.loginfo( 'SteeringAngle=%s', cinfo.SteeringAngle)

        # values = makeMessage()


if __name__ == '__main__':
    listener()

# os.close(fifo)
fifo.close()