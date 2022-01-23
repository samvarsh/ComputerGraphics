#include "plane.h"
#include "hit.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    Hit intersection = { 0, 0, 0 };

    // Math help from scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering
    // -simple-shapes/ray-plane-and-ray-disk-intersection 
    // POI = ((x1 - endpoint) * normal ) / ray * normal

    vec3 x = x1 - ray.endpoint;
    double numerator = dot(x, normal);
    double denominator = dot(ray.direction, normal);

    if (denominator != 0) // Make sure we're not dividing by 0!
    {
        double t = numerator / denominator;

        if (t > 0) // We have a hit!
        {
            intersection.object = this;
            intersection.dist = t;
            intersection.part = part;
        }
    }

    return intersection;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}

