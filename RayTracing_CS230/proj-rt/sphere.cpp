#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    Hit intersection = { 0, 0, 0 };
    vec3 L = ray.endpoint - center;

    double b = dot((ray.direction + ray.direction), L);
    double c = dot(L, L) - (radius * radius);

    double disc = (b * b) - (4 * c);

    if (disc > 0)
    {
        double r1 = (-b + sqrt(disc)) / 2;
        double r2 = (-b - sqrt(disc)) / 2;

        if (r1 > 0 && r2 > 0)
        {
                intersection.object = this;
                intersection.dist = r2;
                intersection.part = part;
        }
    }

    return intersection;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    vec3 temp = (point - center) / radius;
    normal = temp.normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}

// ref : https://link.springer.com/content/pdf/10.1007%2F978-1-4842-4427-2_7.pdf
// ref : https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection