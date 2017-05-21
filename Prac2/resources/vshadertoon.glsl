#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


//method normal


struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec4 direction;
    vec4 position;
    float angle;
    float alpha;
    vec3 coef;//atenuacion
};

uniform mat4 vModView;
uniform mat4 vModProj;

IN vec4 vNormal;
IN vec4 vPosition;
OUT vec4 fNormal;
OUT vec4 fPosition;


void main()
{
    gl_Position = vModProj * vModView * vPosition;
    fNormal = vNormal;
    fPosition = vPosition;
}


