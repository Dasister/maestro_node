/* 
 * File:   test_node.cpp
 * Author: raffaello
 *
 * Created on 25 November 2013, 10:10
 */

#include <cstdlib>
#include <iostream>
#include <ros/ros.h>
#include "TimeoutSerial.h"
#include "ROSMaestroController.h"

using namespace std;
using namespace boost;

std::string name_node = "maestro_node";

/*
 * 
 */
int main(int argc, char** argv) {

    ros::init(argc, argv, name_node);
    if (argc != 2) {
        ROS_ERROR("need serial port name as argument");
        return -1;
    };

    //Name serial port
    std::string serial_port(argv[1]);
    
    ros::NodeHandle nh;

    TimeoutSerial serial(serial_port, 9600);
    serial.setTimeout(posix_time::seconds(1));

    ROS_INFO("Start");

    ROSMaestroController controller(name_node, nh, &serial);
    controller.loadConfiguration();

    ros::spin();

    ROS_INFO("Close");

    serial.close();

    return 0;
}

