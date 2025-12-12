extends XRController3D

@export var ros_node: RosPublisher

@export var frame_id: String

var elapsed_time = 0
var zup = Transform3D(Vector3(1, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0), Vector3(0, 0, 0))

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	elapsed_time += delta
	
	if elapsed_time >= 0.01:
		ros_node.publish_transform(zup * self.transform, frame_id)
