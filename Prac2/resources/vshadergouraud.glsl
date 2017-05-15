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
    //vec4 direction;
    vec4 position;
    //float angle;
    //float alpha;
    vec3 coef;//atenuacion
};

IN vec4 vPosition;
//IN vec4 vColor;
IN vec4 vNormal;
uniform vec4 vOrigin;
uniform vec3 vAmbientGlobal; //light ambienteGlobal

uniform vec4 vModView;
uniform vec4 vModProj;

uniform Material m;
uniform Light lights[2];

OUT vec4 color;

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


vec4 calBlinnPhong(){
    vec4 normal = vNormal;
    vec4 vecL = calL(0);//todo pass the light iterator
    vec4 vecV = calV();
    vec4 vecH = calH(vecL,vecV);
    float NH = dot(normal,vecH);

    vec4 vecAmbientGlo = vec4(m.ambient * vAmbientGlobal,1.0);
    vec4 ambient = vec4(m.ambient * lights[0].ambient,1.0);
    vec4 diffuse = vec4(m.diffuse * lights[0].diffuse,1.0 ) * max(dot(vecL,normal),0.0f);
    vec4 specular = vec4(m.specular * lights[0].specular,1.0) * pow(max(NH,0.0f), m.shininess);
    float atenuation = calAtenuation(lights[0]);

    return vecAmbientGlo + ambient + (atenuation * (diffuse + specular));

}


void main()
{
    //gl_Position = vModProj * vModView *vPosition;
    gl_Position = vPosition;

    color = calBlinnPhong();
    //color= vNormal;
    //vec4 co = vec4(lights[1].diffuse.x,lights[1].diffuse.y,lights[1].diffuse.z, 1.0f);

}


