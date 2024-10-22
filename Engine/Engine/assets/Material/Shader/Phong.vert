#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout(std140 , binding = 1) uniform Matrices{
    mat4 view;
    mat4 projection;
};

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    FragPos = vec3(model*vec4(aPos,1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);
}