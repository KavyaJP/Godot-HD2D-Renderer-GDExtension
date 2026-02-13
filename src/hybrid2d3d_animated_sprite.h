#ifndef HYBRID2D3D_ANIMATED_SPRITE_H
#define HYBRID2D3D_ANIMATED_SPRITE_H

#include <godot_cpp/classes/animated_sprite3d.hpp>

namespace godot
{

    class Hybrid2D3DAnimatedSprite : public AnimatedSprite3D
    {
        GDCLASS(Hybrid2D3DAnimatedSprite, AnimatedSprite3D)

    private:
        float sprite_height;

    protected:
        static void _bind_methods();

    public:
        Hybrid2D3DAnimatedSprite();
        ~Hybrid2D3DAnimatedSprite();
        
        void set_sprite_height(float p_height);
        float get_sprite_height() const;
    };

} // namespace godot

#endif