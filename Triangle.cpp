#include "Triangle.h"

Triangle::Triangle(vec p1,vec3 p2,vec3 p3,vec3 normal, Material *m) : Object(m)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->normal = normal;
}

bool Triangle::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    //TODO

    return false;
}
