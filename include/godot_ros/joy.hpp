#ifndef GODOT_ROS__JOY_HPP
#define GODOT_ROS__JOY_HPP

#include <godot_cpp/classes/resource.hpp>
#include "godot_ros/header.hpp"

namespace godot {

class RosJoy : public Resource {
    GDCLASS(RosJoy, Resource)

private:
    Ref<RosHeader> header;
    PackedFloat32Array axes;
    PackedInt32Array buttons;

protected:
    static void _bind_methods();

public:
    RosJoy();
    ~RosJoy();

    void set_header(const Ref<RosHeader> &p_header);
    Ref<RosHeader> get_header() const;

    void set_axes(const PackedFloat32Array &p_axes);
    PackedFloat32Array get_axes() const;

    void set_buttons(const PackedInt32Array &p_buttons);
    PackedInt32Array get_buttons() const;
};

} // namespace godot

#endif // GODOT_ROS__JOY_HPP
