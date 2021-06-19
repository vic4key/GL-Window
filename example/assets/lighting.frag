#version 330 core

out vec4 outputColor;
in Vertex
{
  vec3 position;
  vec3 normal;
} vertex;

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

void main()
{
  // calculate ambient
  vec3 ambient = light.ambient;

  // calculate diffuse
  vec3  dir  = normalize(light.direction);
  vec3  norm = normalize(vertex.normal);
  float diff = max(dot(norm, dir), 0.F);
  vec3  diffuse = light.diffuse * diff * vec3(1.F);

  // calculate specular
  vec3 viewDir = normalize(target - vertex.position);
  vec3 reflectDir = reflect(-dir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.F), 16.F);
  vec3 specular = light.specular * spec * vec3(1.F);

  // calculate lighting
  float visibility = 1.F;
  vec3 lighting = (ambient + visibility * (diffuse + specular)) * color;

  // calculate output color
  outputColor = vec4(pow(lighting, vec3(1.F / 2.2F)), 1.F);
}