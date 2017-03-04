#include "Triangle.h"

Triangle::Triangle(vec3 p1,vec3 p2,vec3 p3, Material *m) : Object(m)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    getNormal();
}

bool Triangle::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    //TODO no funciona



    //distance from the origin to the plane
    float d = glm::dot(this->normal,r.direction);


    if(glm::abs(d) < 0) return false;//ray and plane are parallel

    float d1 = glm::dot(this->normal,this->p1);
    //t distance  from the ray origin to point
    float t = ((glm::dot(this->normal, r.origin) +d1) / d);


    if (t < 0) return false; //triangle is behind

    vec3 P = r.pointAtParameter(t);//point

    //other test
    vec3 C;
    float d11 =0;

    vec3 edge1 = glm::normalize(this->p2 - this->p1);
    vec3 vp1 = P - this->p1;

    C = glm::cross(edge1,vp1);

    //d11 = glm::dot(r.origin,edge1);
    if(glm::dot(this->normal, C) + d11 < 0) return false; //P is on the right side

    vec3 edge2 = glm::normalize(this->p3 - this->p2);
    vec3 vp2 = P - this->p2;

    C = glm::cross(edge2,vp2);
    //d11 = glm::dot(r.origin,edge2);

    if(glm::dot(this->normal, C)+d11 < 0) return false; //P is on the right side

    vec3 edge3 = glm::normalize(this->p1 - this->p3);
    vec3 vp3 = P - this->p3;

    C = glm::cross(edge3,vp3);
    //d11 = glm::dot(r.origin,edge3);

    if(glm::dot(this->normal, C)+d11 < 0) return false; //P is on the right side

    //if arrived here...intersect done
    rec.t = t;
    rec.p = P;
    rec.normal = normal ;
    rec.mat_ptr = material;

    return true;
}

void Triangle::getNormal(){
    //N = ((P2-P1)* (P3-P1)) / |((P2-P1)* (P3-P1)| )
    this->normal = glm::normalize(glm::cross(this->p2 - this->p1,this->p3 - this->p1));

}
