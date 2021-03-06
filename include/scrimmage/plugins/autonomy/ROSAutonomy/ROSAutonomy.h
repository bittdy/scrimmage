/*!
 * @file
 *
 * @section LICENSE
 *
 * Copyright (C) 2017 by the Georgia Tech Research Institute (GTRI)
 *
 * This file is part of SCRIMMAGE.
 *
 *   SCRIMMAGE is free software: you can redistribute it and/or modify it under
 *   the terms of the GNU Lesser General Public License as published by the
 *   Free Software Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   SCRIMMAGE is distributed in the hope that it will be useful, but WITHOUT
 *   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 *   License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with SCRIMMAGE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Kevin DeMarco <kevin.demarco@gtri.gatech.edu>
 * @author Eric Squires <eric.squires@gtri.gatech.edu>
 * @date 31 July 2017
 * @version 0.1.0
 * @brief Brief file description.
 * @section DESCRIPTION
 * A Long description goes here.
 *
 */

#ifndef INCLUDE_SCRIMMAGE_PLUGINS_AUTONOMY_ROSAUTONOMY_ROSAUTONOMY_H_
#define INCLUDE_SCRIMMAGE_PLUGINS_AUTONOMY_ROSAUTONOMY_ROSAUTONOMY_H_

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_broadcaster.h>

#include <scrimmage/autonomy/Autonomy.h>
#include <scrimmage/pubsub/Subscriber.h>

#include <map>
#include <string>

class ROSAutonomy : public scrimmage::Autonomy {
 public:
    ROSAutonomy();
    virtual void init(std::map<std::string, std::string> &params);
    virtual bool step_autonomy(double t, double dt);
    void cmd_vel_cb(const geometry_msgs::Twist::ConstPtr& msg);

 protected:
    std::shared_ptr<ros::NodeHandle> nh_;

    ros::Subscriber cmd_vel_sub_;
    geometry_msgs::Twist cmd_vel_;

    ros::Publisher odom_pub_;
    ros::Publisher odom_laser_pub_;
    ros::Publisher base_scan_pub_;
    ros::Publisher base_pose_truth_pub;

    ros::Publisher clock_pub_;

    std::shared_ptr<tf::TransformBroadcaster> odom_broadcaster_;
    geometry_msgs::TransformStamped odom_trans_;

    std::shared_ptr<tf::TransformBroadcaster> laser_broadcaster_;
    geometry_msgs::TransformStamped laser_trans_;

    std::string ros_namespace_;

    scrimmage::SubscriberPtr pcl_sub_;

    void publish_clock_msg(double t);
};

#endif // INCLUDE_SCRIMMAGE_PLUGINS_AUTONOMY_ROSAUTONOMY_ROSAUTONOMY_H_
