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
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    scattered = Ray(rec.p, target-rec.p);
    color = this->specular;
    return true; //KS
}
