#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D  ourTexture;
uniform sampler2D  leatherTexture;
void main(){
	vec4 textureColor = texture(ourTexture, texCoord);
	vec4 leatherColor = texture(leatherTexture, texCoord);
	FragColor =  mix(textureColor , leatherColor, 0.5) + vertexColor * 0.3;
}