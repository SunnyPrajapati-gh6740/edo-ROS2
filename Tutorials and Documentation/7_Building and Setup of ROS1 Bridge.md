# Building and Setup of ROS1 Bridge

We will be working inside of the ROS/ROS2 workspaces already made in the edo-ROS2 repository


**These folders can be found in the edo-ROS2 repository cloned from the GitHub
Once you have your directory setup, you can proceed with the build.

## Build ROS1 Packages
1. Open up a new terminal inside your ROS1 Workspace and source your ROS1 distro
    `. /opt/ros/melodic/setup.bash`

2. Check for any dependencies by running the following command
    `rosdep install --from-paths ~/<path to your ros1 workspace> --ignore-src`

3. Build the ROS1 packages using the following command
    `catkin_make_isolated --install`
    
*Note: This will create three new folders in your workspace: build_isolated, devel_isolated, and install_isolated*

*Note: Need to remove any build, install, log files prior to running catkin*

4. If both packages successfully build, you and move onto the next step
5. Source the newly create "devel_isolated" folder in the ROS1 directory
    `. devel_isolated/setup.bash`
6. Open up a a roscore in the background
	$ roscore

## Build ROS2 Packages

1. Open up a new terminal in the ROS2 workspace
2. Source your ROS2 distro
 `. /opt/ros/eloquent/setup.bash`

** A warning may pop up regarding the ROS Distro was set to melodic. This will not affect functionality
3. Build edo_core_msgs on ROS2
 `colcon build --packages-select edo_core_msgs`

*Note: This will create a build, install, and log folder in the directory*

*Note: Need to remove any build, install, log files prior to running colcon 

4. After a successful build, source the newly create local_setup file in the insatll folder
` . install/local_setup.bash`


##Adding Specific Repos
1. Navigate to the edo-ROS2 repository you cloned 
2. Open a new Terminal inside the repository
3. Create a new directory called repos
	mkdir repos
4. Navigate into repos
	cd repos
5. clone the repositories launch and launch_ros
	git clone https://github.com/ros2/launch_ros
	git clone https://github.com/ros2/launch
  Run a Build in this folder
	colcon build

## Building the Bridge

1. Open up a third terminal
2. Navigate to your bridge workspace 
3. Create a 'src' folder inside the bridge workspace
4. Navigate back up to the bridge workspace
5. Source ROS1 and ROS2
    `. /opt/ros/melodic/setup.bash`
    `. /opt/ros/eloquent/setup.bash`
6. Source the messages packages that weere compiled above for both ROS1 and ROS2
Example from my directory, but this will be wherever you build your messages package:
  `. ../ROS/install_isolated/setup.bash`
  `. ../ROS2/install/local_setup.bash`

   Source the repos folder
  `. ../repos/install/setup.bash`

7. Check for any dependencies by running the following command
    `rosdep install --from-paths . --ignore-src`

    *Note: If you get an error saying rosdep keys cannot be resolved, use the following command:*
    `rosdep install --from-paths src --ignore-src --skip-keys python-wxtools --rosdistro eloquent -y`

8. Compile the ros1_bridge
    `colcon build --packages-select ros1_bridge --cmake-force-configure`

    *Note: You may get a warning after the build that "1 of hte mappings can not be generatred due to missing dependencies- edo_core_msgs/JointFwVersionArray <-> edo_core_msgs/JointFwVersionArray: - edo_core_msgs/JointFwVersion".  Currently, the wrapper class does not use this message, so there is no need to map it to ROS2*

9. Source the newly created local_setup file in the install folder
    `. install/local_setup.bash`

10. Test the mapping by printing out the paired messages
    ` ros2 run ros1_bridge dynamic_bridge --print-pairs`

    *Note: This should list out all the edo_core_msg mappings including the custom mapping rules.  Please check to make sure all mappings are included before proceeding*
    
