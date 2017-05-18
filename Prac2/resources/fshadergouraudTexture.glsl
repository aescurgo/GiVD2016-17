#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif
#define PI 3.1415926535

IN vec4 color;
IN vec4 fNormal;

uniform sampler2D texMap;

vec2 calCoordTexture(){

    float u = 0.5 - atan(fNormal.z, fNormal.x) / (2.0 * PI);
    float v = 0.5 - asin(fNormal.y) / PI;

    return vec2(u,v);
}

void main()
{
    //gl_FragColor = color;

    //aqui meterle un 20% color y el resto de la textura
    //Calcular aqui tambien la formula para obtener las coordTExtura
    vec2 v_texcoord = calCoordTexture();
    gl_FragColor = 0.25 * color + 0.75 * texture2D(texMap, v_texcoord);
}

