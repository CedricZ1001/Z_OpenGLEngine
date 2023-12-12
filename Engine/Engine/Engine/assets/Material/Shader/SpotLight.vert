#version 420 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 modelMat;
//uniform mat4 viewMat;
//uniform mat4 projMat;
layout(std140 , binding = 1) uniform Matrices{
    mat4 view;
    mat4 projection;
};
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main(){
	FragPos = vec3(modelMat *vec4(aPos , 1.0)); 
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;
	TexCoord = aTexCoord;

	gl_Position = projection * view * vec4(FragPos, 1.0);
}
