/// @brief The RosNode implementations for Godot TransformStamped -> geometry_msgs::msg::TransformStamped (via tf2)
#ifndef GODOT_ROS__TRANSFORM_STAMPED_TPP
#define GODOT_ROS__TRANSFORM_STAMPED_TPP

#include "godot_ros/node.hpp"
#include "godot_ros/transform_stamped.hpp"
#include "godot_ros/header.hpp"

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include <tf2/LinearMath/Quaternion.h>

#include <iostream>

namespace godot
{

using GodotTransformStampedType = Ref<RosTransformStamped>;

// Specialization for creating the broadcaster (we don't create a regular publisher, checking validity is enough or just no-op)
// But to keep consistency with the API, we might need a specialization that does nothing or initializes something if needed.
// However, the TransformBroadcaster is one per node, so we probably just ensure it exists.
template <>
inline void RosNode::create_publisher<GodotTransformStampedType>(
    const String & topic_name,
    const int & qos)
{
    assert_rclcpp_node_initialized();
    // No specific publisher created here since we use the shared TransformBroadcaster.
    // We could error if topic_name is not "/tf" but tf2_ros handles that internally usually.
    // Actually, create_publisher might be misleading for TF, but we'll allow it as a "setup" step if needed,
    // or just ignore it.
}

template<>
inline void RosNode::publish<GodotTransformStampedType>(
    const String & topic_name,
    const GodotTransformStampedType & data)
{
    if (!m_tf_broadcaster) {
        std::cerr << "TF Broadcaster not initialized!" << std::endl;
        return;
    }

    geometry_msgs::msg::TransformStamped msg;

    // Header
    Ref<RosHeader> godot_header = data->get_header();
    if (godot_header.is_valid()) {
        msg.header.frame_id = godot_header->get_frame_id().utf8().get_data();
        msg.header.stamp.sec = godot_header->get_seconds();
        msg.header.stamp.nanosec = godot_header->get_nanoseconds();
    }

    // Child Frame ID
    msg.child_frame_id = data->get_child_frame_id().utf8().get_data();

    // Transform
    Transform3D godot_transform = data->get_transform();
    
    // Translation
    msg.transform.translation.x = godot_transform.origin.x;
    msg.transform.translation.y = godot_transform.origin.y;
    msg.transform.translation.z = godot_transform.origin.z;

    // Rotation (Basis -> Quaternion)
    Quaternion godot_quat = godot_transform.basis.get_rotation_quaternion();
    msg.transform.rotation.x = godot_quat.x;
    msg.transform.rotation.y = godot_quat.y;
    msg.transform.rotation.z = godot_quat.z;
    msg.transform.rotation.w = godot_quat.w;

    // Broadcast
    m_tf_broadcaster->sendTransform(msg);
}

}  // namespace godot

#endif  // GODOT_ROS__TRANSFORM_STAMPED_TPP
