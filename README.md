# FIRST Camera Control

This repository contains code used by the [Georgia FIRST Robotics Competition](http://gafirst.org/) for remote-controlling [PTZ Optics 12X-SDI](http://ptzoptics.com/12x-sdi/) cameras using [Logitech Extreme 3D Pro](http://gaming.logitech.com/en-us/product/extreme-3d-pro-joystick) joysticks.
 
 ## Setup
 
 #### Dependencies
 
 This application depends on these widely-available packages: 
 
 * [Cmake](https://cmake.org/)
 * [Boost](http://www.boost.org/)
 * [SDL 2.0](https://www.libsdl.org/)
 * [YAML-CPP](https://github.com/jbeder/yaml-cpp)
 
 In Linux, these can be installed with the following command:
 
 ```
 sudo apt-get install cmake libsdl2-dev libboost-all-dev libyaml-cpp-dev
 ```
 
 #### Installation
 
 Clone this repository and run these commands from the FIRST-CameraControl folder:
 
 ```
 mkdir cmake-build-debug
 cd cmake-build-debug
 cmake ..
 make
 ```
 
 This will generate the _FIRST_CameraControl_ binary executable in the _cmake-build-debug_ folder.
 
 ## Usage
 
 #### Setup
 
 Ensure that config.yaml (in the _cmake-build-debug_ folder) contains correct information for your cameras. Follow the example already there to generate entries for each of your cameras.
 
 #### Run
 
 From a terminal, run `./FIRST_CameraControl`. It will tell you how many camera entries it found in the config file and how many joysticks it detects are connected to the computer. Messages will be displayed as the application connects to each camera. Once all are connected, you should be able to control the cameras from your joysticks.
 
 #### Controls
 
 Basic pan-tilt functionality is mapped to the joystick's x and y axes. The speed of these motions is controlled by the paddle at the base of the joystick.
 
 The camera can be zoomed in and out using the direction hat on top of the joystick. Push forward to zoom in, pull back to zoom out.
 
 If the camera begins moving unexpectedly, pull the trigger button to send a stop command to the camera.
 
 The camera has the capacity to store 9, user-defined, preset positions. These positions can be recalled using the labeled buttons (3,5-12) on the top and base of the joystick.
  
 The thumb button on the side of the joystick will reset the connection to the camera. This should happen nearly immeidately.
 
 #### Troubleshooting
 
 There are a variety of network issues which can cause connection errors between this software and the cameras. In the event of one of these issues, this software will disable the individual camera to prevent the interruption of control for other cameras. If this happens, push the reset button or restart the software once the issue has been resolved. 
 
 
