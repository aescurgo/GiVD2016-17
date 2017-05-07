#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

struct Material{
    vec4 diffuse;
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

uniform Material m;
uniform Light lights[2];

OUT vec4 color;

void main()
{
    gl_Position = vPosition;

    color = vec4(0.0,0.0,1.0,1.0);
    //color = lights[1].diffuse;
    //vec4 co = vec4(lights[1].diffuse.x,lights[1].diffuse.y,lights[1].diffuse.z, 1.0);
    //color = co;
}
