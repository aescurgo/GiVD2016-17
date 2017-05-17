#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

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

IN vec4 vPosition;
//IN vec4 vColor;
IN vec4 vNormal;
IN vec2 vCoordTexture;

uniform vec4 vOrigin;
uniform vec3 vAmbientGlobal; //light ambienteGlobal

uniform vec4 vModView;
uniform vec4 vModProj;

uniform Material m;
uniform Light lights[2];

OUT vec4 color;
OUT vec2 v_texcoord;

vec4 calL(int i){
    return normalize(lights[i].position - vPosition);
}

vec4 calV(){
    return normalize(vOrigin - vPosition);
}

vec4 calH(vec4 vecL, vec4 vecV){
    return normalize(vecL + vecV);
}


float calAtenuation(Light l){
    float a = l.coef[0];
    float b = l.coef[1];
    float c = l.coef[2];
    float dis = length(l.position - vPosition);
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
    vec4 normal = vNormal;
    vec4 vecV = calV();
    vec4 vecAmbientGlo = vec4(m.ambient * vAmbientGlobal,1.0);

    colorFinal = vecAmbientGlo;

    //puntual
    vec4 vecL = calL(0);
    vec4 vecH = calH(vecL,vecV);
    float NH  = dot(normal,vecH);

    vec4 ambient     = vec4(m.ambient * lights[0].ambient,1.0);
    vec4 diffuse     = vec4(m.diffuse * lights[0].diffuse,1.0 ) * max(dot(vecL,normal),0.0f);
    vec4 specular    = vec4(m.specular * lights[0].specular,1.0) * pow(max(NH,0.0f), m.shininess);
    float atenuation = calAtenuation(lights[0]);

    colorPuntual = (ambient + (atenuation * (diffuse + specular)));

    //direccional
    vec4 vecLDir = calL(1);
    vec4 vecHDir = calH(vecLDir,vecV);
    float NHDir  = dot(normal,vecHDir);

    vec4 ambientDir     = vec4(m.ambient * lights[1].ambient,1.0);
    vec4 diffuseDir     = vec4(m.diffuse * lights[1].diffuse,1.0 ) * max(dot(vecLDir,normal),0.0f);
    vec4 specularDir    = vec4(m.specular * lights[1].specular,1.0) * pow(max(NHDir,0.0f), m.shininess);
    float atenuationDir = calAtenuation(lights[1]);

    colorDireccional = (ambientDir + (atenuationDir * (diffuseDir + specularDir)));

    //si esta activa sumamos la contribucion de dicha luz al colorFinal
    //si no solo mostramos el ambiente global
    if (lights[0].active == true)
        colorFinal = colorPuntual;
    else if(lights[1].active == true)
        colorFinal += colorDireccional ;

    return colorFinal;

}


void main()
{
    //gl_Position = vModProj * vModView *vPosition;
    gl_Position = vPosition;

    color = calBlinnPhong();
    v_texcoord = vCoordTexture;//pasamos al fragmentShader

    //color= vNormal;
    //vec4 co = vec4(lights[1].diffuse.x,lights[1].diffuse.y,lights[1].diffuse.z, 1.0f);

}


