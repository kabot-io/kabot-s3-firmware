  //  Copyright 2023 Krzysztof Pochwała

  //  Licensed under the Apache License, Version 2.0 (the "License");
  //  you may not use this file except in compliance with the License.
  //  You may obtain a copy of the License at

  //     http://www.apache.org/licenses/LICENSE-2.0

  //  Unless required by applicable law or agreed to in writing, software
  //  distributed under the License is distributed on an "AS IS" BASIS,
  //  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  //  See the License for the specific language governing permissions and
  //  limitations under the License.

#include <Arduino.h>
#include <ESP32_Servo.h>
#include <WiFi.h>
#include <EasyLed.h>
#include <ESPTelnet.h>
#include <ezLED.h>
#include <Preferences.h>

#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>

#include "secrets.h"

rcl_publisher_t publisher;
rcl_subscription_t subscriber;
geometry_msgs__msg__Twist msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error handle loop
void error_loop() {
	while(1) {
		delay(100);
	}
}

void subscription_callback(const void * msgin)
{
	const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
	RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL)); //debug callback
}

void setup()
{
  #if defined(MICRO_ROS_TRANSPORT_ARDUINO_WIFI)
  IPAddress agent_ip(192, 168, 1, 12);
  size_t agent_port = 8888;
  set_microros_wifi_transports(SSID, PASS, agent_ip, agent_port);
  #endif

  #if defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
  Serial.begin(115200);
  Serial.print("Init uros");
  set_microros_serial_transports(Serial);
  #endif

	allocator = rcl_get_default_allocator();
	RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
	RCCHECK(rclc_node_init_default(&node, "kabot", "", &support));

	RCCHECK(rclc_publisher_init_default(
		&publisher,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
		"/cmd_vel_callback"));

	RCCHECK(rclc_subscription_init_default(
		&subscriber,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
		"/cmd_vel"));

  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));
}

void loop() {
  delay(100);
	RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}