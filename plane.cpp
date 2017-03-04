#include "plane.h"

Plane::Plane(vec3 n,vec3 pPunt, Material *m) : Object(m)
{
    normal = n;
    pPuntual = pPunt;//Change to pPass
    d = getDistance();
}


bool Plane::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    float ln = glm::dot(r.direction,this->normal);


    if (glm::abs(ln) == 0.0) return false;//the line is in paralel

    if (glm::abs(ln)!= 0.0)//when ln different that 0
    {

        float d = glm::dot((this->pPuntual - r.initialPoint()), this->normal) / ln;
        if (d >= 0)
        {
            rec.t = d;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = normal ;
            rec.mat_ptr = material;

            return true;
        }


    }


    return false;
}

float Plane::getDistance(){

    this->d = -(this->normal.x * this->pPuntual.x + this->normal.y * this->pPuntual.y + this->normal.z * this->pPuntual.z);

}
