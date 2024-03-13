#!/bin/bash

kill_gazebo(){
  pkill -f gzserver
  pkill -f gzclient
}

launch_creator(){
  colcon build
  source install/setup.bash
  ~/Qt/Tools/QtCreator/bin/qtcreator
}

launch_kabot(){
  kill_gazebo
  colcon build --symlink-install
  source install/setup.bash
  echo ""
  echo ""
  ros2 launch kabot_launcher kabot.launch.py --show-args
  echo ""
  echo ""
  ros2 launch kabot_launcher kabot.launch.py
}

launch_kabot_foxglove(){
  kill_gazebo
  colcon build --symlink-install
  source install/setup.bash
  ros2 launch kabot_launcher kabot.launch.py foxglove_setup:='True'
}

launch_kabot_rviz(){
  kill_gazebo
  colcon build --symlink-install
  source install/setup.bash
  ros2 launch kabot_launcher kabot.launch.py rviz_setup:='True'
}

rebuild(){
  rm -rf install log build
  colcon build --symlink-install
}

show_topics(){
	while true; do clear; ros2 topic list; sleep 5; done
}

show_services(){
  while true; do clear; ros2 service list; sleep 5; done
}

init_agent(){
  cd src
  sudo apt update && rosdep update && sudo apt upgrade
  rosdep install --from-paths src --ignore-src -y
  sudo apt-get install python3-pip
  colcon build
  source install/local_setup.bash
  ros2 run micro_ros_setup create_agent_ws.sh
  source install/local_setup.bash
  ros2 run micro_ros_setup build_agent.sh
}

run_agent_serial(){
  source install/local_setup.bash
  sudo chmod 666 /dev/ttyACM0
  ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0
}

run_agent_wifi(){
  source install/local_setup.bash
  ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
}

export LC_NUMERIC=en_US.UTF-8
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:./src/kabot_launcher/description/models/
source /opt/ros/humble/setup.bash

#sudo apt install python3-venv, python3-pip
