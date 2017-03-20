#ifndef METALL_H
#define METALL_H


#include "Material.h"

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Metall : public Material
{
public:

    Metall(const vec3& Ka,const vec3& color, const vec3& Ks, float shininess);
    ~Metall();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

};

#endif // METAL_H
