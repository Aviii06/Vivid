#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 col;
layout(location = 3) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform vec3 offsets[36];

out vec2 v_TexCoord;
out vec3 v_Color;
out vec3 v_CrntPos;
out vec3 v_Normal;
out vec3 v_Offset;

void main()
{
  vec3 newPos = position + offsets[gl_InstanceID];
  v_CrntPos = vec3(u_Model * vec4(newPos, 1.0f));
  gl_Position = (u_Proj * u_View * u_Model * vec4(newPos, 1.0f));
  v_TexCoord = texCoord;
  v_Color = col;
  v_Normal = normal;
  v_Offset = vec3((gl_InstanceID) / 36.0f);
}

//////////
