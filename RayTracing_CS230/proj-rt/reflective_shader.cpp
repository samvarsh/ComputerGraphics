#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 reflection_color;
    vec3 current_color;
    Ray reflection_ray;

    vec3 v = (ray.endpoint - intersection_point).normalized();
    vec3 r = (-v * 2 * dot(v, normal) * normal).normalized();

    Ray temp(intersection_point + .001 * r, r);

    reflection_color = world.Cast_Ray(temp, (recursion_depth + 1));
    current_color = shader->Shade_Surface(temp, intersection_point, normal, recursion_depth);

    color = reflectivity * reflection_color + (1 - reflectivity) * current_color;
    return color;
}
