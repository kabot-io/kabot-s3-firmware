# Kabbot - lowering entry barrier for ROS2

### Mission
The Kabot robot is a hardware and software solution that lowers the entry barrier to Robot Operating System 2 (ROS2) and provides an expandable platform for makers, students and educators. One of the main obstacles in the adoption of ROS2 by beginners is the high knowledge barrier needed to setup and start tinkering - Kabot mission is to bring batteries included in a box. Think of using Arduino instead of setting up whole toolchain and build system.

### Concept
The robot is a simple differential drive robot with expansion port for connecting external sensors and actuators, and instead of classic internal odometry sensors uses external camera to track itself in the world. Main goals are to create as simple (thus cost effective) hardware, move as much of heavy lifting as possible to the host PC instead of the robot itself and provide user with simple software environment.

Price point at target is less than 50$. Given current availability and prices of ARM SBCs that can run ROS (e.g. Raspberry Pi) embedding one in a robot was not viable option. What if the robot itself was dumb effector, and its brain was running on a PC, that everybody has? This way, the electronics and firmware would just subscribe to and publish data to the way beefier computer, and on this computer we'd have virtual agent that looks like a real robot for the end user. Mandatory thing on a robot that can localize itself in the world is odometry. Unforntunately, encoders with proper resolution for the task can cost a significant amount of money, thus an idea of external localization was born - e.g. external camera that looks at the robot (a webcam or a smartphone with RTSP stream app).
