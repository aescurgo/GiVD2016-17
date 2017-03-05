#include "Cube.h"

Cube::Cube(vec3 vmin, vec3 vmax, Material *m) : Object(m)
{
    this->vmin = vmin;
    this->vmax = vmax;

}

bool Cube::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    float tmin = (vmin.x - r.origin.x) / r.direction.x;
    float tmax = (vmax.x - r.origin.x) / r.direction.x;

    if (tmin > tmax)
    {
        tmin = tmax;
        tmax = tmin;
    }

    float tymin = (vmin.y - r.origin.y) / r.direction.y;
    float tymax = (vmax.y - r.origin.y) / r.direction.y;

    if (tymin > tymax)
    {
        tymin = tymax;
        tymax = tymin;
    }

    if((tmin > tymax) or (tymin > tmax)) return false;

    if (tymin > tmin) tmin = tymin;

    if (tymax < tmax) tmax = tymax;

    float tzmin = (vmin.z - r.origin.z) / r.direction.z;
    float tzmax = (vmax.z - r.origin.z) / r.direction.z;

    if (tzmin > tzmax)
    {
        tzmin = tzmax;
        tzmax = tzmin;
    }

    if((tmin > tzmax) or (tzmin > tmax)) return false;

    if (tzmin > tmin) tmin = tzmin;

    if (tzmax < tmax) tmax = tzmax;

    //if arrived here...intersect done
    float t = glm::min(tmin,tmax);
    rec.t = t;//TODO
    rec.p =  r.pointAtParameter(rec.t);
    rec.normal = vec3(0,1,0);//TODO
    rec.mat_ptr = material;


    return true;
}
