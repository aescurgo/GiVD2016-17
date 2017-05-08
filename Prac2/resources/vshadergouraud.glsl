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
    vec3 speculat;
    float shininess;
};

struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec4 direction;
    vec4 posicion;
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
uniform vec3 vAmbientGlobal; //luz ambienteGlobal

uniform Material m;
uniform Light lights[2];

OUT vec4 color;

void main()
{
    gl_Position = vPosition;

    color = vOrigin;
    //color = vec4(m.diffuse,0.0f);
    //vec4 co = vec4(lights[1].diffuse.x,lights[1].diffuse.y,lights[1].diffuse.z, 1.0f);
    //color = co;
}
/*
vec4 calcBlinnPhong(){

}*/
