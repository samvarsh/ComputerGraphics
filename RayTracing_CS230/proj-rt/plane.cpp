#include "plane.h"
#include "hit.h"
#include "ray.h"
#include <cfloat>
#include <limits>


Hit Plane::Intersection(const Ray& ray, int part) const
{
    Hit intersection = { 0, 0, 0 };

    vec3 x = x1 - ray.endpoint;
    double p = dot(x, normal);
    double q = dot(ray.direction, normal);

    if (q != 0) 
    {
        double ans = p / q;
        if (ans > 0) 
        {
            intersection.object = this;
            intersection.dist = ans;
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

