from launch import LaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory
import os
import xacro

def generate_launch_description():
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(get_package_share_directory('gazebo_ros'), 'launch' , 'gazebo.launch.py')]),
    )

    spawn_kabot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic', 'robot_description',
                   '-entity', 'kabot1'],
        output='screen'
    )

    camera_xacro_file_path = os.path.join(get_package_share_directory('kabot_launcher'), 'description', 'urdf', 'gazebo_camera.urdf.xacro')
    camera_description_config = xacro.process_file(camera_xacro_file_path)
    camera_state_publisher = Node(
        namespace="main_camera",
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': camera_description_config.toxml(),
                     'use_sim_time': True}]
    )

    spawn_camera = Node(
        namespace="main_camera",
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic', 'robot_description',
                   '-entity', 'camera1'],
        output='screen'
    )

    return LaunchDescription([
        gazebo,
        spawn_kabot,
        camera_state_publisher,
        spawn_camera
    ])