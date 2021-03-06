#include "Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {


}




/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getDiffuseIntensity() {
// TO DO: A canviar a la fase 1 de la practica 2

   //return(vec3(1.0, 1.0, 1.0));
    return this->diffuse;
}

/**
 * @brief Light::setDiffuseIntensity
 * @param i
 */
void Light::setDiffuseIntensity(vec3 i) {
    // TO DO: A canviar a la fase 1 de la practica 2
    // el float que es reb ha de multiplicar els tres valors de la intensitat difusa de la Light

    this->diffuse = i;

}
vec4 Light::getLightPosition() {
    // A canviar
    //return(vec4(0.0, 0.0, 0.0, 0.0));
    return this->position;
}

void Light::setLightPosition(vec4 v) {
    this->position = v;

}


vec4 Light::getDirection() {
    // A canviar
    //return(vec4(0.0, 0.0, 0.0, 0.0));
    return this->direction;
}

void Light::setDirection(vec4 v) {
    this->direction = v;
}

/**
 * @brief Light::switchOnOff
 */
void Light::switchOnOff() {
    // TO DO: A canviar a la fase 1 de la practica 2
    // Si esta en on la posa a off i a l'inreves

    this->active = !this->active;//si esta active la desactivamos y viceversa
 }

/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
    // TO DO: A canviar a la fase 1 de la practica 2

       //return(vec3(1.0, 1.0, 1.0));
    return this->ambient;
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    // el float que es reb ha de multiplicar els tres valors de la intensitat difusa de la Light
    this->ambient = value;

}



/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    // TO DO: A canviar a la fase 1 de la practica 2

       return this->specular;
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    // el float que es reb ha de multiplicar els tres valors de la intensitat difusa de la Light
    this->specular = value;

}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 Light::getCoeficients() const
{
    // TO DO: A canviar a la fase 1 de la practica 2

       return this->coef;
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void Light::setCoeficients(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    // el float que es reb ha de multiplicar els tres valors de la intensitat difusa de la Light
    this->coef = value;
}

/**
 * @brief Light::getEstaActivat
 * @return
 */
bool Light::getEstaActivat() const
{
    // TO DO: A canviar a la fase 1 de la practica 2

       return(this->active);
}

/**
 * @brief Light::setEstaActivat
 * @param value
 */
void Light::setEstaActivat(bool value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->active = value;

}

/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
    return Puntual;
}
/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->type = value;
}
