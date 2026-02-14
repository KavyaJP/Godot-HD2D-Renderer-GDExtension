#ifndef HYBRID2D3D_SPRITE_H
#define HYBRID2D3D_SPRITE_H

#include <godot_cpp/classes/sprite3d.hpp>

namespace godot
{

    class Hybrid2D3DSprite : public Sprite3D
    {
        GDCLASS(Hybrid2D3DSprite, Sprite3D)

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
        AnchorMode anchor_mode; // Define the variable

        // Helper to auto-calculate pixel size
        void _update_pixel_size();

    protected:
        static void _bind_methods();

    public:
        Hybrid2D3DSprite();
        ~Hybrid2D3DSprite();

        // Add AABB Override (Crucial for fixing flickering)
        virtual AABB _get_aabb() const override;

        void set_sprite_height_px(float p_height);
        float get_sprite_height_px() const;

        void set_target_3d_height(float p_height);
        float get_target_3d_height() const;

        // Getters/Setters for Anchor
        void set_anchor_mode(AnchorMode p_mode);
        AnchorMode get_anchor_mode() const;
    };

} // namespace godot

// Register the Enum so Godot Inspector sees it
VARIANT_ENUM_CAST(Hybrid2D3DSprite::AnchorMode);

#endif