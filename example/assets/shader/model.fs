#version 330 core

in vec3 g_position;
in vec3 g_normal;
in vec2 g_texcoord;

out vec4 g_color;

uniform sampler2D diffuse;

struct Light
{
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light light;
uniform vec3  target;
uniform vec3  color;

uniform bool  texture_material;

void main()
{
  if (texture_material)
  {
    g_color = texture(diffuse, g_texcoord);
  }
  else
  {
    /*
    // calculate ambient
    vec3 ambient = light.ambient;

    // calculate diffuse
    vec3  dir  = normalize(light.direction);
    vec3  norm = normalize(g_normal);
    float diff = max(dot(norm, dir), 0.F);
    vec3  diffuse = light.diffuse * diff * vec3(1.F);

    // calculate specular
    vec3 viewDir = normalize(target - g_position);
    vec3 reflectDir = reflect(-dir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.F), 16.F);
    vec3 specular = light.specular * spec * vec3(1.F);

    // calculate lighting
    float visibility = 1.F;
    vec3 lighting = (ambient + visibility * (diffuse + specular)) * color;

    // calculate output color
    g_color = vec4(pow(lighting, vec3(1.F / 2.2F)), 1.F);
    */

    g_color = vec4(light.diffuse, 1.0);
  }
}