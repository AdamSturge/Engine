#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector3G.h>

struct Material
{
    public : 
        Vector3Gf ambient;
        Vector3Gf diffuse;
        Vector3Gf specular;
        GLfloat shininess;

        Material();
    
        Material(Vector3Gf ambient,Vector3Gf diffuse,Vector3Gf specular,GLfloat shininess);
};

#endif
