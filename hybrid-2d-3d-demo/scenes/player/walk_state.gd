extends NodeState

@export var player: Player
@export var sprite: Hybrid2D3DAnimatedSprite

func _on_process(_delta : float) -> void:
	pass

func _on_physics_process(delta : float) -> void:
	# 1. Get 3D Input (X and Z)
	var dir = GameInputEvent.get_movement_input()
	
	# 2. Update Velocity (Horizontal Only)
	if dir != Vector3.ZERO:
		# Save direction for Idle State to use later
		player.direction = dir
		
		# Move
		player.velocity.x = dir.x * player.speed
		player.velocity.z = dir.z * player.speed
		
		# Update Animation
		_update_animation(dir)
	else:
		# Should logically transition to Idle, but strictly strictly strictly speaking,
		# for physics safety, we decelerate if input is zero
		player.velocity.x = move_toward(player.velocity.x, 0, player.speed)
		player.velocity.z = move_toward(player.velocity.z, 0, player.speed)

	# 3. Apply Gravity
	if not player.is_on_floor():
		player.velocity.y -= WorldPhysics.gravity * delta
	

	player.move_and_slide()

func _update_animation(dir: Vector3) -> void:
	# Reset flip
	sprite.flip_h = false
	
	# --- 1. CARDINALS ---
	if dir.z < -0.1 and abs(dir.x) < 0.1:     # North (-Z)
		sprite.play("walk_n")
	elif dir.z > 0.1 and abs(dir.x) < 0.1:    # South (+Z)
		sprite.play("walk_s")
	elif dir.x > 0.1 and abs(dir.z) < 0.1:    # East (+X)
		sprite.play("walk_e")
	elif dir.x < -0.1 and abs(dir.z) < 0.1:   # West (-X)
		sprite.play("walk_e") 
		sprite.flip_h = true

	# --- 2. DIAGONALS ---
	elif dir.z < -0.1 and dir.x > 0.1:        # North-East
		sprite.play("walk_ne")
	elif dir.z > 0.1 and dir.x > 0.1:         # South-East
		sprite.play("walk_se")
	elif dir.z > 0.1 and dir.x < -0.1:        # South-West
		sprite.play("walk_se")
		sprite.flip_h = true
	elif dir.z < -0.1 and dir.x < -0.1:       # North-West
		sprite.play("walk_ne")
		sprite.flip_h = true
	
	# Fallback if moving but weird angle
	else:
		sprite.play("walk_s")

func _on_next_transitions() -> void:
	if GameInputEvent.is_jump_just_pressed():
		transition.emit("jump")
		return

	if not GameInputEvent.is_movement_input():
		transition.emit("idle")

func _on_enter() -> void:
	pass

func _on_exit() -> void:
	sprite.stop()
