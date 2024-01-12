#version 420 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 color;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform vec3 viewPos;

uniform bool useDiffuseMap;
uniform bool useNormalMap;
uniform bool useSpecularMap;

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir){
    vec3 directionToLight = normalize(light.position-FragPos);
    float diffuseIntensity = max(dot(normal,directionToLight),0.0);
    
    float specularIntensity = pow(max(dot(normal, normalize(directionToLight + viewDir)),0.0),64);

    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    if(useDiffuseMap){
        ambient = light.ambient * texture(texture_diffuse1,TexCoords).rgb;
        diffuse = light.diffuse * diffuseIntensity * texture(texture_diffuse1,TexCoords).rgb;
    }
    else{
        ambient = light.ambient;
        diffuse = light.diffuse * diffuseIntensity;
    }
    if(useSpecularMap){
        specular = light.specular * specularIntensity * texture(texture_specular1,TexCoords).rgb;
    }
    else{
        specular = light.specular * specularIntensity;
    }
    return (ambient + diffuse + specular)*light.color;
}

void main(){
   vec3 norm;
   if (useNormalMap) {
        vec3 normalMapValue = texture(texture_normal1, TexCoords).rgb;
        norm = normalize(normalMapValue * 2.0 - 1.0);
        norm = normalize(TBN * norm);
   } else {
       norm = normalize(Normal);
   }

   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 result = CalcDirLight(light, norm, viewDir);
   FragColor = vec4(result , 1.0);

}

