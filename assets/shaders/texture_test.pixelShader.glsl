#version 330 core

in vec2 v_TexCoord;
in vec3 v_Color;
layout(location = 0) out vec4 fragColor;

uniform sampler2D DiffuseMap;
uniform sampler2D texture1;

void main()
{
    vec2 uv = -1.0 + 2.0 * v_TexCoord;
    vec3 col = texture(DiffuseMap, uv).rgb;
//    vec3 normal = texture(NormalMap, uv).rgb;
//    vec3 col = v_Color;
//    col = vec3(0.0f, 1.0f, 0.0f);
    fragColor = vec4((col), 1.0f);
}

//////////
