# Fast & jerky moving smoke emitting spark.
extends VaporTrail

var velocity: Vector3
var ttl: float = 1.0

func _enter_tree() -> void:
	# To keep the mesh in the tree even if this node is deleted
	# we need to set the geometry root node for the created mesh.
	# This prevents sudden disappearance of the mesh and allows 
	# the trail to finish the animation before removal.
	set_geometry_root(get_parent().get_path())
	var random = Vector3(
		randf_range(-1, 1),
		randf_range(-1, 1),
		randf_range(-1, 1)
	) * 0.2
	velocity = (Vector3.UP + random)

func _process(delta: float) -> void:
	var random = Vector3(
		randf_range(-1, 1),
		randf_range(-1, 1),
		randf_range(-1, 1)
	).normalized()
	position += (velocity + (random * 5)) * delta
	ttl -= delta
	if ttl < 0:
		queue_free()
