#include "light.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    // Calculate the ambient color.
    // color = R_a * L_a
    // R_a = color of the object
    // L_a = color / intensity of the ambient lighting around the world.
    color = color_ambient * world.ambient_color * world.ambient_intensity;

    // Loop through all of the lights in the scene, calculate shadows, diffuse, and specular.
    for (unsigned int i = 0; i < world.lights.size(); i++)
    {
        vec3 light = world.lights.at(i)->position - intersection_point;
        vec3 color_light = (world.lights.at(i)->Emitted_Light(light.normalized())) / (light.magnitude_squared());

        // If shadows are enabled...
        if (world.enable_shadows)
        {
            Ray tempRay;
            Hit tempHit;

            tempRay.direction = light.normalized();
            tempRay.endpoint = intersection_point;

            tempHit = world.Closest_Intersection(tempRay);
            if (tempHit.object != NULL)
            {
                // If something is blocking the light ray, just leave it as ambient light.
                if (tempHit.dist < light.magnitude_squared())
                {
                    continue;
                }
            }
        }

        // Calculate the diffuse component.
        // Diffuse = R_d * L_d * max( dot(normal, light), 0)
        // R_d = reflected color off the object (essentially, the color of the object)
        // L_d = color/intensity of the light hitting the object
        double diffuse_intensity = std::max(0.0, dot(normal, light.normalized()));
        vec3 diffuse = color_diffuse * diffuse_intensity * color_light;

        // Calculate specular component.
        // Specular = R_s * L_s * max(v * reflection, 0) ^ alpha
        // R_s = reflected color of the 'shiny' spot
        // L_s = color / intensity of the light hitting the object
        // reflecton = reflection vector of the light
        // alpha = some specular constant, the higher alpha is the more 'shiny' the dot is
        vec3 reflection_vector = (2 * dot(light.normalized(), normal) * normal) - light.normalized();
        vec3 v = ray.direction.normalized() * -1;
        double specular_intensity = pow(std::max(dot(reflection_vector, v), 0.0), specular_power);
        vec3 specular = color_specular * specular_intensity * color_light;


        // Calculate the final color.
        // color = ambient + diffuse + specular
        color = color + diffuse + specular;
    }
    return color;
}
