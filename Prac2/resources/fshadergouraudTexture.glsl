#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 color;
IN vec2 v_texcoord;

uniform sampler2D texMap;

void main()
{
    gl_FragColor = color;

    //aqui meterle un 20% color y el resto de la textura
    //Calcular aqui tambien la formula para obtener las coordTExtura

    //gl_FragColor = texture2D(texMap, v_texcoord);
}

