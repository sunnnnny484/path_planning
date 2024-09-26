#Home Service Robot

## Packages:
1. `turtlebot3_gazebo`: Deploy the turtlebot in the simulation environment
2. `turtlebot3_slam`: Generate the map of the environment
3. `turtlebot3_navigation`: Perform AMCL in the generated map and localize robot in the simulation world
4. `turtlebot3_teleop`: Control turtlebot by pressing the keyboard
5. `pick_objects`: Receive the destination coordinate and transmit to move_base
6. `add_markers`: Draw a marker in rviz window at the pre-define location

## Usage:
1. Build this workspace
2. Run `test_slam.sh`:
    `./src/scripts/test_slam.sh`
3. Save the map to `map` folder:
    `rosrun map_server map_saver -f ./src/map/map`
4. Run the Home Service Robot demo:
    `./src/scripts/home_service.sh`
