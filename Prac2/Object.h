#ifndef Object_H
#define Object_H

#include <QObject>
#include <vector>
#include <Common.h>
#include <cara.h>
#include <Material.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

using namespace std;

typedef Common::vec4  point4;

// Classe que conte la representacio d'un Objecte: geometria, topologia, material i textures
class Object : public QObject {

    Q_OBJECT
protected:
    QString nom;
    vector<Cara> cares;
    vector<point4> vertexs;

    GLuint buffer;

    int     numPoints;
    point4 *points;
    point4 *normals;
    vector<vec4> allNormals;//aqui guardaremos todas las normales sin repetir

    // Els colors s'usen en la primera execució però després son prescindibles
    point4 *colors;



    int Index; // index de control del numero de vertexs a passar a la GPU

    QOpenGLTexture *texture;
    QOpenGLTexture *texture1;//para utilizar la textura Normal


    QGLShaderProgram *program;

public:
    //material
    Material *material;
    Object(const int npoints, QObject *parent = 0);
    Object(const int npoints, QString n);
    ~Object();

    virtual void readObj(QString filename);

    virtual void make();
    virtual void toGPU(QGLShaderProgram *p);
    virtual void toGPUTexture(QGLShaderProgram *pr);

    virtual void draw();
    virtual void drawTexture();

    Capsa3D calculCapsa3D();

    void calNormalVertex();

private:

    void construeix_cara ( char **words, int nwords);
    void initTextura();
};



#endif // Object_H
