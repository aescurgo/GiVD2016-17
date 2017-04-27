#ifndef MATERIAL_H
#define MATERIAL_H

#include <Common.h>
#include <QGLShaderProgram>

// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte

struct gl_Material
{
    GLuint diffuse;
    GLuint ambient;
    GLuint specular;
    GLuint shininess;

};

class Material {


public:
    Material();
    Material(vec4 diffuse, vec3 ambient, vec3 specular, float shininess);
    ~Material();
    vec4 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;

    void toGPU(QGLShaderProgram *program);

};

#endif // MATERIAL_H
