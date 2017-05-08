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
    vec3 speculal;
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
    float a;
    float b;
    float c;
};

IN vec4 vPosition;
IN vec4 vColor;
IN vec3 vNormal;
uniform vec4 vOrigin;
uniform vec3 vAmbientGlobal; //light ambienteGlobal

uniform Material m;
uniform Light lights[2];

OUT vec4 color;

/*vec4 calL(int i){
    return normalize(lights[i].position - vPosition);
}

vec4 calV(){
    return normalize(vOrigin - vPosition);
}

vec4 calH(vec4 vecL, vec4 vecV){
    return normalize(vecL + vecV);
}
*/

vec4 calBlinnPhong(){

    //for lights

    /*vec4 vecL = calL(1);//todo pass the light iterator
    vec4 vecV = calV();
    vec4 vecH = calH();*/
    //float NH = vNormal * vecH;

    vec4 vecAmbientGlo = (m.ambient * vAmbientGlobal,1.0);
    vec4 ambient = (m.ambient* lights[1].ambient,1.0);


    return ambient;

}

void main()
{
    gl_Position = vPosition;

    //color = vOrigin;
    color = vec4(m.diffuse,1.0);
    //color = calBlinnPhong();
    //vec4 co = vec4(lights[1].diffuse.x,lights[1].diffuse.y,lights[1].diffuse.z, 1.0f);
    //color = co;
}


