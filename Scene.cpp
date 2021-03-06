#include "Scene.h"

const int MAXDEPTH = 10;
Scene::Scene()
{

    // creacio de la camera
    vec3 lookfrom(13, 2, 3);
    //vec3 lookfrom(20, 5, 15); // LOOKFROM 2
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = 600;
    int pixelsY = 400;
    /*int pixelsX = 200;
    int pixelsY = 200;*/
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

    //Escenas de muestra
    RandomScene();
    //sceneOne();//2 planos + esfera NOTA: NOTA: habilitar lookfrom o lookfrom 2
    //sceneTwo();//habitacion + esferas + cubo  NOTA: habilitar lookfrom 2
    //sceneThree();//esferas + 2 luces puntuales
    //sceneFour();//triangulo NOTA: habilitar lookfrom 2 para mejor visualizacion

    addLight();
    
    setAmbientGlobal(vec3(0.01,0.01,0.01));
}

Scene::~Scene()
{
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            //TODO: hacer otro para los planos,tringulos, etc

            //el tipo de objeto es una instancia de sphere.. si es asi delete
            if (dynamic_cast<Sphere*>(objects[i]))
                    delete (Sphere *)(objects[i]);
            if (dynamic_cast<Plane*>(objects[i]))
                    delete (Plane *)(objects[i]);
            if (dynamic_cast<Triangle*>(objects[i]))
                    delete (Triangle *)(objects[i]);
            if (dynamic_cast<Cube*>(objects[i]))
                    delete (Cube *)(objects[i]);
        }
    }

    //delete all lights
    for(unsigned int i = 0; i < llums.size(); ++i){
        if(llums[i]){
            if (dynamic_cast<PuntualLight*>(llums[i]))
                    delete (PuntualLight *)(llums[i]);

        }
    }

    delete cam;
}

void Scene::setAmbientGlobal(vec3 ambient){
    this->ambGlobal = ambient;
}

void Scene::sceneOne(){
    objects.push_back(new Sphere(vec3(-3,1,1), 1, new Metall(vec3(0.2,0.2, 0.2),vec3(0.7, 0.6, 0.5),vec3( 0.7, 0.7, 0.7),10.0)));
    //objects.push_back(new Plane(vec3(1,0,0),vec3(-1,-15,-15), new Lambertian(vec3(0.4, 0.4, 0.4),vec3(0.4, 0.4, 0.4),vec3(0.4,0.4,0.4),10.0)));
    objects.push_back(new Plane(vec3(0,1,0),vec3(-15,-1,-15), new Lambertian(vec3(0.2, 0.2, 0.2),vec3(0.2, 0.2, 0.2),vec3(0.2,0.2,0.2),10.0)));
    objects.push_back(new Plane(vec3(0,0,1),vec3(-15,-15,-1), new Lambertian(vec3(0.6, 0.6, 0.6),vec3(0.6, 0.6, 0.6),vec3(0.6,0.6,0.6),10.0)));

}

