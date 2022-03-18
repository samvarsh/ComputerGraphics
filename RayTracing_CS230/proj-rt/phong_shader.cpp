#include "light.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{

    // reference : https://learnopengl.com/Lighting/Basic-Lighting
    vec3 color;
   // only one ambient 
    vec3 ambient = world.ambient_color * world.ambient_intensity;
    color = color_ambient * ambient;

    // Calculating diffuse, specular and shadows for each light
    for (int i = 0; i < world.lights.size(); i++)
    {
        vec3 light = world.lights.at(i)->position - intersection_point;
        vec3 light_norm = light.normalized();
        vec3 color_light = (world.lights.at(i)->Emitted_Light(light_norm)) / (light.magnitude_squared());

        if (world.enable_shadows)
        {
            // shadow ray casted from the intersection to the light source to see if its blocked by some obj inbetween
            Ray shadowRay;
            Hit shadowHit;

            shadowRay.direction = light_norm;
            shadowRay.endpoint = intersection_point;

            shadowHit = world.Closest_Intersection(shadowRay);
            if (shadowHit.object != nullptr)
            {
                if (shadowHit.dist < light.magnitude_squared())
                    continue;
            }
        }

        double diffuse_intensity = std::max(dot(normal, light_norm), 0.0);
        vec3 diffuse = color_diffuse * diffuse_intensity * color_light;

        // require from light to intersection, so negating
        vec3 u = ray.direction.normalized() * -1;
        vec3 reflectDir = (2 * dot(light_norm, normal) * normal) - light_norm;
        double specular_intensity = pow(std::max(dot(reflectDir, u), 0.0), specular_power);
        vec3 specular = color_specular * specular_intensity * color_light;


        // final color = combination of ambient diffuse and specular
        color = color + diffuse + specular;
    }
    return color;
}
