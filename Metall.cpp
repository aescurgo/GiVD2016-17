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
    //vec3 target = rec.p + rec.normal + this->RandomInSphere();
    vec3 distance = r_in.origin + rec.p;
    vec3 target = distance- (2.0f * (distance * rec.normal) )* rec.normal;

    float ep = 0.01;
    vec3 p0 = rec.p + (ep * target);//to solve surface acne.. mod the point

    scattered = Ray(p0, target-p0);
    color = this->specular;
    return true;
}
