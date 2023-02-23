#pragma once

/**
 * @file   model.h
 * @author Vic P.
 * @brief  Model
 */

#include "glwnd/model.h"
#include "glwnd/mesh.h"
#include "glwnd/utils.h"
#include "glwnd/tex2d.h"
#include "glwnd/shader.h"

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TinyObjLoader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace glwnd
{

struct Material
{
  GLuint                 id = GL_INVALID_ID;
  tinyobj::material_t    material;
  std::unique_ptr<Tex2D> tex2d_ambient;
  std::unique_ptr<Tex2D> tex2d_diffuse;
  std::unique_ptr<Tex2D> tex2d_specular;
  std::unique_ptr<Tex2D> tex2d_normal;
};

Model::Model() : m_ready(false)
{
}

Model::~Model()
{
  m_ready = false;

  for (auto ptr : m_meshes)
  {
    if (ptr != nullptr)
    {
      delete ptr;
    }
  }

  for (auto ptr : m_materials)
  {
    if (ptr != nullptr)
    {
      delete ptr;
    }
  }
}

bool Model::ready() const
{
  return m_ready;
}

void Model::load(const std::string& obj_file_path, bool use_assimp)
{
  if (!utils::is_file_exist(obj_file_path))
  {
    throw std::runtime_error("the model file not found");
  }

  m_directory = utils::extract_file_directory_t<std::string>(obj_file_path);

  if (use_assimp)
  {
    this->assimp_load(obj_file_path);
    return;
  }

  // parsing meshes & materials

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  auto succeed = tinyobj::LoadObj(shapes, materials, obj_file_path.c_str(), m_directory.c_str());
  if (!succeed.empty())
  {
    throw std::runtime_error("load model failed");
  }

  auto fn_load_material_texture = [&](const std::string& file_name) -> std::unique_ptr<Tex2D>
  {
    auto image_file_path = m_directory + file_name;
    if (utils::is_file_exist(image_file_path))
    {
      std::unique_ptr<Tex2D> tex2d(new Tex2D);
      if (tex2d->initialize_from_image_file(image_file_path))
      {
        return tex2d;
      }
    }

    return nullptr;
  };

  for (auto& shape : shapes)
  {
    m_meshes.emplace_back(new Mesh(shape.name));
    auto ptr_mesh = m_meshes.back();
    ptr_mesh->load(shape);

    if (!shape.mesh.material_ids.empty())
    {
      auto material_id = shape.mesh.material_ids.front(); // TODO: Vic. Recheck. Currently, treat them are the same material id. It's right?
      if (material_id >= 0 && material_id < int(materials.size()))
      {
        m_materials.emplace_back(new Material);
        auto ptr_material = m_materials.back();

        ptr_material->id = material_id;
        ptr_material->material = materials[material_id];
        ptr_material->tex2d_ambient  = fn_load_material_texture(ptr_material->material.ambient_texname);
        ptr_material->tex2d_diffuse  = fn_load_material_texture(ptr_material->material.diffuse_texname);
        ptr_material->tex2d_specular = fn_load_material_texture(ptr_material->material.specular_texname);
        ptr_material->tex2d_normal   = fn_load_material_texture(ptr_material->material.normal_texname);

        ptr_mesh->material_id(material_id);
      }
    }
  }

  m_ready = true;
}

void Model::render(Shader& shader)
{
  if (!m_ready)
  {
    throw std::runtime_error("model is not ready to render");
  }

  for (auto ptr_mesh : m_meshes)
  {
    auto it = std::find_if(m_materials.begin(), m_materials.end(), [ptr_mesh](Material* ptr_material) -> bool
    {
      return ptr_mesh->material_id() == ptr_material->id;
    });

    bool is_texture_material = false;

    if (it != m_materials.cend())
    {
      auto ptr_material = *it;

      // only use one of the loaded materials (priority ordered)
      auto ptr_texture_material = \
        ptr_material->tex2d_diffuse  ? ptr_material->tex2d_diffuse.get()  :
        ptr_material->tex2d_specular ? ptr_material->tex2d_specular.get() :
        ptr_material->tex2d_normal   ? ptr_material->tex2d_normal.get()   :
        ptr_material->tex2d_ambient  ? ptr_material->tex2d_ambient.get()  : nullptr;

      is_texture_material = ptr_texture_material != nullptr;
      shader.set_variable("is_texture_material", is_texture_material);

      if (is_texture_material)
      {
        glBindTexture(GL_TEXTURE_2D, 0);
        shader.set_variable("texture_diffuse", 0);
        ptr_texture_material->use(true);
      }
      else
      {
        shader.set_variable("light.direction", glm::vec3(-3.F, 6.F, -3.F));
        shader.set_variable("light.ambient",   glm::make_vec3(ptr_material->material.ambient));
        shader.set_variable("light.diffuse",   glm::make_vec3(ptr_material->material.diffuse));
        shader.set_variable("light.specular",  glm::make_vec3(ptr_material->material.specular));
        shader.set_variable("color", glm::make_vec3(ptr_material->material.diffuse)); // TODO: Vic. Recheck. In mtl file, diffuse is color ?
      }
    }

    ptr_mesh->render();

    if (is_texture_material)
    {
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void Model::assimp_load(std::string const& obj_file_path)
{
  if (!utils::is_file_exist(obj_file_path))
  {
    throw std::runtime_error("the model file not found");
  }

  // loading model file

  Assimp::Importer loader;
  auto ptr_scene = loader.ReadFile(
    obj_file_path,
    aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (ptr_scene == nullptr || ptr_scene->mRootNode == nullptr || ptr_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
  {
    throw std::runtime_error("load model failed");
  }

  m_directory = utils::extract_file_directory_t(obj_file_path);

  // parsing meshes & materials

  this->assimp_parse_meshes(*ptr_scene, *ptr_scene->mRootNode);
  this->assimp_parse_materials(*ptr_scene);

  m_ready = true;
}

size_t Model::assimp_parse_meshes(const aiScene& scene, aiNode& node)
{
  for (unsigned int i = 0; i < node.mNumMeshes; i++)
  {
    if (auto ptr = scene.mMeshes[node.mMeshes[i]])
    {
      std::vector<uint16> indices;
      std::vector<vertex_t> vertices;
      this->assimp_parse_mesh(*ptr, vertices, indices);
      auto ptr_mesh = new Mesh(ptr->mName.C_Str());
      ptr_mesh->load(vertices, indices, ptr->mMaterialIndex);
      m_meshes.push_back(ptr_mesh);
    }
  }

  for (unsigned int i = 0; i < node.mNumChildren; i++)
  {
    this->assimp_parse_meshes(scene, *node.mChildren[i]);
  }

  return m_meshes.size();
}

void Model::assimp_parse_mesh(const aiMesh& mesh, std::vector<vertex_t>& vertices, std::vector<uint16>& indices)
{
  vertices.clear();
  vertices.resize(mesh.mNumVertices);
  for (unsigned int i = 0; i < mesh.mNumVertices; i++)
  {
    auto& vertex = vertices[i];

    // positions
    vertex.position.x = mesh.mVertices[i].x;
    vertex.position.y = mesh.mVertices[i].y;
    vertex.position.z = mesh.mVertices[i].z;

    // normals
    if (mesh.HasNormals())
    {
      vertex.normal.x = mesh.mNormals[i].x;
      vertex.normal.y = mesh.mNormals[i].y;
      vertex.normal.z = mesh.mNormals[i].z;
    }

    // texture coordinates
    if (mesh.mTextureCoords[0])
    {
      // texcoords
      vertex.texcoords.x = mesh.mTextureCoords[0][i].x;
      vertex.texcoords.y = mesh.mTextureCoords[0][i].y;

      // tangent
      vertex.tangent.x = mesh.mTangents[i].x;
      vertex.tangent.y = mesh.mTangents[i].y;
      vertex.tangent.z = mesh.mTangents[i].z;

      // bitangent
      vertex.bitangent.x = mesh.mBitangents[i].x;
      vertex.bitangent.y = mesh.mBitangents[i].y;
      vertex.bitangent.z = mesh.mBitangents[i].z;
    }
  }

  indices.clear();
  indices.reserve(mesh.mNumFaces * 3); // triangle has 3 vertices
  for (unsigned int i = 0; i < mesh.mNumFaces; i++)
  {
    aiFace& face = mesh.mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }
}

size_t Model::assimp_parse_materials(const aiScene& scene)
{
  auto fn_assimp_parse_material = [&](aiMaterial& material, aiTextureType type) -> std::unique_ptr<Tex2D>
  {
    if (material.GetTextureCount(type) == 0)
    {
      return nullptr;
    }

    aiString file_name;
    material.GetTexture(type, 0, &file_name);
    auto image_file_path = m_directory + file_name.C_Str();
    if (!utils::is_file_exist(image_file_path))
    {
      return nullptr;
    }

    std::unique_ptr<Tex2D> tex2d(new Tex2D);
    if (tex2d->initialize_from_image_file(image_file_path))
    {
      return tex2d;
    }

    return nullptr;
  };

  for (auto ptr_mesh : m_meshes)
  {
    auto material_id = ptr_mesh->material_id();
    if (material_id == GL_INVALID_ID)
    {
      continue;
    }

    auto it = std::find_if(m_materials.begin(), m_materials.end(), [&](Material* ptr_material) -> bool
    {
      return ptr_material->id == material_id;
    });
    if (it != m_materials.end())
    {
      continue;
    }

    if (auto ptr = scene.mMaterials[material_id])
    {
      m_materials.emplace_back(new Material);
      auto ptr_material = m_materials.back();
      ptr_material->id = material_id;
      //ptr_material->material = materials[material_id];
      ptr_material->tex2d_diffuse  = fn_assimp_parse_material(*ptr, aiTextureType_DIFFUSE);
      ptr_material->tex2d_specular = fn_assimp_parse_material(*ptr, aiTextureType_SPECULAR);
      ptr_material->tex2d_normal   = fn_assimp_parse_material(*ptr, aiTextureType_NORMALS);
      ptr_material->tex2d_ambient  = fn_assimp_parse_material(*ptr, aiTextureType_AMBIENT);
    }
  }

  return m_materials.size();
}

}; // glwnd