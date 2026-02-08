#ifndef HD2D_SPRITE_H
#define HD2D_SPRITE_H

#include <godot_cpp/classes/geometry_instance3d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class HD2DSprite : public GeometryInstance3D {
    GDCLASS(HD2DSprite, GeometryInstance3D)

private:
    // Sprite properties
    Ref<Texture2D> texture;
    Vector2 sprite_size;
    bool pixel_perfect;
    float pixel_size;
    bool billboard_enabled;
    Color modulate;
    float alpha_scissor_threshold;

    // Mesh and material
    Ref<ArrayMesh> mesh;
    Ref<StandardMaterial3D> material;
    
    // Internal methods
    void _update_mesh();
    void _update_material();

protected:
    static void _bind_methods();

public:
    HD2DSprite();
    ~HD2DSprite();

    // Texture management
    void set_texture(const Ref<Texture2D> &p_texture);
    Ref<Texture2D> get_texture() const;

    // Size management
    void set_sprite_size(const Vector2 &p_size);
    Vector2 get_sprite_size() const;

    // Pixel perfect rendering
    void set_pixel_perfect(bool p_enabled);
    bool get_pixel_perfect() const;

    void set_pixel_size(float p_size);
    float get_pixel_size() const;

    // Billboard mode
    void set_billboard_enabled(bool p_enabled);
    bool get_billboard_enabled() const;

    // Color Modulation
    void set_modulate(const Color &p_color);
    Color get_modulate() const;

    // Alpha Scissor
    void set_alpha_scissor_threshold(float p_threshold);
    float get_alpha_scissor_threshold() const;

    // Godot lifecycle
    void _ready();
    void _process(double delta);
};

} // namespace godot

#endif // HD2D_SPRITE_H