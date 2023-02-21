#pragma once

/**
 * @file   model.h
 * @author Vic P.
 * @brief  Model
 */

#include <string>
#include <vector>

namespace glwnd
{

class Mesh;
class Tex2D;
class Shader;
struct Material;

class Model
{
public:
  Model();
  Model(Model&&) = delete;
  Model(const Model&) = delete;
  Model& operator=(Model&&) = delete;
  Model& operator=(const Model&) = delete;
  virtual ~Model();

  bool ready() const;
  void load(const std::string& obj_file_path);
  void render(Shader& m_shader);

private:
  bool m_ready;
  std::vector<Mesh*> m_meshes;
  std::vector<Material*> m_materials;
};

}; // glwnd