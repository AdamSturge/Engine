#include <material.h>

Material::Material()
{
    ambient = Vector3Gf(1.0f,0.0f,0.0f);
    diffuse = Vector3Gf(1.0f,0.0f,0.0f);
    specular = Vector3Gf(0.0f,0.0f,0.0f);
    shininess = 0.0f;
}

Material::Material(Vector3Gf ambient,Vector3Gf diffuse,Vector3Gf specular,GLfloat shininess) : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
{}
