from launch import LaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    kabot_launcher_dir = get_package_share_directory('kabot_launcher')

    usb_camera_node = Node(
        namespace='main_camera',
        package='usb_cam',
        executable='usb_cam_node_exe',
        name='usb_camera_node',
        parameters=[os.path.join(kabot_launcher_dir, 'config','camera_params.yaml')]
    )

    camera_tranform_publisher = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["0","0","0","0","0","0","world","camera"],
        output="screen"
    )

    aruco_detection_node = Node(
        package='ros2_aruco',
        executable='aruco_node',
        name='aruco_detection_node',
        emulate_tty=True,
        parameters=[{'image_topic':'/main_camera/image_raw'},
                    {'camera_info_topic':'/main_camera/camera_info'},
                    {'camera_frame':'camera_link'},
                    # {'marker_size':'.0260'}
                ],
    )

    return LaunchDescription([
        # usb_camera_node,
        # camera_tranform_publisher,
        aruco_detection_node
    ])