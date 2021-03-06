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
    GLuint alpha;

};

class Material {


public:
    Material();
    Material(vec3 diffuse, vec3 ambient, vec3 specular, float shininess, float alpha);
    ~Material();
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
    float alpha;
    void setAlpha(float a);

    void toGPU(QGLShaderProgram *program);

};

#endif // MATERIAL_H
