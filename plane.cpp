#include "plane.h"

Plane::Plane(vec3 n,vec3 pPunt, Material *m) : Object(m)
{
    normal = n;
    pPass = pPunt;//Change to pPass
    d = getDistance();
}


bool Plane::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    //nx * x + ny * y *nz * z + d = 0

    float t = -(glm::dot(this->normal,r.origin) + this->d)  / glm::dot(this->normal,r.direction);

    float nd = glm::normalize(glm::dot(this->normal,r.direction));

    if (glm::abs(nd) == 0.001) return false; //is in parallel with the ray.
    if (glm::abs(nd) > 0.001)
    {
        if (t >= 0.001)
        {
            rec.t = t;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = normal ;
            rec.mat_ptr = material;
            return true;
        }

    }
    return false;
}

/**
 * @brief Plane::getDistance
 * @return ditance
 * The distance whitch separetes with origin coord.
 */
float Plane::getDistance(){
    float dir = -(glm::dot(this->normal,this->pPass));
    return dir;

}
