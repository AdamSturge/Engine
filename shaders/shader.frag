#version 330 core
struct Light{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 viewPos;
uniform Light light;

void main()
{
 
    //Ambient
    vec3 ambient = light.ambient;

    // Diffuse
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(n,lightDir),0.0f);
    vec3 diffuse = diff * light.diffuse;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,n);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),32);
    vec3 specular = spec * light.specular;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result,1.0f);
}

