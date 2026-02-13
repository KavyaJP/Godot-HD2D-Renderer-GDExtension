class_name GameInputEvent
extends Node

static func get_movement_input() -> Vector3:
	# 1. Get the 2D Input Vector
	# arg1 (Neg X): walk_w (Left)
	# arg2 (Pos X): walk_e (Right)
	# arg3 (Neg Y): walk_n (Forward / North) -> produces -1
	# arg4 (Pos Y): walk_s (Backward / South) -> produces +1
	var input_vector = Input.get_vector("walk_w", "walk_e", "walk_n", "walk_s")
	
	# 2. Map directly to 3D World Space (X and Z)
	# Y is 0 because we don't move up/down relative to input
	var direction = Vector3(input_vector.x, 0, input_vector.y).normalized()
	
	return direction

static func is_movement_input() -> bool:
	# If any movement key is pressed then we just check if the length_squared of the vector is 0, 
	# length just refers to the magnitude of the vector, 
	# since we dont need the square_root of length, it is faster to use length_squared than length to avoid square root calculation
	return Input.get_vector("walk_w", "walk_e", "walk_n", "walk_s").length_squared() > 0

static func is_jump_just_pressed() -> bool:
	# Will return true only on the frame jump is pressed
	return Input.is_action_just_pressed("jump")
