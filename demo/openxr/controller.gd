extends XRController3D

@export var ros_node: RosPublisher

# Update rate in Hz for the transform brodcast
@export var tf_update_rate: int = 100

# Update rate in Hz for the joy topic
@export var joy_update_rate: int = 100

var elapsed_time = 0

var last_published_q: Quaternion = Quaternion.IDENTITY

const BUTTON_ACTIONS = ["trigger_click", "trigger_touch", "grip_click", "primary_click", "primary_touch", "secondary_click", "secondary_touch", "menu_button", "select_button"]
const TRANSFORM = Transform3D(Vector3(0, -1, 0), Vector3(0, 0, 1), Vector3(-1, 0, 0), Vector3(0, 0, 0))

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	elapsed_time += delta
	
	if elapsed_time >= 1.0 / tf_update_rate:
		var current_q = self.quaternion
		
		# Check the dot product between current and previous quaternion.
		# If it's negative, the quaternion has flipped to the opposite representation.
		if last_published_q.dot(current_q) < 0:
			current_q = - current_q
			
		# Update our tracker
		last_published_q = current_q
		
		# Reconstruct the "smooth" transform for ROS
		ros_node.publish_pose(Vector3(self.position.z, self.position.x, self.position.y), Quaternion(current_q.z, current_q.x, current_q.y, current_q.w), self.tracker)
		
	if elapsed_time >= 1.0 / joy_update_rate:
		var buttons: PackedInt32Array = []
		for input_name in BUTTON_ACTIONS:
			var input = self.get_input(input_name)
			buttons.append(1 if input else 0)
		var axes: PackedFloat32Array = [self.get_float("trigger"), self.get_float("grip")]
		ros_node.publish_joy_data(buttons, axes, self.tracker)
