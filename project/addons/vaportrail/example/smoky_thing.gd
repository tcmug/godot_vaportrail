extends CharacterBody3D

func _enter_tree() -> void:
	$VaporTrail.set_geometry_root(get_parent().get_path())
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
	velocity += random * 4 * delta
	move_and_slide()
	$VaporTrail.size = 0.3 * ($Timer.time_left / $Timer.wait_time)
	
func _on_timer_timeout() -> void:
	queue_free()
