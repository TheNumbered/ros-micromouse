import launch
from launch.substitutions import Command, LaunchConfiguration
import launch_ros
import os


def generate_launch_description():
    pkg_share = launch_ros.substitutions.FindPackageShare(
        package='micromouse_description').find('micromouse_description')

    default_model_path = os.path.join(
        pkg_share, 'urdf/micromouse_description.xacro')

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
        arguments=['-entity', 'micromouse', '-topic', 'micromouse/robot_description'],
        output='screen'
    )

    return launch.LaunchDescription([
        launch.actions.DeclareLaunchArgument(name='model', default_value=default_model_path,
                                             description='Absolute path to robot urdf file'),
        launch.actions.ExecuteProcess(
            cmd=['gazebo', '--verbose', '-s', 'libgazebo_ros_init.so', '-s', 'libgazebo_ros_factory.so'], output='screen'),
        joint_state_publisher_node,
        robot_state_publisher_node,
        spawn_entity
    ])
