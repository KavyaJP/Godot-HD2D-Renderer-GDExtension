#include "hybrid2d3d_animated_sprite.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Hybrid2D3DAnimatedSprite::Hybrid2D3DAnimatedSprite()
{
    // Enforce HD-2D Rendering Standards
    set_billboard_mode(BaseMaterial3D::BILLBOARD_FIXED_Y);
    set_texture_filter(BaseMaterial3D::TEXTURE_FILTER_NEAREST);
    set_alpha_cut_mode(SpriteBase3D::ALPHA_CUT_DISCARD);
    set_alpha_scissor_threshold(0.5);
    set_centered(true);

    // Default Height Setup
    sprite_height = 32.0;
    set_offset(Vector2(0, sprite_height * 0.5));
}

Hybrid2D3DAnimatedSprite::~Hybrid2D3DAnimatedSprite()
{
}

void Hybrid2D3DAnimatedSprite::set_sprite_height(float p_height)
{
    sprite_height = p_height;

    // Smart Offset: Update Y but keep X (in case user manually tweaked it)
    Vector2 current = get_offset();
    set_offset(Vector2(current.x, sprite_height * 0.5));
}

float Hybrid2D3DAnimatedSprite::get_sprite_height() const
{
    return sprite_height;
}

void Hybrid2D3DAnimatedSprite::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_sprite_height", "height"), &Hybrid2D3DAnimatedSprite::set_sprite_height);
    ClassDB::bind_method(D_METHOD("get_sprite_height"), &Hybrid2D3DAnimatedSprite::get_sprite_height);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sprite_height", PROPERTY_HINT_NONE, "suffix:px"), "set_sprite_height", "get_sprite_height");
}