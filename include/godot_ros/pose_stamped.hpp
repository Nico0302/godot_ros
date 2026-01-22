#ifndef GODOT_ROS__POSE_STAMPED_HPP
#define GODOT_ROS__POSE_STAMPED_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include "godot_ros/header.hpp"
#include "godot_ros/ros_pose.hpp"

namespace godot {

class RosPoseStamped : public Resource {
    GDCLASS(RosPoseStamped, Resource)

private:
    Ref<RosHeader> header;
    Ref<RosPose> pose;

protected:
    static void _bind_methods();

public:
    RosPoseStamped();
    ~RosPoseStamped();

    void set_header(const Ref<RosHeader> &p_header);
    Ref<RosHeader> get_header() const;

    void set_pose(const Ref<RosPose> &p_pose);
    Ref<RosPose> get_pose() const;
};

} // namespace godot

#endif // GODOT_ROS__POSE_STAMPED_HPP
