#!/usr/bin/env python
import rospy
import sys
from std_msgs.msg import String
from daq.msg import Radar,Sim,Track
import random

def talker():
    pub = rospy.Publisher('/can/radar', Radar, queue_size=10)
    rospy.init_node('car', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    #rand_status =random.randrange(0,2)
    rand_status=1
    
    while not rospy.is_shutdown():
        radar_msg=Radar()
        int=0
        for i in range(0,64):
            track_msg=Track()
            track_msg.track_oncoming=True
            track_msg.track_grouping_changed=True
            track_msg.track_lat_rate=random.randrange(0,10000)
            track_msg.track_status=random.randrange(0,100)
            track_msg.track_angle=random.randrange(0,10000)
            track_msg.track_range=random.randrange(0,10000)
            track_msg.track_width=random.randrange(0,10000)
            track_msg.track_rolling_count=False
            track_msg.track_bridge_object=False
            track_msg.track_range_accel=random.randrange(0,10000)
            track_msg.track_med_range_mode=random.randrange(0,100)
            track_msg.track_range_rate=random.randrange(0,10000)
            radar_msg.tracks[i]=track_msg
        sim_msg=Sim()
        sim_msg.sim_function=random.randrange(0,100)
        sim_msg.sim_status=random.randrange(0,100)
        sim_msg.sim_track_id=random.randrange(0,100)
        sim_msg.sim_angle=random.randrange(0,10000)
        sim_msg.sim_lat_pos=random.randrange(0,10000)
        sim_msg.sim_lat_rate=random.randrange(0,10000)
        sim_msg.sim_range=random.randrange(0,100)
        sim_msg.sim_range_accel=random.randrange(0,10000)
        sim_msg.sim_range_rate=random.randrange(0,10000)
        radar_msg.sim=sim_msg
        pub.publish(radar_msg)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
