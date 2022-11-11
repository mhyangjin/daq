#!/usr/bin/env python3from numpy import real

import requests
# from bs4 import BeautifulSoup
import threading
import json

# from selenium import webdriver
# from selenium.webdriver.firefox.options import Options

import pyudev
import os
import sys
import errno
import rospy
import rostopic

NAME='sensor_status'

TIMEOUT = 1
MASK_CONN = 0x01
MASK_MSG  = 0x02
MASK_DIAG = 0x04

topics = []

rt = rostopic.ROSTopicHz(-1)

sensor_status = {}

sensor_status['USB_CAM_1'] = 0xff
sensor_status['USB_CAM_2']   = 0xff

PIPE_NAME='sensor_status'

try:
    os.mkfifo(PIPE_NAME)
except OSError as oe: 
    if oe.errno != errno.EEXIST:
        raise

fifo = os.open(PIPE_NAME, os.O_WRONLY)

def getStatus_USB( key, device_file):
    context = pyudev.Context()
    try:
        bitmask = sensor_status[key] | (MASK_CONN | MASK_DIAG)
        device = pyudev.Devices.from_device_file(context, device_file)
        info = { item[0] : item[1] for item in device.items()}
        bitmask &= ~MASK_CONN
    except:
        pass
    finally:
        sensor_status[key] = bitmask

def initMonitorRostopic():
    global rt

    rospy.init_node(NAME, anonymous=True)

    for topic in topics:
        rospy.Subscriber(topic, rospy.AnyMsg, rt.callback_hz, callback_args=topic, tcp_nodelay=False)
        print("subscribed to [%s]" % topic)

    if rospy.get_param('use_sim_time', False):
        print("WARNING: may be using simulated time",file=sys.stderr)

def updateStatus( key, topic):
    try:
        bitmask = sensor_status[key] | MASK_MSG
        hz = rt.get_hz(topic)
        # rt.print_hz(topics)
        if hz is not None:
            # print( f'{key} => {hz} {hz[0]}')
            if hz[0] != 0:
                bitmask &= ~MASK_MSG
    except:
        print(f' No key {key}')
        pass
    finally:
        sensor_status[key] = bitmask

def thread_run():

    print(f'...Starting Monitor')
    while not rospy.is_shutdown():
        rostopic._sleep(5.0)

        getStatus_USB( 'USB_CAM_1',   '/dev/video0')
        getStatus_USB( 'USB_CAM_2',  '/dev/video2')

        updateStatus( 'USB_CAM_1', '/usb_cam_1/image_raw')
        updateStatus( 'USB_CAM_2', '/usb_cam_2/image_raw')


        print(sensor_status)
        json_object = json.dumps(sensor_status)
        os.write( fifo, json_object.encode('utf-8'))

def start_Monitor():
    """ Basic thread safety tests. """

    print(f'...Starting Monitor')
    thr = threading.Thread(target=thread_run, name='main')

    thr.start()
    thr.join()

    print('Monitor is done')

if __name__ == '__main__':
    initMonitorRostopic()
    # start_Monitor()
    thread_run()

os.close(fifo)
