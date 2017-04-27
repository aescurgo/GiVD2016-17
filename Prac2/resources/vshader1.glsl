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

IN vec4 vPosition;
IN vec4 vColor;

uniform Material m;

OUT vec4 color;

void main()
{
    gl_Position = vPosition;

    color = m.diffuse;
}
