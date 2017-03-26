#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Object.h"
#include "Sphere.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "Camera.h"
#include "plane.h"
#include "Triangle.h"
#include "Cube.h"
#include "Light.h"
#include "Puntuallight.h"
#include "Metall.h"

class Scene: public Hitable
{
public:
    Scene();
    virtual ~Scene();

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth );

    // Vector d'objectes continguts a l'escena
    std::vector<Object*> objects;

    //Vector de Llums a l'escena
    std::vector<Light*> llums;

    // Camera: on está l'observador
    Camera *cam;

    //global ambient
    vec3 ambGlobal;

    //blinn-phong method
    vec3 blinnPhong(vec3 point,vec3 normal,const Material *material,bool ombra);

    //hit shodow
    bool hitShadow(Ray *r, float t_min, float t_max, HitInfo& info);

private:
    void RandomScene();
    void sceneOne();
    void sceneTwo();
    void sceneThree();
    void addLight();
    void setAmbientGlobal(vec3 ambient);
    float getAtenuacion4Point(vec3 postLight, vec3 point);

};

#endif // SCENE_H
