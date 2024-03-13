from launch import LaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory

import os

def generate_launch_description():
    kabot_launcher_dir = get_package_share_directory('kabot_launcher')

    kabot_app = Node(
        package='kabot_app',
        executable='kabot_app',
    )

    rviz2 = Node(   
        package='rviz2',
        executable='rviz2',
        arguments=['-d', [os.path.join(kabot_launcher_dir, 'config', 'rviz.rviz')]],
    )

    return LaunchDescription([
        # kabot_app,
        rviz2
    ])