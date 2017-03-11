#ifndef PUNTUALLIGHT_H
#define PUNTUALLIGHT_H

#include "Light.h"


class PuntualLight: public Light
{
private:
    float a;
    float b;
    float c;
public:
    PuntualLight(vec3 pos, vec3 ia, vec3 id, vec3 is);
    ~PuntualLight();
};

#endif // PUNTUALLIGHT_H
