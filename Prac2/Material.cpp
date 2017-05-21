#include "Material.h"


Material::Material() {

    this->diffuse   = vec3(0.8, 0.3, 0.0);
    this->ambient   = vec3(0.2,0.2,0.2);
    this->specular  = vec3(1.0,1.0,1.0);
    this->shininess = 10.0;
    this->alpha     = 1.0;


}

Material::Material(vec3 diffuse, vec3 ambient, vec3 specular, float shininess, float alpha){
    this->diffuse   = diffuse;
    this->ambient   = ambient;
    this->specular  = specular;
    this->shininess = shininess;
    this->alpha     = alpha;

}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(QGLShaderProgram *program){

    gl_Material mate;
    mate.diffuse = program->uniformLocation("m.diffuse");
    mate.ambient = program->uniformLocation("m.ambient");
    mate.specular = program->uniformLocation("m.specular");
    mate.shininess = program->uniformLocation("m.shininess");
    mate.alpha = program->uniformLocation("m.alpha");

    glUniform3fv(mate.diffuse,1,this->diffuse);
    glUniform3fv(mate.ambient,1,this->ambient);
    glUniform3fv(mate.specular,1,this->specular);
    glUniform1f(mate.shininess,this->shininess);
    glUniform1f(mate.alpha,this->alpha);

}
