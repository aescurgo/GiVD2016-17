#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif
#define PI 3.1415926535

//IN vec4 color;
IN vec4 fPosition;
IN vec4 fNormal;
IN vec4 fOrigin;

uniform sampler2D texMap; //recibimos la textura

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec4 direction;
    vec4 position;
    float angle;
    float alpha;
    vec3 coef;//atenuacion
    bool active;
};

uniform vec4 vOrigin;
uniform vec3 vAmbientGlobal; //light ambienteGlobal

uniform Material m;
uniform Light lights[2];


vec4 calL(int i){
    return normalize(lights[i].position - fPosition);
}

vec4 calV(){
    return normalize(fOrigin - fPosition);
}

vec4 calH(vec4 vecL, vec4 vecV){
    return normalize(vecL + vecV);
}


float calAtenuation(Light l){
    float a = l.coef[0];
    float b = l.coef[1];
    float c = l.coef[2];
    float dis = length(l.position - fPosition);
    a = a * pow(dis,2.0);
    b = b * dis;

    return (1.0 / (a+b+c));
}


//metodo blinn, devulve el color asignado a cada pixel
/*
 * [0] -> puntual
 * [1] -> direccional
 * [2] -> spot
 */
vec4 calBlinnPhong(){
    vec4 colorFinal, colorPuntual, colorDireccional;

    //vec common to puntual, direccional y spot
    vec4 normal = fNormal;
    vec4 vecV = calV();
    vec4 vecAmbientGlo = vec4(m.ambient * vAmbientGlobal,1.0);

    colorFinal = vecAmbientGlo;


    //si esta activa sumamos la contribucion de dicha luz al colorFinal
    //si no solo mostramos el ambiente global
    if (lights[0].active == true){
        //puntual
        vec4 vecL = calL(0);
        vec4 vecH = calH(vecL,vecV);
        float NH  = dot(normal,vecH);

        vec4 ambient     = vec4(m.ambient * lights[0].ambient,1.0);
        vec4 diffuse     = vec4(m.diffuse * lights[0].diffuse,1.0 ) * max(dot(vecL,normal),0.0f);
        vec4 specular    = vec4(m.specular * lights[0].specular,1.0) * pow(max(NH,0.0f), m.shininess);
        float atenuation = calAtenuation(lights[0]);

        colorPuntual = (ambient + (atenuation * (diffuse + specular)));

        colorFinal = colorPuntual;
    }
    else if(lights[1].active == true){
        //direccional
        vec4 vecLDir = calL(1);
        vec4 vecHDir = calH(vecLDir,vecV);
        float NHDir  = dot(normal,vecHDir);

        vec4 ambientDir     = vec4(m.ambient * lights[1].ambient,1.0);
        vec4 diffuseDir     = vec4(m.diffuse * lights[1].diffuse,1.0 ) * max(dot(vecLDir,normal),0.0f);
        vec4 specularDir    = vec4(m.specular * lights[1].specular,1.0) * pow(max(NHDir,0.0f), m.shininess);
        float atenuationDir = calAtenuation(lights[1]);

        colorDireccional = (ambientDir + (atenuationDir * (diffuseDir + specularDir)));

        colorFinal += colorDireccional ;

    }

    return colorFinal;

}

vec2 calCoordTexture(){

    float u = 0.5 - atan(fNormal.z, fNormal.x) / (2.0 * PI);
    float v = 0.5 - asin(fNormal.y) / PI;

    return vec2(u,v);
}

void main()
{
    vec2 v_texcoord = calCoordTexture();
    vec4 color = calBlinnPhong();
    gl_FragColor = 0.25 * color + 0.75 * texture2D(texMap, v_texcoord);
}

