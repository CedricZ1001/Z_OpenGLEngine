#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 directionToLight = normalize(-light.direction);
    float diffuseIntensity = max(dot(normal,directionToLight),0.0);

    vec3 reflectDirection = reflect(-directionToLight, normal);
    float specularIntensity = pow(max(dot(viewDir, reflectDirection),0.0),material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords)).rgb;
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse,TexCoords)).rgb;
    vec3 specular = light.specular * specularIntensity * vec3(texture(material.specular,TexCoords)).rgb;

    return (ambient + diffuse + specular);
}

void main(){
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    FragColor = vec4(result , 1.0);
}