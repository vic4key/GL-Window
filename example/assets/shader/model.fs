#version 330 core

in vec3 g_position;
in vec3 g_normal;
in vec2 g_texcoord;

out vec4 g_color;

uniform sampler2D diffuse;

void main()
{
  g_color = texture(diffuse, g_texcoord);
}