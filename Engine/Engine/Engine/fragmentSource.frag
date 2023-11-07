#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

//uniform sampler2D  ourTexture;
//uniform sampler2D  leatherTexture;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
	vec3 lightDir = normalize(lightPos - FragPos); 
	vec3 reflectVec = reflect(-lightDir , Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);

	//specular
	float specularAmount = pow(max(dot(reflectVec,cameraVec), 0), material.shininess);
	vec3 specular = material.specular * specularAmount * lightColor; 

	//diffuse
	//vec3 diffuse = material.diffuse * max(dot(lightDir, Normal), 0) * lightColor;
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb;

	//ambient
	vec3 ambient = material.ambient * ambientColor;
	//FragColor = vec4(objColor * ambientColor , 1.0);
	FragColor = vec4((diffuse + ambient + specular) * objColor, 1.0);
}
