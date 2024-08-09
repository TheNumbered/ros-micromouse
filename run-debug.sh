#!/bin/bash

source "/opt/ros/humble/setup.bash"
colcon build --symlink-install
source "install/setup.bash"

ros2 run micromouse_debugger debug_node
