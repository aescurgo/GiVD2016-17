#ifndef LIGHT_H
#define LIGHT_H
#include "glm/glm.hpp"
#include <vector>
using namespace glm;
using namespace std;

class Light
{
private:
    vec3 ambient;
    vec3 difus;
    vec3 especular;
    vec3 pos;
public:
    Light(vec3 ambient, vec3 difus, vec3 especular,vec3 pos);
    ~Light();
};

#endif // LIGHT_H
