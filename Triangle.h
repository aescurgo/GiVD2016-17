#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"

class Triangle: public Object
{
private:
    vec3 p1,p2,p3;
    vec3 normal;
public:
    Triangle(vec3 p1,vec3 p2,vec3 p3, vec3 normal, Material *m);
    bool hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const;
    ~Triangle(){}
};

#endif // TRIANGLE_H
