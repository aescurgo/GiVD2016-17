#include "Scene.h"

/**
 * @brief Scene::Scene
 */
Scene::Scene() {
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
    lightAmbientGlobal = vec3(0.5, 0.1, 0.1);

    //adding light
    /*
     * [0] -> puntual
     * [1] -> direccional
     * [2] -> spot
     */

/*
    Light *spot = new Light(Spot);
    spot->setDiffuseIntensity(vec3(1.0,0.5,0.5));
    spot->setIa(vec3(0.4,0.4,0.4));
    spot->setIs(vec3(1.0,1.0,1.0));
    spot->setLightPosition(vec4(4.0,4.0,4.0,1.0));
    spot->setDirection(vec4(4.0,4.0,4.0,1.0));
    spot->setCoeficients(vec3(0.5,0.5,0.5));
    spot->setEstaActivat(false);*/
}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene() {
    elements.clear();
    lights.clear();
}

/**
 * @brief Scene::addObject
 * @param obj
 */
void Scene::addObject(Object *obj) {
    elements.push_back(obj);
    calculCapsaMinCont3DEscena();
}

/**
 * @brief Scene::draw
 */
void Scene::draw() {
    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->draw();
    }
}

/**
 * @brief Scene::drawTexture
 */
void Scene::drawTexture() {

    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->drawTexture();
    }
}

void Scene::setAlphaObject(float alpha) {

    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->material->setAlpha(alpha);
    }
}



/**
 * @brief Scene::getLightActual
 * @return
 */
Light* Scene::getLightActual(int i) {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    //return (lights[lights.size()-1]);
    return (lights[i]);
}

/**
 * @brief Scene::setLightActual
 * @param l
 */
void Scene::setLightActual(Light* l){
    lights[lights.size()-1]=l;
}



/**
 * @brief Scene::lightsToGPU
 * @param program
 */
void Scene::lightsToGPU(QGLShaderProgram *program){
// TO DO: A implementar a la fase 1 de la practica 2
    //cout << "numLight: " << lights.size() <<endl;
    gl_Light *li = new gl_Light[lights.size()];

    for(unsigned int i = 0; i < lights.size(); i++){
        li[i].diffuse = program->uniformLocation(QString("lights[%1].diffuse").arg(i));
        li[i].ambient = program->uniformLocation(QString("lights[%1].ambient").arg(i));
        li[i].specular = program->uniformLocation(QString("lights[%1].specular").arg(i));
        li[i].direction = program->uniformLocation(QString("lights[%1].direction").arg(i));
        li[i].position = program->uniformLocation(QString("lights[%1].position").arg(i));
        li[i].angle = program->uniformLocation(QString("lights[%1].angle").arg(i));
        li[i].alpha = program->uniformLocation(QString("lights[%1].alpha").arg(i));
        li[i].coef = program->uniformLocation(QString("lights[%1].coef").arg(i));
        li[i].active = program->uniformLocation(QString("lights[%1].active").arg(i));

        glUniform3fv(li[i].diffuse,1,lights[i]->getDiffuseIntensity());
        glUniform3fv(li[i].ambient,1,lights[i]->getIa());
        glUniform3fv(li[i].specular,1,lights[i]->getIs());
        glUniform4fv(li[i].direction,1,lights[i]->direction);
        glUniform4fv(li[i].position,1,lights[i]->getLightPosition());
        glUniform1f(li[i].angle,lights[i]->angle);
        glUniform1f(li[i].alpha,lights[i]->alpha);
        glUniform3fv(li[i].coef,1,lights[i]->getCoeficients());
        glUniform1i(li[i].active,lights[i]->active);


    }








}

void Scene::addLight(Light *l) {
    lights.push_back(l);

}

/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */
void Scene::setAmbientToGPU(QGLShaderProgram *program){
    // TO DO: A implementar a la fase 1 de la practica 2

    gl_ambientGlobal.ambientGlobal = program->uniformLocation("vAmbientGlobal");
    glUniform3fv(gl_ambientGlobal.ambientGlobal, 1, this->lightAmbientGlobal);

}


void Scene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (elements.size()==1) {
        capsaMinima = elements[0]->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<elements.size(); i++) {
       c = elements[i]->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}
