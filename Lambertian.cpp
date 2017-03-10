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
    scattered = Ray(rec.p, target-rec.p);
    color = diffuse;
    return true;
}

