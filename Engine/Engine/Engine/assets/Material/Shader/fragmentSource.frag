#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
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
uniform Light light;
uniform vec3 cameraPos;

out vec4 FragColor;

void main(){

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoord).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - FragPos);
	float diffuseIntensity = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * diffuseIntensity * texture(material.diffuse,TexCoord).rgb;

	// specular
	vec3 viewDirection = normalize(cameraPos - FragPos);
	vec3 reflectDirection = reflect(-lightDirection,norm);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection),0),material.shininess);
	vec3 specular = light.specular * specularIntensity * texture(material.specular,TexCoord).rgb;

	//spotlight (soft edges)
	float theta = dot(lightDirection,normalize(-light.direction));
	
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon , 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	//attenuation 
	float lightdistance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * lightdistance + light.quadratic * (lightdistance * lightdistance),0);
    


	FragColor = vec4((ambient + diffuse + specular) * attenuation, 1.0);
	
}
