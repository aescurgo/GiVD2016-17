#ifndef CUBE_H
#define CUBE_H

#include "Object.h"

class Cube: public Object
{
private:
    vec3 vmin;
    vec3 vmax;

public:
    Cube(vec3 vmin,vec3 vmax, Material *m);
    bool hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const;
    ~Cube(){}
};

#endif // CUBE_H
