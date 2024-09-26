#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <cmath>

double pickGoal[2]  = {4.0, -3.0};
double dropGoal[2] = {0, 0};
double pose[2] = {0, 0};

void get_pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
  pose[0] = msg->pose.pose.position.x;
  pose[1] = msg->pose.pose.position.y;
//   ROS_INFO("current x %f", pose[0]);
//   ROS_INFO("current y %f", pose[0]);
}

bool reach_goal(double currentPose[2], double goal[2])
{
  return pow(currentPose[0] - goal[0], 2) <= 0.01 && pow(currentPose[1] - goal[1], 2) <= 0.01;
}

void init_maker(visualization_msgs::Marker &marker)
{
    uint32_t shape = visualization_msgs::Marker::CUBE;

    marker.header.frame_id = "odom";
    marker.header.stamp = ros::Time::now();

    marker.ns = "basic_shapes";
    marker.id = 0;

    marker.type = shape;

    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = 1.0;
    marker.pose.position.y = 1.0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1, true);
  uint32_t shape = visualization_msgs::Marker::CUBE;
  ros::Subscriber pose_sub = n.subscribe("odom", 10, get_pose_callback);

  enum State {
    PICKUP,  // going to pick up zon
    CARRY,   // carry to drop zone
    DROP,    // already drop
  } state = PICKUP;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;

    init_maker(marker);

    ROS_INFO("Moving to the pick up position");

    if (state == PICKUP) {
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = pickGoal[0];
      marker.pose.position.y = pickGoal[1];
      marker_pub.publish(marker);
      if (reach_goal(pose, pickGoal)) {
        ROS_INFO("Picking up the package");
        sleep(4.5);
        state = CARRY;
      }
    }
    else if (state == CARRY) {
      ROS_INFO("Moving to drop off position");
      marker.action = visualization_msgs::Marker::DELETE;
      marker.pose.position.x = dropGoal[0];
      marker.pose.position.y = dropGoal[1];
      marker_pub.publish(marker);
      if (reach_goal(pose, dropGoal)) {
        state = DROP;
      }
    }
    else {
      ROS_INFO("Reached the drop off position");
      sleep(5);
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = dropGoal[0];
      marker.pose.position.y = dropGoal[1];
      marker_pub.publish(marker);
    }
    ros::spinOnce();
    sleep(1);
  }
}