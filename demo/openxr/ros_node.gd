class_name RosPublisher
extends RosNode

@export var node_name: String = "godot_bridge"

@export var joy_topic: String = "/joy"
@export var tf_topic: String = "/tf"

@export var frame_id: String = "virtual_world"

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	self.init_rclcpp_node(node_name)
	self.create_joy_publisher(joy_topic, 10)
	self.create_transform_stamped_publisher(tf_topic, 10)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass

func publish_transform(transform: Transform3D, child_frame_id: String) -> void:
	var transform_stamped = RosTransformStamped.new()
	transform_stamped.transform = transform
	transform_stamped.header = RosHeader.new()
	transform_stamped.header.frame_id = frame_id
	transform_stamped.child_frame_id = child_frame_id
	self.publish_transform_stamped(tf_topic, transform_stamped)
	
func publish_joy_data(buttons: PackedInt64Array, axis: PackedFloat64Array, frame_id: String) -> void:
	var joy_msg = RosJoy.new()
	joy_msg.header = RosHeader.new()
	joy_msg.buttons = buttons
	joy_msg.axis = axis
	joy_msg.header.frame_id = frame_id
