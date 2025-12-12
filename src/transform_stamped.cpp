#include "godot_ros/transform_stamped.hpp"

namespace godot {

void RosTransformStamped::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_header", "p_header"), &RosTransformStamped::set_header);
    ClassDB::bind_method(D_METHOD("get_header"), &RosTransformStamped::get_header);

    ClassDB::bind_method(D_METHOD("set_child_frame_id", "p_child_frame_id"), &RosTransformStamped::set_child_frame_id);
    ClassDB::bind_method(D_METHOD("get_child_frame_id"), &RosTransformStamped::get_child_frame_id);

    ClassDB::bind_method(D_METHOD("set_transform", "p_transform"), &RosTransformStamped::set_transform);
    ClassDB::bind_method(D_METHOD("get_transform"), &RosTransformStamped::get_transform);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "header", PROPERTY_HINT_RESOURCE_TYPE, "RosHeader"), "set_header", "get_header");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "child_frame_id"), "set_child_frame_id", "get_child_frame_id");
    ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM3D, "transform"), "set_transform", "get_transform");
}

RosTransformStamped::RosTransformStamped() {
}

RosTransformStamped::~RosTransformStamped() {
}

void RosTransformStamped::set_header(const Ref<RosHeader> &p_header) {
    header = p_header;
}

Ref<RosHeader> RosTransformStamped::get_header() const {
    return header;
}

void RosTransformStamped::set_child_frame_id(const String &p_child_frame_id) {
    child_frame_id = p_child_frame_id;
}

String RosTransformStamped::get_child_frame_id() const {
    return child_frame_id;
}

void RosTransformStamped::set_transform(const Transform3D &p_transform) {
    transform = p_transform;
}

Transform3D RosTransformStamped::get_transform() const {
    return transform;
}

} // namespace godot
