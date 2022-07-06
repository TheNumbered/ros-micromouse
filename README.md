# ros-micromouse
Micromouse robot simulation in ROS2 with gazebo

# Building
Container is not on DockerHub yet that is why it is necessary to build on host.
``` bash
make build
```
# Running
Use docker copose to bring  micromouse robot:
``` bash
# Enable using display inside container
xhost local:+docker0

# Spawn robot
docker-compose up micromouse_bringup

# Run random controller
docker-compose up micromouse_controller
```
