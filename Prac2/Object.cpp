#include <Object.h>
#include <readfile.h>

/**
 * @brief Object::Object
 * @param npoints
 * @param parent
 */
Object::Object(int npoints, QObject *parent) : QObject(parent){
    numPoints = npoints;
    points = new point4[numPoints];
    normals= new point4[numPoints];
    colors = new point4[numPoints];
    this->material = new Material();
 }

/**
 * @brief Object::Object
 * @param npoints
 * @param n
 */
Object::Object(int npoints, QString n) : numPoints(npoints){
    points = new point4[numPoints];
    normals= new point4[numPoints];
    colors = new point4[numPoints];
    //this->material = new Material(vec4(1.0,0.0,0.0,0.0),vec3(0.0),vec3(0.0),1.0);
    this->material = new Material();


    readObj(n);
    //initTextura();
    calNormalVertex();
    make();
}


/**
 * @brief Object::~Object
 */
Object::~Object(){
    delete points;
    delete normals;
    //delete colors;
}

/**
 * @brief Object::toGPU
 * @param pr
 */
void Object::toGPU(QGLShaderProgram *pr) {
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals

    program = pr;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(point4)*Index, NULL, GL_STATIC_DRAW );
    glEnable( GL_DEPTH_TEST );

    //remporal
    //glEnable(GL_TEXTURE_2D);

    program->bind();//add

}


/**
 * Pintat en la GPU.
 * @brief Object::draw
 */
void Object::draw(){
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals a la GPU



    // Aqui es torna a repetir el pas de dades a la GPU per si hi ha més d'un objecte
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] );
    //glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &colors[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &normals[0] );//pasamos las normales a la gpu por el buffer

    int vertexLocation = program->attributeLocation("vPosition");
    //int colorLocation = program->attributeLocation("vColor");
    int normalLocation = program->attributeLocation("vNormal");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);

    //program->enableAttributeArray(colorLocation);
    //program->setAttributeBuffer("vColor", GL_FLOAT, sizeof(point4)*Index, 4);

    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, sizeof(point4)*Index, 4);



    //remporal
    //texture->bind(0);
    //program->setUniformValue("texMap", 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );


    //

    this->material->toGPU(program);
}

/**
 * @brief Object::make
 */
void Object::make(){

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal calcular la normal a cada vertex a la CPU

    /*static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };*/

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            //colors[Index] = vec4(base_colors[j%4], 1.0);
            normals[Index] = allNormals[cares[i].idxVertices[j]]; //also add normals with the same dimensions like points.

            Index++;
        }
    }



}




/**
 * @brief Object::toGPUTexture
 * @param pr
 */
void Object::toGPUTexture(QGLShaderProgram *pr) {
    program = pr;

// TO DO: Cal implementar en la fase 2 de la practica 2
// S'ha d'activar la textura i es passa a la GPU
    program->setUniformValue("texMap", 0);
    program->setUniformValue("texMap1", 1);
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(point4)*Index, NULL, GL_STATIC_DRAW );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D); //para la texture

    program->bind();



}


/**
 * Pintat en la GPU.
 * @brief Object::drawTexture
 */
void Object::drawTexture(){

    initTextura();//inicializamos las texturas
    //activamos las texturas
    //pero tambien pasamos todo el buffer

    texture->bind(0);
    program->setUniformValue("texMap", 0);

    //activamos tambien la textura de las normales
    texture->bind(1);
    program->setUniformValue("texMap1", 1);

    glEnable(GL_TEXTURE_2D);

    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] );
    //glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &colors[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &normals[0] );//pasamos las normales a la gpu por el buffer

    int vertexLocation = program->attributeLocation("vPosition");
    //int colorLocation = program->attributeLocation("vColor");
    int normalLocation = program->attributeLocation("vNormal");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);

    //program->enableAttributeArray(colorLocation);
    //program->setAttributeBuffer("vColor", GL_FLOAT, sizeof(point4)*Index, 4);

    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, sizeof(point4)*Index, 4);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    this->material->toGPU(program);

}



/**
 * @brief Object::initTextura
 */
void Object::initTextura()
 {
    // TO DO: A implementar a la fase 2 de la practica 2
    // Cal inicialitzar la textura de l'objecte: veure l'exemple del CubGPUTextura
    qDebug() << "Initializing textures...";

    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    texture = new QOpenGLTexture(QImage("://resources/textures/earth1.png"));
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->bind(0);

    // Carregar la textura de normales
    glActiveTexture(GL_TEXTURE1);
    texture1 = new QOpenGLTexture(QImage("://resources/textures/earth3.png"));
    texture1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

    texture1->bind(1);

 }



// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic Object.
void Object::readObj(QString filename){

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5) {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'Object
                vertexs.push_back(point4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {

            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'Object
                // A modificar si es vol carregar mes de un Object
                construeix_cara (&ReadFile::words[1], nwords-1);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    // Calcul de les normals a cada cara
    for(unsigned int i=0; i<cares.size(); i++){
        cares[i].calculaNormal(vertexs);
    }


}


void Object::calNormalVertex()
{

    //allNormals = allNormals(vertexs.size()); //allocate all normals, his index is vertexID
    for (unsigned int i = 0; i < vertexs.size(); i++) allNormals.push_back(vec4(0.0f));
    vector<float> vertexID;
    int count = 0;
    float mod;

    for(unsigned int i = 0; i < cares.size(); i++){
        //cares[i].calculaNormal(vertexs);
        for(unsigned int j = 0; j < cares[i].idxVertices.size(); j++){
            vertexID.push_back(cares[i].idxVertices[j]);
            allNormals[cares[i].idxVertices[j]] += cares[i].normal;//vamos guardando las normales

            count++;
            //cout<<"cares-> "<<i <<" : "<<cares[i].idxVertices[j]<<endl;

        }

    }


    //hacemosla media para cada normal
    for(unsigned int i = 0; i < allNormals.size(); i++){
        mod = 0.0;
        mod = sqrt(pow(allNormals[i].x,2) + pow(allNormals[i].y,2) +pow(allNormals[i].z,2));
        allNormals[i] /= mod;
        //allNormals[i] = allNormals[vertexID[i]] / length(allNormals[vertexID[i]]);
        //cout << "normal-> " << normals[i] << endl;
    }



}

Capsa3D Object::calculCapsa3D()
{
    vec3    pmin, pmax;
    int     i;
    Capsa3D capsa;

    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;
    pmax = pmin;
    for(i=1; i<Index; i++) {
        if(points[i].x <pmin[0])
            pmin[0] = points[i].x;
        if(points[i].y <pmin[1])
            pmin[1] = points[i].y;
        if(points[i].z <pmin[2])
            pmin[2] = points[i].z;

        if(points[i].x >pmax[0])
            pmax[0] = points[i].x;
        if(points[i].y >pmax[1])
            pmax[1] = points[i].y;
        if(points[i].z >pmax[2])
            pmax[2] = points[i].z;
    }
    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}



void Object::construeix_cara ( char **words, int nwords) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(this->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    this->cares.push_back(face);
}
