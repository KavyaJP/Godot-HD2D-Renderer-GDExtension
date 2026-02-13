extends NodeState

@export var player: Player
@export var sprite: Hybrid2D3DAnimatedSprite
@export var air_control: float = 0.8 

# Timer to hold the landing frame briefly
var landing_timer : float = 0.0
var is_landing : bool = false

func _on_enter() -> void:
	is_landing = false
	landing_timer = 0.0
	
	# 1. Apply Jump Force
	player.velocity.y = player.jump_velocity
	
	# 2. Start Animation (Pause it immediately so we can control frames manually)
	_update_jump_animation(player.direction)
	sprite.pause() 

func _on_physics_process(delta: float) -> void:
	# --- PHASE 1: LANDING SEQUENCE ---
	if is_landing:
		# Lock velocity to zero while recovering (optional, feels "weighty")
		player.velocity.x = 0
		player.velocity.z = 0
		
		# Set to Landing Frame (4)
		sprite.frame = 4 
		
		# Count down
		landing_timer -= delta
		if landing_timer <= 0:
			if GameInputEvent.is_movement_input():
				transition.emit("walk")
			else:
				transition.emit("idle")
		return # Stop processing physics during landing lag

	# --- PHASE 2: AIR PHYSICS ---
	
	# Gravity & Movement (Same as before)
	player.velocity.y -= WorldPhysics.gravity * delta
	
	var input_dir = GameInputEvent.get_movement_input()
	if input_dir != Vector3.ZERO:
		player.direction = input_dir
		player.velocity.x = input_dir.x * player.speed * air_control
		player.velocity.z = input_dir.z * player.speed * air_control
	else:
		player.velocity.x = move_toward(player.velocity.x, 0, player.speed * 0.05)
		player.velocity.z = move_toward(player.velocity.z, 0, player.speed * 0.05)

	# --- PHASE 3: FRAME LOCKING LOGIC ---
	
	# Update direction animation (N, S, E, W...)
	_update_jump_animation(player.direction)
	
	# Select Frame based on Velocity
	if player.velocity.y > (player.jump_velocity * 0.5):
		sprite.frame = 1 # Fast Rising (Launch)
	elif player.velocity.y > 0:
		sprite.frame = 2 # Slow Rising (Apex)
	else:
		sprite.frame = 3 # Falling

	player.move_and_slide()

func _on_next_transitions() -> void:
	# Only transition if we land
	if player.is_on_floor() and not is_landing:
		# Trigger the landing sequence instead of exiting immediately
		is_landing = true
		landing_timer = 0.15 # Hold the landing frame for 0.15 seconds

func _update_jump_animation(dir: Vector3) -> void:
	sprite.flip_h = false
	
	# Pick the correct 8-way animation (same logic as Walk/Idle)
	# BUT we don't call .play() if it's already playing the right one, 
	# to avoid resetting the frame index to 0.
	
	var anim_name = "jump_s" # Default
	
	# --- CARDINALS ---
	if dir.z < -0.1 and abs(dir.x) < 0.1:     anim_name = "jump_n"
	elif dir.z > 0.1 and abs(dir.x) < 0.1:    anim_name = "jump_s"
	elif dir.x > 0.1 and abs(dir.z) < 0.1:    anim_name = "jump_e"
	elif dir.x < -0.1 and abs(dir.z) < 0.1:   anim_name = "jump_e"; sprite.flip_h = true

	# --- DIAGONALS ---
	elif dir.z < -0.1 and dir.x > 0.1:        anim_name = "jump_ne"
	elif dir.z > 0.1 and dir.x > 0.1:         anim_name = "jump_se"
	elif dir.z > 0.1 and dir.x < -0.1:        anim_name = "jump_se"; sprite.flip_h = true
	elif dir.z < -0.1 and dir.x < -0.1:       anim_name = "jump_ne"; sprite.flip_h = true

	# Only switch if changed (Prevents frame reset)
	if sprite.animation != anim_name:
		sprite.play(anim_name)
		sprite.pause() # Important: Pause immediately so we control frames!

func _on_exit() -> void:
	# Resume sprite logic for the next state (Walk/Idle)
	sprite.play()
