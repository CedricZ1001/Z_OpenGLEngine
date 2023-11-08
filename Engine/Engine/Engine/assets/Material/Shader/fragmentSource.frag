#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
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
	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor; 

	//diffuse
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;
	//vec3 diffuse = texture(material.diffuse, TexCoord).rgb;

	//ambient
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;
	//FragColor = vec4(objColor * ambientColor , 1.0);
	FragColor = vec4((diffuse + ambient + max(specular, 0)) * objColor, 1.0);
}
