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
uniform vec4 vOrigin;
uniform vec3 vAmbientGlobal; //light ambienteGlobal

uniform Material m;
uniform Light lights[2];

//OUT vec4 color;
OUT vec4 fPosition;
OUT vec4 fNormal;
OUT vec4 fOrigin;


void main()
{
    gl_Position = vPosition;
    fNormal = vNormal;
    fPosition = vPosition;
    fOrigin = vOrigin;
}


