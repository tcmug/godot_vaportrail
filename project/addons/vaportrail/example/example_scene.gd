extends Node3D

@onready var proto_smoke = preload("res://addons/vaportrail/example/smoky_thing.tscn")

func _on_timer_timeout() -> void:
	var smoke = proto_smoke.instantiate()
	add_child(smoke)

var t = 0.0;
func _process(delta) -> void:
	# Emitter size manipulation
	t += delta
	%Vapor.size = clamp(((sin(t) + 0.7) / 2.0) * 0.2, 0.0, 1.0) 
	
