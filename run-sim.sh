#!/bin/bash

source "/opt/ros/humble/setup.bash"
colcon build --symlink-install
source "install/setup.bash"

ros2 launch micromouse_bringup micromouse_bringup.launch.py
