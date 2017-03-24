#include "Metall.h"



Metall::Metall(const vec3& Ka,const vec3& color, const vec3& Ks, float shininess):Material()
{
    this->diffuse = color;
    this->ambient = Ka;
    this->specular = Ks;
    this->shininess = shininess;
}

Metall::~Metall()
{}


bool Metall::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const
{

    //vec3 r = r_in.direction + (2 * glm::dot(r_in.direction ,rec.normal) ) * rec.normal;
    vec3 r = r_in.direction + (2.0f * (r_in.direction * rec.normal) ) * rec.normal;

    float ep = 0.01;
    float fuzzy = 0;


    vec3 target = r + fuzzy * this->RandomInSphere();

    vec3 p0 = rec.p + (ep * target);//to solve surface acne.. mod the point

    scattered = Ray(p0, target);

    color = this->specular;

    return true;
}
