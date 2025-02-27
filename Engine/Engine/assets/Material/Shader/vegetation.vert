#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
layout(std140 , binding = 1) uniform Matrices{
    mat4 view;
    mat4 projection;
};
uniform mat4 model;

//uniform mat4 view;
//uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
}