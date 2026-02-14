#include "hybrid2d3d_sprite.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Hybrid2D3DSprite::Hybrid2D3DSprite()
{
    // Defaults
    set_billboard_mode(BaseMaterial3D::BILLBOARD_FIXED_Y);
    set_texture_filter(BaseMaterial3D::TEXTURE_FILTER_NEAREST);
    set_alpha_cut_mode(SpriteBase3D::ALPHA_CUT_DISCARD);
    set_alpha_scissor_threshold(0.5);
    set_centered(true);

    // Default Values
    sprite_height_px = 32.0;
    target_3d_height = 1.7;
    anchor_mode = ANCHOR_BOTTOM_CENTER; // Default to Smart Anchor

    // Apply Initial Calculations
    _update_pixel_size();
}

Hybrid2D3DSprite::~Hybrid2D3DSprite()
{
}

void Hybrid2D3DSprite::_update_pixel_size()
{
    if (sprite_height_px > 0.0)
    {
        // Calculate Pixel Size (Scaling)
        double new_pixel_size = target_3d_height / sprite_height_px;
        set_pixel_size(new_pixel_size);

        // Apply Smart Anchor (Offsetting)
        if (anchor_mode == ANCHOR_BOTTOM_CENTER)
        {
            // Shift UP by half height so (0,0) is at the feet
            set_offset(Vector2(0, sprite_height_px * 0.5));
        }
        else
        {
            // Standard Centered
            set_offset(Vector2(0, 0));
        }
    }
}

void Hybrid2D3DSprite::set_sprite_height_px(float p_height)
{
    sprite_height_px = p_height;
    _update_pixel_size();
    notify_property_list_changed();
}

float Hybrid2D3DSprite::get_sprite_height_px() const
{
    return sprite_height_px;
}

void Hybrid2D3DSprite::set_target_3d_height(float p_height)
{
    target_3d_height = p_height;
    _update_pixel_size();
    notify_property_list_changed();
}

float Hybrid2D3DSprite::get_target_3d_height() const
{
    return target_3d_height;
}

// Implement Anchor Setter
void Hybrid2D3DSprite::set_anchor_mode(AnchorMode p_mode)
{
    anchor_mode = p_mode;
    _update_pixel_size(); // Recalculate offset immediately
}

Hybrid2D3DSprite::AnchorMode Hybrid2D3DSprite::get_anchor_mode() const
{
    return anchor_mode;
}

// Implement AABB Fix (Prevents flickering)
AABB Hybrid2D3DSprite::_get_aabb() const
{
    AABB aabb = Sprite3D::get_aabb();
    real_t max_len = MAX(aabb.size.x, aabb.size.y);
    aabb.position = Vector3(-max_len, 0, -max_len);
    aabb.size = Vector3(max_len * 2.0, aabb.size.y, max_len * 2.0);
    return aabb;
}

void Hybrid2D3DSprite::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_sprite_height_px", "height"), &Hybrid2D3DSprite::set_sprite_height_px);
    ClassDB::bind_method(D_METHOD("get_sprite_height_px"), &Hybrid2D3DSprite::get_sprite_height_px);

    ClassDB::bind_method(D_METHOD("set_target_3d_height", "height"), &Hybrid2D3DSprite::set_target_3d_height);
    ClassDB::bind_method(D_METHOD("get_target_3d_height"), &Hybrid2D3DSprite::get_target_3d_height);

    // Bind Anchor Methods
    ClassDB::bind_method(D_METHOD("set_anchor_mode", "mode"), &Hybrid2D3DSprite::set_anchor_mode);
    ClassDB::bind_method(D_METHOD("get_anchor_mode"), &Hybrid2D3DSprite::get_anchor_mode);

    ADD_GROUP("Hybrid 2D3D Scaling", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sprite_height_px", PROPERTY_HINT_RANGE, "1,512,1,or_greater,suffix:px"), "set_sprite_height_px", "get_sprite_height_px");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "target_3d_height", PROPERTY_HINT_RANGE, "0.1,10.0,0.01,or_greater,suffix:m"), "set_target_3d_height", "get_target_3d_height");

    // Add Anchor to Inspector
    ADD_PROPERTY(PropertyInfo(Variant::INT, "anchor_mode", PROPERTY_HINT_ENUM, "Center,Bottom Center"), "set_anchor_mode", "get_anchor_mode");

    // Bind Enum Constants
    BIND_ENUM_CONSTANT(ANCHOR_CENTER);
    BIND_ENUM_CONSTANT(ANCHOR_BOTTOM_CENTER);
}