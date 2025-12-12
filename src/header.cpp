#include "godot_ros/header.hpp"
#include <godot_cpp/core/class_db.hpp>

namespace godot {

RosHeader::RosHeader() {
    frame_id = "";
    seconds = 0;
    nanoseconds = 0;
}

RosHeader::~RosHeader() {
}

void RosHeader::set_frame_id(const String &p_frame_id) {
    frame_id = p_frame_id;
}

String RosHeader::get_frame_id() const {
    return frame_id;
}

void RosHeader::set_seconds(int32_t p_seconds) {
    seconds = p_seconds;
}

int32_t RosHeader::get_seconds() const {
    return seconds;
}

void RosHeader::set_nanoseconds(uint32_t p_nanoseconds) {
    nanoseconds = p_nanoseconds;
}

uint32_t RosHeader::get_nanoseconds() const {
    return nanoseconds;
}

void RosHeader::set_ros_header(std_msgs::msg::Header &p_header, const rclcpp::Node &p_node) const {
    p_header.frame_id = frame_id.utf8().get_data();
    if (seconds != 0 && nanoseconds != 0) {
        p_header.stamp.sec = seconds;
        p_header.stamp.nanosec = nanoseconds;
    } else {
        p_header.stamp = p_node.get_clock()->now();
    }
}

void RosHeader::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_frame_id", "frame_id"), &RosHeader::set_frame_id);
    ClassDB::bind_method(D_METHOD("get_frame_id"), &RosHeader::get_frame_id);
    ClassDB::bind_method(D_METHOD("set_seconds", "seconds"), &RosHeader::set_seconds);
    ClassDB::bind_method(D_METHOD("get_seconds"), &RosHeader::get_seconds);
    ClassDB::bind_method(D_METHOD("set_nanoseconds", "nanoseconds"), &RosHeader::set_nanoseconds);
    ClassDB::bind_method(D_METHOD("get_nanoseconds"), &RosHeader::get_nanoseconds);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "frame_id"), "set_frame_id", "get_frame_id");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "seconds"), "set_seconds", "get_seconds");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "nanoseconds"), "set_nanoseconds", "get_nanoseconds");
}

} // namespace godot
