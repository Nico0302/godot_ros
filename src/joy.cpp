#include "godot_ros/joy.hpp"
#include <godot_cpp/core/class_db.hpp>

namespace godot {

RosJoy::RosJoy() {
    header.instantiate();
}

RosJoy::~RosJoy() {
}

void RosJoy::set_header(const Ref<RosHeader> &p_header) {
    header = p_header;
}

Ref<RosHeader> RosJoy::get_header() const {
    return header;
}

void RosJoy::set_axes(const PackedFloat32Array &p_axes) {
    axes = p_axes;
}

PackedFloat32Array RosJoy::get_axes() const {
    return axes;
}

void RosJoy::set_buttons(const PackedInt32Array &p_buttons) {
    buttons = p_buttons;
}

PackedInt32Array RosJoy::get_buttons() const {
    return buttons;
}

void RosJoy::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_header", "header"), &RosJoy::set_header);
    ClassDB::bind_method(D_METHOD("get_header"), &RosJoy::get_header);
    ClassDB::bind_method(D_METHOD("set_axes", "axes"), &RosJoy::set_axes);
    ClassDB::bind_method(D_METHOD("get_axes"), &RosJoy::get_axes);
    ClassDB::bind_method(D_METHOD("set_buttons", "buttons"), &RosJoy::set_buttons);
    ClassDB::bind_method(D_METHOD("get_buttons"), &RosJoy::get_buttons);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "header", PROPERTY_HINT_RESOURCE_TYPE, "RosHeader"), "set_header", "get_header");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "axes"), "set_axes", "get_axes");
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "buttons"), "set_buttons", "get_buttons");
}

} // namespace godot