void Scene::sceneTwo(){
    objects.push_back(new Sphere(vec3(5,2,7.5), 1, new Lambertian(vec3(0.0,0.05,0.05),vec3(0.4, 0.5, 0.5),vec3(0.04,0.7,0.7),10.078125)));
    objects.push_back(new Sphere(vec3(6,2,1.5), 1, new Metall(vec3(0.24725,0.1995, 0.0745),vec3(0.75164 , 0.60648, 0.22648),vec3( 0.628281,0.555802 , 0.366065),0.4)));
    objects.push_back(new Cube(vec3(2,2,2),vec3(0.5,0.5,0.5), new Lambertian(vec3(0.8, 0.2, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
    objects.push_back(new Plane(vec3(1,0,0),vec3(-0,-1,-1), new Metall(vec3(0.4, 0.4, 0.4),vec3(0.4, 0.4, 0.4),vec3(0.4,0.4,0.4),10.0)));
    objects.push_back(new Plane(vec3(0,1,0),vec3(-1,-0,-1), new Metall(vec3(0.2, 0.2, 0.2),vec3(0.2, 0.2, 0.2),vec3(0.2,0.2,0.2),10.0)));
    objects.push_back(new Plane(vec3(0,0,1),vec3(-1,-1,-0), new Metall(vec3(0.6, 0.6, 0.6),vec3(0.6, 0.6, 0.6),vec3(0.6,0.6,0.6),10.0)));
}

void Scene::sceneThree(){

    objects.push_back(new Sphere(vec3(0,0,-3), 0.3,new Lambertian(vec3(0.2,0.2,0.2),vec3(0.5, 0.5, 0.5),vec3(1.0,1.0,1.0),10.0)));
    objects.push_back(new Sphere(vec3(0,0,3), 0.3,new Lambertian(vec3(0.2,0.2,0.2),vec3(0.5, 0.5, 0.5),vec3(1.0,1.0,1.0),10.0)));
    objects.push_back(new Sphere(vec3(0,0,-1), 0.5, new Lambertian(vec3(0.0,0.0,0.0),vec3(0.5, 0.0, 0.0),vec3(0.7,0.6,0.6),.25)));
    objects.push_back(new Sphere(vec3(2,0,1), 0.6, new Lambertian(vec3(0.0,0.0,0.0),vec3(0.5, 0.0, 0.0),vec3(0.7,0.6,0.6),.25)));
    objects.push_back(new Sphere(vec3(-3,0,2), 0.2,new Metall(vec3(0.0215,0.1745,0.0215),vec3(0.07568, 0.61424, 0.07568),vec3(0.633,0.727811,0.633),0.6))); // esmeralda

    objects.push_back(new Sphere(vec3(-3,1,1), 1, new Metall(vec3(0.1,0.18725, 0.1745),vec3(0.396, 0.74151, 0.69102),vec3( 0.297254, 0.30829, 0.306678),0.1)));
    objects.push_back(new Sphere(vec3(0,-100.5,-1), 100, new Metall(vec3(0.19225,0.19225,0.19225),vec3(0.50754, 0.50754, 0.50754),vec3(0.508273,0.508273,0.508273),0.4))); // silver

}

void Scene::sceneFour(){

    objects.push_back(new Triangle(vec3(-1,-1,0),vec3(1,-2,0),vec3(0,1,0), new Lambertian(vec3(0.8, 0.2, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
    //objects.push_back(new Triangle(vec3(-1, -1, -5),vec3( 1, -1, -5),vec3(0, 1, -5), new Lambertian(vec3(0.8, 0.2, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
}

// TODO: Metode que genera una escena random de numObjects de tipus esfera, a diferents posicions,
// amb diferents radis i diferents materials. S'usa drand48 per generar numeros random

void Scene::RandomScene() {

   // objects.push_back(new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.5, 0.2, 0.7))));


    //objects.push_back(new Sphere(vec3(0,-1,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5))));
    //objects.push_back(new Sphere(vec3(1,-1,-1), 0.5, new Lambertian(vec3(0.8, 0.6, 0.2))));
    //objects.push_back(new Sphere(vec3(-1,-1,-1), 0.5, new Lambertian(vec3(0.6, 0.8, 0.2),vec3(0.8, 0.1, 0.0),vec3(0.0,1.0,1.0),5.0)));
    //objects.push_back(new Sphere(vec3(-1,0,-1), -0.45, new Lambertian(vec3(0.2, 0.6, 0.8),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
    //objects.push_back(new Plane(vec3(1,0,0),vec3(1,1,1), new Lambertian(vec3(0.2, 0.2, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
    //objects.push_back(new Plane(vec3(0,0,1),vec3(1,1,1), new Lambertian(vec3(0.8, 0.6, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
    //objects.push_back(new Plane(vec3(0,1,0),vec3(1,1,1), new Lambertian(vec3(0.2, 0.2, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));
    //objects.push_back(new Triangle(vec3(-1,-1,0),vec3(1,-1,0),vec3(0,1,0), new Lambertian(vec3(0.8, 0.2, 0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));

    //objects.push_back(new BoundaryObject("../F_05/resources/peo1K.obj", new Lambertian(vec3(0.2, 0.6, 0.8),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));

    //phase 2

    objects.push_back(new Sphere(vec3(0,0,-1), 0.5, new Lambertian(vec3(0.2,0.2,0.2),vec3(0.5, 0.5, 0.5),vec3(1.0,1.0,1.0),10.0)));
    objects.push_back(new Sphere(vec3(-3,1,1), 1, new Metall(vec3(0.2,0.2, 0.2),vec3(0.7, 0.6, 0.5),vec3( 0.7, 0.7, 0.7),10.0)));
    objects.push_back(new Sphere(vec3(0,-100.5,-1), 100, new Lambertian(vec3(0.2,0.2,0.2),vec3(0.8, 0.8, 0.0),vec3(1.0,1.0,1.0),10.0)));

    //profundidad,altura,der o iz

}

/*
 *
 */
void Scene::addLight()
{
    llums.push_back(new PuntualLight(vec3(2,8,10),vec3(0.4,0.4,0.4),vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0)));//izq
    //llums.push_back(new PuntualLight(vec3(2,8,-10),vec3(0.4,0.4,0.4),vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0)));//der
    //llums.push_back(new PuntualLight(vec3(20,5,18),vec3(0.4,0.4,0.4),vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0)));//pos obs

}

/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena (Fase 1)
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    //intersecta
    //hits a todos los objetos y quedamos con la t min
    //
    //aqui mirar la minima o no de t con info.  ...iterando con la t min me quedo con la t

    HitInfo infoTemp;
    bool inter = false;
    //for(Object *o: objects)
    for (int i=0; i<objects.size(); i++)
    {
        if (objects[i]->hit(raig,t_min,t_max,infoTemp))//si intersecta
        {
            if (info.t < infoTemp.t)
            {
                info = info ;//coprobamos si la t de info es más pequeña
                t_min= info.t;
            }
            //que la infoTemp del objeto que estamos mirando
            else
            {
                info =infoTemp;
                t_min = info.t;
            }

            inter = true;
        }

    }


    if (inter){
        //info = infoTemp;
        return true;
    }
    else return false;


    //return objects[0]->hit(raig,t_min,t_max,info);

    //return true;
    // TODO: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode hit per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig,
    // pero no en aquesta funcio.

}

/*
** TODO: Funcio ComputeColor es la funcio recursiva del RayTracing.
** A modificar en la Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en la Fase 2 per a tractar reflexions
**
*/


vec3 Scene::ComputeColor (Ray &ray, int depth) {

    vec3 color;
    vec3 colorReflejo;

    //si intersecta con objeto caculo el color
    //si no pongo el backgraound
    //llamaraemos a : testinterseccio  --> hit

    /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
     * el material de l'objecte i les llums per la fase 2 de la practica
     * En aquestesta fase 2,  cal fer que tambe es tinguin en compte els rebots de les reflexions.

       Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
       hitInfo ha d'anar tenint el color actualitzat segons els rebots.
    */
     //color = 0.5f*vec3(ray.direction.x+1, ray.direction.y+1, ray.direction.z+1);

    HitInfo info;//no tocar (es el principal)
    if(this->hit(ray,0,info.t,info))
    {
        //color = vec3(info.normal.x,info.normal.y,info.normal.z);
        //color = vec3(1,0,0);

        //applying gamma correction
        //color = vec3(glm::sqrt(info.mat_ptr->diffuse.x),glm::sqrt(info.mat_ptr->diffuse.y),glm::sqrt(info.mat_ptr->diffuse.z));

        //only blinn-phong
        //color = blinnPhong(info.p,info.normal,info.mat_ptr,true);


        Ray scattered;
        vec3 K;

        if(MAXDEPTH >= depth )
        {
            if (info.mat_ptr->scatter(ray,info,K, scattered))

                color = blinnPhong(info.p,info.normal,info.mat_ptr,true) + ComputeColor(scattered,depth + 1) *K;


        }

    }
    else
    {
        //float colorY = (ray.direction.y+1) * 0.5;//obtemos el valor de Y entre un rango de 0 y 1
        //color = ((1-colorY)*vec3(1.0,1.0,1.0)) + (colorY*vec3(0.5,0.7,1.0));//aqui vamos mostrando o blanco o azul dependiendo del valor de Y
        color = vec3(0.5,0.7,1);//aplicamos solo un color de fondo... ya que con el degradado salia un efecto raro
    }

     return color;
}

vec3 Scene::blinnPhong(vec3 point,vec3 normal,const Material *material,bool ombra)
{
    vec3 color, ambient,difus, especular,posLight,ambienteGlobal;

    //for each light we calculate the blinn-phong & shadows
    //for(Light *l : llums)
    for (int i=0; i<llums.size(); i++)
    {
        ambienteGlobal = material->ambient * this->ambGlobal;//calculamos el ambiente global -> materialAmbiente * por la ambiente Global definida por la escena

        //normalizamos todos los vectores necesarios para blinn
        normal = glm::normalize(normal);
        vec3 L = glm::normalize(llums[i]->pos - point);//vec Luz
        vec3 V = glm::normalize(vec3(13, 2, 3)- point);
        vec3 H = glm::normalize((L + V));
        float NH = glm::dot(normal,H);

        //lanzamos el rayoSombra
        float ep = 0.01;
        vec3 pointRay = point + (ep * L);
        Ray *rShadow =  new Ray(pointRay, L);

        HitInfo infoShadow;
        float factShadow = 1.0;
        if(hitShadow(rShadow,0,infoShadow.t, infoShadow)){//if intersect with object, it is in the shadow
            factShadow = 0.0;
        }

        ambient = material->ambient * llums[i]->ambient; //only Ka * Ia
        difus = material->diffuse * llums[i]->difus * glm::max(glm::dot(L , normal),0.0f); //only Kd * Id * L * N
        especular =(material->specular * llums[i]->especular) * glm::pow(glm::max(NH,0.0f),material->shininess); //only Ks

        float atenuacion = getAtenuacion4Point(llums[i]->pos, point);
        color = ambienteGlobal + color + (ambient + atenuacion * (factShadow * (difus +  especular)));


    }
    return color;
}

/*
 * Comprueba si hace hit con otros objetos de la escena
*/
bool Scene::hitShadow(Ray *raig,float t_min, float t_max, HitInfo& info){
    //for(Object *ob: objects)
    for (int i=0; i<objects.size(); i++)
    {
        if (objects[i]->hit(*raig,0,info.t,info))return true;
    }
}

float Scene::getAtenuacion4Point(vec3 posLight, vec3 point)
{
    float atenuacion;
    vec3 d = posLight - point;

    atenuacion = 1 /(0.5 + ( 0.01 * glm::dot(d,d)));

    return atenuacion;
}



