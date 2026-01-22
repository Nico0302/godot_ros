#ifndef GODOT_ROS__ROS_POSE_HPP
#define GODOT_ROS__ROS_POSE_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class RosPose : public Resource {
    GDCLASS(RosPose, Resource)

private:
    Vector3 position;
    Quaternion orientation;

protected:
    static void _bind_methods();

public:
    RosPose();
    ~RosPose();

    void set_position(const Vector3 &p_position);
    Vector3 get_position() const;

    void set_orientation(const Quaternion &p_orientation);
    Quaternion get_orientation() const;
};

} // namespace godot

#endif // GODOT_ROS__ROS_POSE_HPP
