#ifndef LIGHT_H
#define LIGHT_H
#include <vector3G.h>

struct Light
{
    public :
        Vector3Gf position;
        Vector3Gf ambient;
        Vector3Gf diffuse;
        Vector3Gf specular;

    Light();

    Light(Vector3Gf position, Vector3Gf ambient, Vector3Gf diffuse, Vector3Gf specular);
};
#endif
