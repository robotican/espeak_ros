/*
 * espeak_ros_node.cpp
 *
 * Originally copied from https://github.com/Teknoman117/linbot
 *
 * Modified by Murilo FM (muhrix@gmail.com)
 * 12 Dec 2013
 *
 */

#include <speak_lib.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

void string_received_callback(const std_msgs::String::ConstPtr& line) {
    /* Speak the string */
    espeak_Synth(line->data.c_str(), line->data.length()+1, 0, POS_CHARACTER, 0, 
        espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE, NULL, NULL);
    espeak_Synchronize();
    ROS_INFO("Speaking: \"%s\"", line->data.c_str());
}

int main( int argc, char** argv ) {
    ros::init(argc, argv, "espeak_node");
    ros::NodeHandle n;
    std::string voice;
    n.getParam(std::string("/espeak_node/voice"), voice);
    espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
    espeak_SetVoiceByName(voice.c_str());
    ros::Subscriber sub = n.subscribe("/espeak_node/speak_line", 1000, string_received_callback);
    ros::spin();
    return 0;
}
