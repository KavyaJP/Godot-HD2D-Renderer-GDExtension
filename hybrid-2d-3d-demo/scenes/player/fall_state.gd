extends NodeState

@export var player: Player
@export var sprite: Hybrid2D3DAnimatedSprite

var is_landing : bool = false
var landing_timer : float = 0.0

func _on_enter() -> void:
	is_landing = false
	landing_timer = 0.0
	
	# Force "Fall" animation frame immediately
	_update_fall_animation(player.direction)
	sprite.pause() 
	sprite.frame = 3 # Falling Frame

func _on_physics_process(delta: float) -> void:
	# --- PHASE 1: LANDING SEQUENCE ---
	if is_landing:
		player.velocity.x = 0
		player.velocity.z = 0
		sprite.frame = 4 # Landing Frame
		
		landing_timer -= delta
		if landing_timer <= 0:
			if GameInputEvent.is_movement_input():
				transition.emit("walk")
			else:
				transition.emit("idle")
		return

	# --- PHASE 2: AIR PHYSICS ---
	player.velocity.y -= WorldPhysics.gravity * delta
	
	var input_dir = GameInputEvent.get_movement_input()
	if input_dir != Vector3.ZERO:
		player.direction = input_dir
		player.velocity.x = input_dir.x * player.speed * player.air_control
		player.velocity.z = input_dir.z * player.speed * player.air_control
		_update_fall_animation(input_dir)
	else:
		player.velocity.x = move_toward(player.velocity.x, 0, player.speed * 0.05)
		player.velocity.z = move_toward(player.velocity.z, 0, player.speed * 0.05)

	player.move_and_slide()

func _on_next_transitions() -> void:
	# Check for Landing
	if player.is_on_floor() and not is_landing:
		is_landing = true
		landing_timer = 0.1 # Short landing lag (shorter than jump is okay)

func _update_fall_animation(dir: Vector3) -> void:
	sprite.flip_h = false
	
	# Reuse Jump Animations but lock to Frame 3
	var anim_name = "jump_s"
	
	if dir.z < -0.1 and abs(dir.x) < 0.1:     anim_name = "jump_n"
	elif dir.z > 0.1 and abs(dir.x) < 0.1:    anim_name = "jump_s"
	elif dir.x > 0.1 and abs(dir.z) < 0.1:    anim_name = "jump_e"
	elif dir.x < -0.1 and abs(dir.z) < 0.1:   anim_name = "jump_e"; sprite.flip_h = true
	elif dir.z < -0.1 and dir.x > 0.1:        anim_name = "jump_ne"
	elif dir.z > 0.1 and dir.x > 0.1:         anim_name = "jump_se"
	elif dir.z > 0.1 and dir.x < -0.1:        anim_name = "jump_se"; sprite.flip_h = true
	elif dir.z < -0.1 and dir.x < -0.1:       anim_name = "jump_ne"; sprite.flip_h = true

	if sprite.animation != anim_name:
		sprite.play(anim_name)
		sprite.pause() 
		sprite.frame = 3 # Ensure we stay on falling frame

func _on_exit() -> void:
	sprite.play()
