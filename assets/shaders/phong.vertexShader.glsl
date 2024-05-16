#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec2 v_TexCoord;
out vec3 v_CrntPos;
out vec3 v_Normal;
out vec3 v_VertPos;
out mat3 v_TBN;

void main()
{
  vec4 temp = u_Model * vec4(position, 1.0f);
  v_CrntPos = vec3(temp);
  temp = u_View * temp;
  v_VertPos = vec3(temp);
  gl_Position = u_Proj * temp;
  v_TexCoord = texCoord;
  v_Normal = normal;

  vec3 T = normalize(vec3(u_Model * vec4(tangent, 0.0)));
  vec3 N = normalize(vec3(u_Model * vec4(normal, 0.0)));
  // re-orthogonalize T with respect to N
  T = normalize(T - dot(T, N) * N);
  // then retrieve perpendicular vector B with the cross product of T and N
  vec3 B = cross(N, T);

  v_TBN = transpose(mat3(T, B, N));
}

//////////
