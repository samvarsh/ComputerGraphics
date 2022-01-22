#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    double min = std::numeric_limits<T>::max();
    Hit closest_obj = { nullptr, min, 0 };
    for (int i = 0; i < objects.size(); i++)
    {
        Hit intersectionInfo = objects[i]->Intersection(ray, small_t);
        if (intersectionInfo.dist < min)
            closest_obj = intersectionInfo;
    }
    return closest_obj;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    // set up the initial view ray here
    vec3 e = camera.position; // e - eye position
    vec3 u = camera.World_Position(pixel_index) - camera.position;

    Ray ray;
    ray.endpoint = e;
    ray.direction = u.normalized();
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    // determine the color here
    // find the closest intersection
    Hit closestInt = Closest_Intersection(ray);
    if (closestInt == NULL)
    {
        // background shader
        color = background_shader->Shade_Surface(ray, { 0,0,0 }, { 0,0,0 }, recursion_depth);
    }
    else
    {
        vec3 intPoint = ray.Point(closestInt.dist);
        vec3 n = closestInt.object->Normal(intPoint, closestInt.part);
        color = closestInt.object->material_shader->Shade_Surface(ray, intPoint, n, recursion_depth);
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
