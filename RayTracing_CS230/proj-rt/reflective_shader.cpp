#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 resultantColor;
    vec3 reflection_color;
    vec3 current_color;
    Ray reflection_ray;

    vec3 shotRay = (ray.endpoint - intersection_point).normalized();
    vec3 refRay = (-shotRay * 2 * dot(shotRay, normal) * normal).normalized();

    Ray r(intersection_point + .001 * refRay, refRay);

    reflection_color = world.Cast_Ray(r, (recursion_depth + 1));
    current_color = shader->Shade_Surface(r, intersection_point, normal, recursion_depth);

    resultantColor = reflectivity * reflection_color + (1 - reflectivity) * current_color;
    return resultantColor;
}
