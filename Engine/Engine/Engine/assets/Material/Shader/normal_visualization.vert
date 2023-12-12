#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

//out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

out VS_OUT {
    vec2 texCoords;
} vs_out;

layout(std140 , binding = 1) uniform Matrices{
    mat4 view;
    mat4 projection;
};

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;


void main() {
    FragPos = vec3(model*vec4(aPos,1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    //TexCoords = aTexCoords;
    vs_out.texCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos,1.0);
    //gl_PointSize = gl_Position.z;    
}
