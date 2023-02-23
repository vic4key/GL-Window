#pragma once

/**
 * @file   model.h
 * @author Vic P.
 * @brief  Model
 */

#include <string>
#include <vector>

#include "mesh.h"

struct aiNode;
struct aiMesh;
struct aiScene;

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
  void load(const std::string& obj_file_path, bool use_assimp = true);
  void render(Shader& m_shader);

private:
  void   assimp_load(const std::string& obj_file_path);
  void   assimp_parse_mesh(const aiMesh& mesh, std::vector<vertex_t>& vertices, std::vector<uint16>& indices);
  size_t assimp_parse_meshes(const aiScene& scene, aiNode& node);
  size_t assimp_parse_materials(const aiScene& scene);

private:
  bool m_ready;
  std::string m_directory;
  std::vector<Mesh*> m_meshes;
  std::vector<Material*> m_materials;
};

}; // glwnd