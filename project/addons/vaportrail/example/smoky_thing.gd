extends VaporTrail

var velocity: Vector3
var ttl: float = 1.0

func _enter_tree() -> void:
	set_geometry_root(get_parent().get_path())
	var random = Vector3(
		randf_range(-1, 1),
		randf_range(-1, 1),
		randf_range(-1, 1)
	) * 0.2
	velocity = (Vector3.UP + random)

func _physics_process(delta: float) -> void:
	var random = Vector3(
		randf_range(-1, 1),
		randf_range(-1, 1),
		randf_range(-1, 1)
	).normalized()
	velocity += random * 6 * delta
	position += velocity * delta
	
	ttl -= delta
	if ttl < 0:
		queue_free()
