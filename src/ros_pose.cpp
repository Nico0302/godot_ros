#include "godot_ros/ros_pose.hpp"

namespace godot {

void RosPose::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_position", "p_position"), &RosPose::set_position);
    ClassDB::bind_method(D_METHOD("get_position"), &RosPose::get_position);

    ClassDB::bind_method(D_METHOD("set_orientation", "p_orientation"), &RosPose::set_orientation);
    ClassDB::bind_method(D_METHOD("get_orientation"), &RosPose::get_orientation);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
    ADD_PROPERTY(PropertyInfo(Variant::QUATERNION, "orientation"), "set_orientation", "get_orientation");
}

RosPose::RosPose() {
}

RosPose::~RosPose() {
}

void RosPose::set_position(const Vector3 &p_position) {
    position = p_position;
}

Vector3 RosPose::get_position() const {
    return position;
}

void RosPose::set_orientation(const Quaternion &p_orientation) {
    orientation = p_orientation;
}

Quaternion RosPose::get_orientation() const {
    return orientation;
}

} // namespace godot
