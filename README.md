#Home Service Robot

## Packages:
1. `turtlebot3_gazebo`: Deploy the turtlebot in the simulation environment with the [custom world file](./map/myworld.world)
2. `turtlebot3_slam`: 
    - Package allows TurtleBot3 to perform Simultaneous Localization and Mapping (SLAM).
    - It helps the robot create and update a map of its environment while tracking its position.
    - The package supports popular SLAM algorithms like Gmapping, Karto, and Cartographer. And in this project we using Gmapping.
    - Gmapping in the turtlebot3_slam package is an algorithm that enables the TurtleBot3 to create 2D occupancy grid maps of its environment while simultaneously determining its location within that map. It uses laser scan data and odometry to build the map incrementally, making it useful for robots operating in indoor environments. 
3. `turtlebot3_navigation`: 
    - The turtlebot3_navigation package enables autonomous navigation for the TurtleBot3 using [pre-built](./map/map.yaml) or live maps.
    - It utilizes the Adaptive Monte Carlo Localization (AMCL) algorithm for precise localization within a known environment.
    - And AMCL package helps the TurtleBot3 estimate its precise location within a known map using probabilistic techniques. It relies on a particle filter, which represents multiple possible robot positions (particles) and updates their likelihood based on sensor data, such as laser scans and odometry. As the robot moves, AMCL evaluates the consistency between sensor readings and the map, discarding unlikely positions and refining the most probable ones. This process allows the TurtleBot3 to continuously track its position, even in the presence of noise or small inaccuracies in odometry. AMCL is essential for robust autonomous navigation, especially when path planning and obstacle avoidance are required.
    - In this navigation package, the Dynamic Window Approach (DWA) is used for path planning problem. It is a real-time motion planning method for mobile robots that generates feasible trajectories by sampling velocities based on the robot's current speed and acceleration limits. It evaluates these trajectories using a cost function that considers how well they align with the desired goal direction and how safely they avoid obstacles. By continuously updating the chosen trajectory as new sensor data comes in, DWA enables the robot to navigate dynamically changing environments effectively.
4. `turtlebot3_teleop`: 
    - Package allows manual control of the TurtleBot3 using a keyboard, joystick, or other input devices.
    - It provides simple control over the robot's movement, enabling users to directly drive it in any environment.
5. `pick_objects`: Receive the destination coordinate and transmit to move_base
    - `pick_objects_test_node`: Moving robot to a pre-defined coordinate, after reaching the destination, send back a message to console
    - `pick_objects_node`: Receive 1st goal from add_marker_node, after reaching the first goal, obtain the 2nd goal and moving to the drop off position.
6. `add_markers`: Draw a marker in rviz window at the pre-defined location
    - `add_marker_test_node`: Show a cube marker at a pre-defined location. Delete the marker for 5 sec and show it at the new position
    - `add_marker_node`: Publish marker position to `pick_objects_node`, and obtain robot's position from `odom` topic. When robot reach the 1st goal, this package transmit the 2nd goal to `pick_objects_node`



## Usage:
1. Build this workspace and source the setup file
2. Run `test_slam.sh`:
    `./src/scripts/test_slam.sh`
3. Save the map to `map` folder:
    `rosrun map_server map_saver -f ./src/map/map`
4. After creating a simulation map, you can try 3 demo:
    - Run the Home Service Robot demo:
        `./src/scripts/home_service.sh`
    - Run the add marker demo:
        `./src/scripts/add_marker.sh`
    - Run the pick_objects demo:
        `./src/scripts/pick_objects.sh`
