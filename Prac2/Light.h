#ifndef Light_H
#define Light_H

#include <Common.h>

// Tipus de Lights
enum LightType {Puntual, Direccional, Spot};

//struct to GPU
struct gl_Light{
    GLuint diffuse;
    GLuint ambient;
    GLuint specular;
    GLuint direction;
    GLuint position;
    //GLuint angle;
    //GLuint alpha;
    GLuint coef;
};

// Classe que representa els atributs d'una Light
class Light {
    public:
        Light(LightType l);

        vec3 diffuse;
        vec3 ambient;
        vec3 specular;
        vec4 direction;
        vec4 position;
        GLfloat angle;
        GLfloat alpha;
        vec3 coef;
        bool active;

        vec4 getLightPosition();
        void setLightPosition(vec4 v);

        void switchOnOff();//TODO

        vec3 getIa() const;
        void setIa(const vec3 &value);

        vec3 getDiffuseIntensity();
        void setDiffuseIntensity(vec3 i);

        vec3 getIs() const;
        void setIs(const vec3 &value);

        vec3 getCoeficients() const;
        void setCoeficients(const vec3 &value);

        vec4 getDirection();
        void setDirection(vec4 value);

        bool getEstaActivat() const;//TODO
        void setEstaActivat(bool value);

        LightType getTipusLight() const;
        void setTipusLight(const LightType &value);


};

#endif // Light_H
