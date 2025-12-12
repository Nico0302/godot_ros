/// @brief The RosNode implementations for Godot Joy -> sensor_msgs::msg::Joy
#ifndef GODOT_ROS__JOY_TPP
#define GODOT_ROS__JOY_TPP
#include "godot_ros/node.hpp"
#include "godot_ros/joy.hpp"
#include "godot_ros/header.hpp"

#include "sensor_msgs/msg/joy.hpp"

#include <iostream>

namespace godot
{

using GodotJoyType = Ref<RosJoy>;
using RosJoyType = sensor_msgs::msg::Joy;

template <>
inline void RosNode::create_publisher<GodotJoyType>(
    const String & topic_name,
    const int & qos)
{
    assert_rclcpp_node_initialized();

    // Cast the Godot type to a C++ type
    std::string topic_name_as_string = topic_name.utf8().get_data();
    // Create the publisher
    auto new_pub = m_node->create_publisher<RosJoyType>(
        topic_name_as_string,
        qos
    );
    // Add the new publisher to the map, using the topic name as the key
    m_publishers.emplace(topic_name, std::move(new_pub));
}

template<>
inline void RosNode::publish<GodotJoyType>(
    const String & topic_name,
    const GodotJoyType & data)
{
    if (m_publishers.find(topic_name) != m_publishers.end()) {
        // get the publisher for this topic
        auto publisher_variant = m_publishers[topic_name];
        auto publisher = std::get<rclcpp::Publisher<RosJoyType>::SharedPtr>(publisher_variant);
        // borrow a loaned message from the publisher
        auto loaned_msg = publisher->borrow_loaned_message();
        // fill in message with data from Godot
        auto & msg = loaned_msg.get();
        
        // Header
        Ref<RosHeader> godot_header = data->get_header();
        if (godot_header.is_valid()) {
            msg.header.frame_id = godot_header->get_frame_id().utf8().get_data();
            msg.header.stamp.sec = godot_header->get_seconds();
            msg.header.stamp.nanosec = godot_header->get_nanoseconds();
        }

        // Axes
        PackedFloat32Array godot_axes = data->get_axes();
        msg.axes.resize(godot_axes.size());
        for (int i = 0; i < godot_axes.size(); ++i) {
            msg.axes[i] = godot_axes[i];
        }

        // Buttons
        PackedInt32Array godot_buttons = data->get_buttons();
        msg.buttons.resize(godot_buttons.size());
        for (int i = 0; i < godot_buttons.size(); ++i) {
            msg.buttons[i] = godot_buttons[i];
        }

        // publish data
        publisher->publish(std::move(loaned_msg));
    }
}

}  // namespace godot

#endif  // GODOT_ROS__JOY_TPP
