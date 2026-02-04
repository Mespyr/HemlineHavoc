extends CharacterBody2D

const SPEED: int = 300
const ACCEL: int = 10

const MOUSE_INFLUENCE: float = 1.5

var direction: Vector2 = Vector2.ZERO

func _process(delta: float) -> void:
	direction = Input.get_vector("left", "right", "up", "down").normalized()
	animation()
	velocity = lerp(velocity, direction * SPEED, delta * ACCEL)
	move_and_slide()
	
func animation():
	var flip: bool = get_local_mouse_position().x > 0
	$PlayerSprite.flip_h = flip
	$ShadowSprite.flip_h = flip
	if direction != Vector2.ZERO:
		$PlayerSprite.play("run")
		$ShadowSprite.play("run")
	else:
		$PlayerSprite.play("idle")
		$ShadowSprite.play("idle")
