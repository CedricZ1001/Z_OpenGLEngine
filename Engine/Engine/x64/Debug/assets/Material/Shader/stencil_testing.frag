#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

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

void main(){
    vec3 norm = normalize(Normal);
    //vec3 norm = texture(texture_height1,TexCoords).rgb;
    vec3 viewDir = normalize(viewPos - FragPos);

    FragColor = vec4(1.0,0,0,1);
}