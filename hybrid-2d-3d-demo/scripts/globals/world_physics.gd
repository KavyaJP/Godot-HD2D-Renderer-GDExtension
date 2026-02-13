class_name WorldPhysics
extends Node

# We use 'static var' so we can change them at runtime 
# (e.g., if the player enters a Zero-G zone or underwater level)
static var gravity : float = 9.8
static var terminal_velocity : float = 50.0
static var friction : float = 0.1
static var air_resistance : float = 0.02
