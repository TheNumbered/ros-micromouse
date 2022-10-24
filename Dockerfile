ARG ROS_DISTRO=humble
FROM osrf/ros:$ROS_DISTRO-desktop
SHELL ["/bin/bash", "-c"]

RUN apt-get update && \
        apt install -y \
        ros-$ROS_DISTRO-xacro \
        ros-$ROS_DISTRO-joint-state-publisher \
        ros-$ROS_DISTRO-gazebo-ros-pkgs \
        ros-$ROS_DISTRO-rqt-robot-steering \
        ros-$ROS_DISTRO-rmw-fastrtps-cpp && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

ENV RMW_IMPLEMENTATION=rmw_fastrtps_cpp
COPY ./micromouse_bringup /app/src/micromouse_bringup
COPY ./micromouse_description /app/src/micromouse_description
COPY ./micromouse_robot /app/src/micromouse_robot
COPY ./ros_entrypoint.sh /

WORKDIR /app
RUN source /opt/ros/$ROS_DISTRO/setup.bash && colcon build
RUN echo "source /opt/ros/$ROS_DISTRO/setup.bash" >> ~/.bashrc
RUN echo "source /app/install/setup.bash" >> ~/.bashrc
ENTRYPOINT ["/ros_entrypoint.sh"]