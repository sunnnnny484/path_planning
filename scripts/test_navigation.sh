#!/bin/sh

export TURTLEBOT3_MODEL='waffle_pi'

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_world.launch " &
sleep 10

xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch " &
sleep 10

#xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch " &
#sleep 5

#xterm  -e  " roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" &
#sleep 5
