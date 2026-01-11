extends Node3D

@onready var proto_smoke = preload("res://addons/vaportrail/example/smoky_thing.tscn")

func _on_timer_timeout() -> void:
	var smoke = proto_smoke.instantiate()
	add_child(smoke)
	
