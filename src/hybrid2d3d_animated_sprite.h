#ifndef HYBRID2D3D_ANIMATED_SPRITE_H
#define HYBRID2D3D_ANIMATED_SPRITE_H

#include <godot_cpp/classes/animated_sprite3d.hpp>

namespace godot
{

    class Hybrid2D3DAnimatedSprite : public AnimatedSprite3D
    {
        GDCLASS(Hybrid2D3DAnimatedSprite, AnimatedSprite3D)

    public:
        // Define the Custom Enum
        enum AnchorMode
        {
            ANCHOR_CENTER,
            ANCHOR_BOTTOM_CENTER
        };

    private:
        float sprite_height_px;
        float target_3d_height;
        AnchorMode anchor_mode;

        void _update_pixel_size();

    protected:
        static void _bind_methods();

    public:
        Hybrid2D3DAnimatedSprite();
        ~Hybrid2D3DAnimatedSprite();

        // Add AABB Override (Crucial for fixing flickering later)
        virtual AABB _get_aabb() const override;

        void set_sprite_height_px(float p_height);
        float get_sprite_height_px() const;

        void set_target_3d_height(float p_height);
        float get_target_3d_height() const;

        // Getters/Setters for Anchor
        void set_anchor_mode(AnchorMode p_mode);
        AnchorMode get_anchor_mode() const;

        // To set a pose in animation
        void set_pose(const StringName &p_name, int p_frame);
    };

} // namespace godot

// Register the Enum so Godot Inspector sees it
VARIANT_ENUM_CAST(Hybrid2D3DAnimatedSprite::AnchorMode);

#endif