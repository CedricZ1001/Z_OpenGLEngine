#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;

layout(std140 , binding = 1) uniform Matrices{
    mat4 view;
    mat4 projection;
};

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0); 
}