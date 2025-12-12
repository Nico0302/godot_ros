#ifndef GODOT_ROS__HEADER_HPP
#define GODOT_ROS__HEADER_HPP

#include <godot_cpp/classes/resource.hpp>

namespace godot {

class RosHeader : public Resource {
    GDCLASS(RosHeader, Resource)

private:
    String frame_id;
    int32_t seconds;
    uint32_t nanoseconds;

protected:
    static void _bind_methods();

public:
    RosHeader();
    ~RosHeader();

    void set_frame_id(const String &p_frame_id);
    String get_frame_id() const;

    void set_seconds(int32_t p_seconds);
    int32_t get_seconds() const;

    void set_nanoseconds(uint32_t p_nanoseconds);
    uint32_t get_nanoseconds() const;
};

} // namespace godot

#endif // GODOT_ROS__HEADER_HPP
