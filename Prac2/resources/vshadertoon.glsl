#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


//method interpolacion color


struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec4 direction;
    vec4 position;
    //float angle;
    //float alpha;
    vec3 coef;//atenuacion
};

IN vec4 vNormal;
IN vec4 vPosition;
OUT vec4 fNormal;


void main()
{
    gl_Position = vPosition;
    fNormal = vNormal;

}


