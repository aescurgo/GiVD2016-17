#include "Triangle.h"

Triangle::Triangle(vec3 p1,vec3 p2,vec3 p3, Material *m) : Object(m)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    getNormal();
    this->d = getDistance();
}

bool Triangle::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    float t = -(glm::dot(this->normal,r.origin) + this->d)  / glm::dot(this->normal,r.direction);

    float nd = glm::normalize(glm::dot(this->normal,r.direction));


    if (glm::abs(nd) == 0.001) return false; //is in parallel with the ray.
    if (glm::abs(nd) < 0.001) return false;

    vec3 P = r.pointAtParameter(t);

    //check if the ray point is inside of triangle

    //coord barycentric (u,v,w)
    float u;
    float v;
    float w;
    float TriABC = (glm::normalize(glm::dot(this->p2 - this->p1,this->p3 - this->p1)) / 2.0);

    //triangle area's incluing the P
    float TriABP = (glm::normalize(glm::dot(this->p2 - this->p1, P - this->p1)) / 2.0);
    float TriBCP = (glm::normalize(glm::dot(this->p3 - this->p2, P - this->p2)) / 2.0);
    float TriCAP = (glm::normalize(glm::dot(this->p1 - this->p3, P - this->p3)) / 2.0);

    u = TriCAP / TriABC;
    v = TriABP / TriABC;
    w = TriBCP / TriABC;

    float res = glm::abs(u+v+w);
    //cout <<"res " << res <<endl;
    if( res== 1){
        if((0 <= res)&&(res <= 1)){
            rec.t = t;
            rec.p = P;
            rec.normal = this->normal ;
            rec.mat_ptr = material;
            return true;
        }
    }




    return false;
}

/**
 * @brief Triangle::getNormal
 * normal of triangle
 */
void Triangle::getNormal(){
    //N = ((P2-P1)* (P3-P1)) / |((P2-P1)* (P3-P1)| )
    this->normal = glm::normalize(glm::cross(this->p2 - this->p1,this->p3 - this->p1));

}


float Triangle::getDistance(){
    //float dir = -(glm::dot(this->normal,this->pPass));
    //return dir;
    return 0;
}
