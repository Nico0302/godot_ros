/// @brief The RosNode implementations for Godot RosPoseStamped -> geometry_msgs::msg::PoseStamped
#ifndef GODOT_ROS__POSE_STAMPED_TPP
#define GODOT_ROS__POSE_STAMPED_TPP

#include "godot_ros/node.hpp"
#include "godot_ros/pose_stamped.hpp"
#include "godot_ros/header.hpp"

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "ros_pose.hpp"

#include <iostream>

namespace godot
{

using GodotPoseStampedType = Ref<RosPoseStamped>;
using RosPoseStampedType = geometry_msgs::msg::PoseStamped;

template <>
inline void RosNode::create_publisher<GodotPoseStampedType>(
    const String & topic_name,
    const int & qos)
{
    assert_rclcpp_node_initialized();

    // Cast the Godot type to a C++ type
    std::string topic_name_as_string = topic_name.utf8().get_data();
    // Create the publisher
    auto new_pub = m_node->create_publisher<RosPoseStampedType>(
        topic_name_as_string,
        qos
    );
    // Add the new publisher to the map, using the topic name as the key
    m_publishers.emplace(topic_name, std::move(new_pub));
}

template<>
inline void RosNode::publish<GodotPoseStampedType>(
    const String & topic_name,
    const GodotPoseStampedType & data)
{
    if (m_publishers.find(topic_name) != m_publishers.end()) {
        // get the publisher for this topic
        auto publisher_variant = m_publishers[topic_name];
        auto publisher = std::get<rclcpp::Publisher<RosPoseStampedType>::SharedPtr>(publisher_variant);
        // borrow a loaned message from the publisher
        auto loaned_msg = publisher->borrow_loaned_message();
        
        // fill in message with data from Godot
        auto & msg = loaned_msg.get();

        // Header
        Ref<RosHeader> godot_header = data->get_header();
        if (godot_header.is_valid()) {
            godot_header->set_ros_header(msg.header, *m_node);
        }

        // Pose
        Ref<RosPose> godot_pose = data->get_pose();

        Vector3 position = godot_pose->get_position();

        // Position
        msg.pose.position.x = position.x;
        msg.pose.position.y = position.y;
        msg.pose.position.z = position.z;

        // Orientation
        Quaternion godot_quat = godot_pose->get_orientation();
        msg.pose.orientation.x = godot_quat.x;
        msg.pose.orientation.y = godot_quat.y;
        msg.pose.orientation.z = godot_quat.z;
        msg.pose.orientation.w = godot_quat.w;

        // publish data
        publisher->publish(std::move(loaned_msg));
    }
}

}  // namespace godot

#endif  // GODOT_ROS__POSE_STAMPED_TPP
