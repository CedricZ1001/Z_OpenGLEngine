#version 420 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform SpotLight  spotLight;
uniform vec3 cameraPos;
uniform sampler2D texture_diffuse1;

out vec4 FragColor;

void main(){

	// ambient
	vec3 ambient = spotLight.ambient * texture(material.diffuse,TexCoord).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(spotLight.position - FragPos);
	float diffuseIntensity = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = spotLight.diffuse * diffuseIntensity * texture(material.diffuse,TexCoord).rgb;

	// specular
	vec3 viewDirection = normalize(cameraPos - FragPos);
	vec3 reflectDirection = reflect(-lightDirection,norm);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection),0),material.shininess);
	vec3 specular = spotLight.specular * specularIntensity * texture(material.specular, TexCoord).rgb;

	//spotlight (soft edges)
	float theta = dot(lightDirection, normalize(-spotLight.direction));
	float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon , 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	//attenuation 
	float lightdistance = length(spotLight.position - FragPos);
	float attenuation = 1.0 / (spotLight.constant + spotLight.linear * lightdistance + spotLight.quadratic * (lightdistance * lightdistance));

	FragColor = vec4((ambient + diffuse + specular) , 1.0);
		
}
