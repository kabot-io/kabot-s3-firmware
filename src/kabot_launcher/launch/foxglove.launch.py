from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource

from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    rosbridge_server = IncludeLaunchDescription(
        XMLLaunchDescriptionSource(
            [os.path.join(get_package_share_directory('rosbridge_server'), 'launch', 'rosbridge_websocket_launch.xml')])
    )

    foxglove_web_client = ExecuteProcess(
        cmd=['xdg-open https://studio.foxglove.dev/?ds=rosbridge-websocket&ds.url=ws://localhost:9090'],
        shell=True
    )

    return LaunchDescription([
        rosbridge_server,
        foxglove_web_client
    ])