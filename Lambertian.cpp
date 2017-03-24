#include "Lambertian.h"

Lambertian::Lambertian( const vec3& Ka,const vec3& color, const vec3& Ks, float shininess):Material()
{
    diffuse = color;
    ambient = Ka;
    specular = Ks;
    this->shininess = shininess;
}

Lambertian::~Lambertian()
{}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    float ep = 0.01;
    vec3 p0 = rec.p + (ep * target);//to solve surface acne.. mod the point
    scattered = Ray(p0, target-p0);
    color = diffuse;
    return true;
}

