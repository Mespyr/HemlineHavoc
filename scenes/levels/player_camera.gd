extends Camera2D

const MAX_DISTANCE: int = 30
var target_distance: int = 0
var center_pos: Vector2 = position

func _process(_delta: float) -> void:
	var direction: Vector2 = center_pos.direction_to(get_local_mouse_position())
	var target_pos: Vector2 = center_pos + direction * target_distance
	position = target_pos.clamp(
		center_pos - Vector2(MAX_DISTANCE, MAX_DISTANCE),
		center_pos + Vector2(MAX_DISTANCE, MAX_DISTANCE))

func _input(event: InputEvent):
	if event is InputEventMouseMotion:
		target_distance = center_pos.distance_to(get_local_mouse_position())
