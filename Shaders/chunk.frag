#version 330 core

struct PointLight
{
    vec3 lightColor;
    vec3 position;
    float kA; 
    float kD;
    float kS;
};

in vec3 fragPos;
in vec3 normal;

uniform PointLight pLight;

out vec4 FragColor;

void main()
{

    float amb = pLight.kA;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(fragPos - pLight.position);
    float diff = pLight.kD * max(dot(norm, lightDir), 0.0);

    vec3 ambient = amb * vec3(1.0, 1.0, 1.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    vec3 lighting = ambient + diffuse;

    //FragColor = vec4(lighting, 1.0);
    FragColor = vec4(normal, 1.0);
    
}