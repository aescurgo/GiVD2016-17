#include "Material.h"


Material::Material() {
    //define material if you want a static for all

}

Material::Material(vec4 diffuse, vec3 ambient, vec3 specular, float shininess){
    this->diffuse   = diffuse;
    this->ambient   = ambient;
    this->specular  = specular;
    this->shininess = shininess;

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

    glUniform4fv(mate.diffuse,1,this->diffuse);
    glUniform3fv(mate.ambient,1,this->ambient);
    glUniform3fv(mate.specular,1,this->specular);
    glUniform1f(mate.shininess,this->shininess);

}