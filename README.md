# Inspection-robot-using-joystick-controller


# Overview:

The robot utilizes a laptop's webcam to process video through a YOLOv8 object detection model. By using a Joystick Module, the user can direct the robot's gait in real-time to navigate through warehouses, industrial plants, or hazardous zones.


# Key Features:

Real-time Object Detection: Uses Ultralytics YOLOv8 and OpenCV for high-speed processing.

Manual Precision: Controlled via a dedicated Joystick Module for real-time directional input.

Legged Mobility: Quadruped architecture designed to navigate uneven terrains.

Scalable Control: Utilizes a dedicated PWM driver to manage the complex movement of 8+ servo motors simultaneously


# Hardware Components:

Microcontroller: Arduino Uno (Motion Controller).

Servo Driver: PCA9685 PWM Servo Driver Module (manages leg joints).

Actuators: High-torque Servo Motors for hip and knee movement.

Input: Joystick Module for directional control.

Sensors: Laptop Webcam for object processing.

Power: Dual 18650 Batteries (~7.4V Total).


# Tech Stack:

Languages: Python (AI & Serial Communication), C++ (Arduino Sketches)

AI Framework: Ultralytics YOLOv8 
 
Computer Vision: OpenCV 
 
Communication: Serial Interface


# System Flow:

Capture: Video stream is captured via the Laptop Webcam. 

Process: YOLOv8 identifies objects and determines their spatial location. 

Command: Python scripts translate detection data into movement commands. 

Transmit: Commands are sent via Serial Communication to the Arduino. 

Actuate: The Servo Motors actuate the Hip and Knee joints of the quadruped legs to execute movement using joystick.


# Applications:

Industrial Inspection: Monitoring machinery and pipelines in factories. 

Security: Autonomous patrolling of warehouses and restricted zones. 

Search & Rescue: Navigating disaster areas to locate survivors. 

Hazardous Environments: Deploying in fire zones or chemical plants.
 

