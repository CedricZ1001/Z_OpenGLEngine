#version 420 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;

out vec4 FragColor;

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 directionToLight = normalize(-light.direction);
    float diffuseIntensity = max(dot(normal,directionToLight),0.0);

   float specularIntensity = pow(max(dot(normal, normalize(directionToLight + viewDir)),0.0),64);
    vec3 ambient = light.ambient * texture(texture_diffuse1,TexCoords).rgb;
    vec3 diffuse = light.diffuse * diffuseIntensity * texture(texture_diffuse1,TexCoords).rgb;
    vec3 specular = light.specular * specularIntensity * texture(texture_specular1,TexCoords).rgb;

    return (ambient + diffuse + specular);
}

void main(){
   vec3 normalMapValue  = texture(texture_normal1,TexCoords).rgb;
   vec3 norm =  normalize(normalMapValue  * 2.0 - 1.0);
   norm = normalize(TBN * norm);
   //vec3 norm = normalize(Normal);

   vec3 viewDir = normalize(viewPos - FragPos);
   
   vec3 result = CalcDirLight(dirLight, norm, viewDir);
   FragColor = vec4(result , 1.0);

}

