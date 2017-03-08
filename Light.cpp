#include "Light.h"

Light::Light(vec3 ambient, vec3 difus, vec3 especular, vec3 pos)
{
    this->ambient = ambient;//Ia
    this->difus = difus;//Id
    this->especular = especular;//Is
    this->pos = pos;//light position
}
