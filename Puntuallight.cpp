#include "Puntuallight.h"

PuntualLight::PuntualLight(vec3 pos, vec3 ia, vec3 id, vec3 is):Light()
{
    this->pos = pos;
    this->ambient = ia;
    this->difus = id;
    this->especular = is;
    this->coeAtenuacion = 0;

}

PuntualLight::~PuntualLight()
{}


