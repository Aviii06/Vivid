#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 col;
layout(location = 3) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec2 v_TexCoord;
out vec3 v_Color;

uniform vec3 offsets[36];

void main()
{
  gl_Position = u_Proj * u_View * u_Model * vec4(position + offsets[gl_InstanceID], 1.0f);
  v_TexCoord = texCoord;
  v_Color = col;
}

//////////
