#!/bin/sh

export TURTLEBOT3_MODEL='waffle_pi'

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_world.launch " &
sleep 10

xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch " &
sleep 10

xterm  -e  " rosrun add_markers add_markers_node " &
sleep 5

xterm  -e  " rosrun pick_objects pick_objects_node " &
sleep 5