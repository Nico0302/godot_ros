extends RosNode

var count = 0
var elapsed_time = 0

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	self.init_rclcpp_node("my_ros_node")  # Initialize the rclcpp::Node
	self.create_string_publisher("/string_topic", 10)
	self.create_joy_publisher("/joy", 10)
	self.create_transform_stamped_publisher("/tf", 10)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	elapsed_time += delta
	if elapsed_time >= 1:
		elapsed_time = 0
		print("Publish count: " + str(count))
		self.publish_string("/string_topic", str(count))
		var joy = RosJoy.new()
		var header = RosHeader.new()
		header.frame_id = "test"
		joy.header = header
		joy.axes = [0.0]
		joy.buttons = [0, 0]
		self.publish_joy("/joy", joy)
		
		var transfrom = RosTransformStamped.new()
		transfrom.header = header
		transfrom.child_frame_id = "test"
		
		self.publish_transform_stamped("/tf", transfrom)
		
		count += 1
	pass
