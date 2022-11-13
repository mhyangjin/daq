rosrun daq talker.py /gps/fix &
rosrun daq talker.py /gps/imu &
rosrun daq talker.py /can/radar &
rosrun daq talker.py /can/car &
rosrun daq diagnostic_talker.py /can/car &