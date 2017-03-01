#include "plane.h"

Plane::Plane(vec3 n,vec3 pPunt, Material *m) : Object(m)
{
    normal = n;
    pPuntual = pPunt;//Change to pPass
}


bool Plane::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    float ln = glm::dot(r.direction,this->normal);



    if (glm::abs(ln) > 0.0)//est en paralelo
    {

        float d = glm::dot((pPuntual - r.direction), normal) / ln;
        if (d == 0.0f)
        {
            return false;
        }
        else
        {
            rec.t = d;
            rec.p = r.pointAtParameter(rec.t);//TODO
            rec.normal = normal ;
            rec.mat_ptr = material;

            return true;
        }

    }


    return false;
}
