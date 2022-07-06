from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node
from launch.substitutions import Command, LaunchConfiguration, PythonExpression
from launch.conditions import IfCondition, UnlessCondition
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
import launch
from launch.substitutions import Command, LaunchConfiguration
import launch_ros
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition


def generate_launch_description():
    os.environ["GAZEBO_MODEL_PATH"] = os.path.join(
        get_package_share_directory('micromouse_description'), 'worlds')

    pkg_share = launch_ros.substitutions.FindPackageShare(
        package='micromouse_description').find('micromouse_description')

    default_model_path = os.path.join(
        pkg_share, 'urdf/micromouse_description.xacro')

    world_path = os.path.join(
        pkg_share, 'worlds/world.sdf')

    robot_state_publisher_node = launch_ros.actions.Node(
        namespace='micromouse',
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': Command(
            ['xacro ', LaunchConfiguration('model')])}]
    )

    joint_state_publisher_node = launch_ros.actions.Node(
        namespace='micromouse',
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher'
    )

    spawn_entity = launch_ros.actions.Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'micromouse', '-topic',
                   'micromouse/robot_description'],
        output='screen'
    )

    return launch.LaunchDescription([
        launch.actions.DeclareLaunchArgument(name='model', default_value=default_model_path,
                                             description='Absolute path to robot urdf file'),

        launch.actions.ExecuteProcess(
            cmd=['gazebo',  world_path, '-s', 'libgazebo_ros_init.so', '-s', 'libgazebo_ros_factory.so'], output='screen'),

        joint_state_publisher_node,
        robot_state_publisher_node,
        spawn_entity,
    ])
