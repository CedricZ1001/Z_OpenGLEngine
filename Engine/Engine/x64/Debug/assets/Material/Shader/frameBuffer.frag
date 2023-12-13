#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 600.0;  

void main()
{ 
    //FragColor = texture(screenTexture, TexCoords);

    //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

    //FragColor = texture(screenTexture, TexCoords);
    //float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
    //FragColor = vec4(average, average, average, 1.0);

    //FragColor = texture(screenTexture, TexCoords);
    //float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    //FragColor = vec4(average, average, average, 1.0);

    //锐化
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    //default
    float kernel[9] = float[](
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    );

    //模糊
    /*float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
    );*/

    //锐化
    /*float kernel[9] = float[](
        2, 2, 2,
        2, -15, 2,
        2, 2, 2
    );*/
    
    //边缘检测
    /* float kernel[9] = float[](
        1, 1, 1,
        1, -8,1,
        1, 1, 1
    );*/

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 color = vec3(0.0);
    for(int i = 0; i < 9; i++)
        color += sampleTex[i] * kernel[i];

    FragColor = vec4(color, 1.0);
   float gamma = 2.2;
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}