class_name RosPublisher
extends RosNode

@export var node_name: String = "godot_bridge"

@export var joy_topic: String = "/joy"

@export var frame_id: String = "virtual_world"

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	self.init_rclcpp_node(node_name)
	self.create_joy_publisher(joy_topic, 10)
	self.create_pose_stamped_publisher("left_hand", 10)
	self.create_pose_stamped_publisher("right_hand", 10)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass

func publish_pose(position: Vector3, orientation: Quaternion, topic: String) -> void:
	var pose_stamped = RosPoseStamped.new()
	var pose = RosPose.new()
	pose.position = position
	pose.orientation = orientation
	pose_stamped.pose = pose
	pose_stamped.header = RosHeader.new()
	pose_stamped.header.frame_id = frame_id
	self.publish_pose_stamped(topic, pose_stamped)
	
func publish_joy_data(buttons: PackedInt32Array, axes: PackedFloat32Array, frame_id: String) -> void:
	var joy_msg = RosJoy.new()
	joy_msg.header = RosHeader.new()
	joy_msg.buttons = buttons
	joy_msg.axes = axes
	joy_msg.header.frame_id = frame_id
	self.publish_joy(self.joy_topic, joy_msg)
