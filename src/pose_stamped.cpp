#include "godot_ros/pose_stamped.hpp"

namespace godot {

void RosPoseStamped::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_header", "p_header"), &RosPoseStamped::set_header);
    ClassDB::bind_method(D_METHOD("get_header"), &RosPoseStamped::get_header);

    ClassDB::bind_method(D_METHOD("set_pose", "p_pose"), &RosPoseStamped::set_pose);
    ClassDB::bind_method(D_METHOD("get_pose"), &RosPoseStamped::get_pose);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "header", PROPERTY_HINT_RESOURCE_TYPE, "RosHeader"), "set_header", "get_header");
    ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM3D, "pose"), "set_pose", "get_pose");
}

RosPoseStamped::RosPoseStamped() {
}

RosPoseStamped::~RosPoseStamped() {
}

void RosPoseStamped::set_header(const Ref<RosHeader> &p_header) {
    header = p_header;
}

Ref<RosHeader> RosPoseStamped::get_header() const {
    return header;
}

void RosPoseStamped::set_pose(const Transform3D &p_pose) {
    pose = p_pose;
}

Transform3D RosPoseStamped::get_pose() const {
    return pose;
}

} // namespace godot
