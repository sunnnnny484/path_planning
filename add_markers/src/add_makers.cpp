#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

double pickGoal[2]  = {4.0, -3.0};
double dropGoal[2] = {-5.0, 0};

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

  // Set the shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;

  init_maker(marker);

  ROS_INFO("Marker is located at the pickup zone");
  marker.pose.position.x = pickGoal[0];
  marker.pose.position.y = pickGoal[1];
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);
  sleep(5);
  
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
  ROS_INFO("Marker is being moved");
  sleep(5);

  // Set new pose of the marker.
  marker.pose.position.x = dropGoal[0];
  marker.pose.position.y = dropGoal[1];
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);
  ROS_INFO("Marker is dropped at the drop off zone");
  sleep(5);
}