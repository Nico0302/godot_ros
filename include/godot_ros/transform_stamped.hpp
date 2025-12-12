#ifndef GODOT_ROS__TRANSFORM_STAMPED_HPP
#define GODOT_ROS__TRANSFORM_STAMPED_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include "godot_ros/header.hpp"

namespace godot {

class RosTransformStamped : public Resource {
    GDCLASS(RosTransformStamped, Resource)

private:
    Ref<RosHeader> header;
    String child_frame_id;
    Transform3D transform;

protected:
    static void _bind_methods();

public:
    RosTransformStamped();
    ~RosTransformStamped();

    void set_header(const Ref<RosHeader> &p_header);
    Ref<RosHeader> get_header() const;

    void set_child_frame_id(const String &p_child_frame_id);
    String get_child_frame_id() const;

    void set_transform(const Transform3D &p_transform);
    Transform3D get_transform() const;
};

} // namespace godot

#endif // GODOT_ROS__TRANSFORM_STAMPED_HPP
