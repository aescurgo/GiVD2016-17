#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 fPosition;
IN vec4 fNormal;


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

uniform Light lights[2];



void main()
{
    float intensity;
    vec4 color;

    vec4 directionLight = lights[0].position - fPosition;//vector que hay entre el pixel y la luz

    intensity = dot(normalize(directionLight) , normalize(fNormal));

    if(intensity > 0.95) color = vec4(1.0,0.5,0.5,1.0);
    else if(intensity > 0.5) color = vec4(0.6,0.3,0.3,1.0);
    else if(intensity > 0.25) color = vec4(0.4,0.2,0.2,1.0);
    else color = vec4(0.2,0.1,0.1,1.0);

    gl_FragColor = color;
}

