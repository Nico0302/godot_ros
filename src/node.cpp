#include <godot_cpp/classes/node.hpp>
#include "godot_ros/node.hpp"

namespace godot
{

void RosNode::_bind_methods() {
  ClassDB::bind_method(D_METHOD("init_rclcpp_node"), &RosNode::init_rclcpp_node);
  ClassDB::bind_method(D_METHOD("spin_some"), &RosNode::spin_some);

  ClassDB::bind_method(D_METHOD("create_string_publisher"), &RosNode::create_publisher<String>);
  ClassDB::bind_method(D_METHOD("publish_string"), &RosNode::publish<String>);

  ClassDB::bind_method(D_METHOD("create_image_publisher"), &RosNode::create_publisher<Ref<Image>>);
  ClassDB::bind_method(D_METHOD("publish_image"), &RosNode::publish<Ref<Image>>);

  ClassDB::bind_method(D_METHOD("create_joy_publisher"), &RosNode::create_publisher<Ref<RosJoy>>);
  ClassDB::bind_method(D_METHOD("publish_joy"), &RosNode::publish<Ref<RosJoy>>);

  ClassDB::bind_method(D_METHOD("create_transform_stamped_publisher"), &RosNode::create_publisher<Ref<RosTransformStamped>>);
  ClassDB::bind_method(D_METHOD("publish_transform_stamped"), &RosNode::publish<Ref<RosTransformStamped>>);
}

void RosNode::init_rclcpp_node(const String & node_name) {
  m_node = std::make_shared<rclcpp::Node>(node_name.utf8().get_data());
  m_tf_broadcaster = std::make_shared<tf2_ros::TransformBroadcaster>(m_node);
}

void RosNode::assert_rclcpp_node_initialized() {
	if (m_node == nullptr) {
		throw std::runtime_error("rclcpp Node not initialized yet. Did you call `self.init()` for this node?");
	}
}

void RosNode::spin_some() {
  rclcpp::spin_some(m_node);
}

}  // namespace godot
