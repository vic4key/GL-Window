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

#include "TinyObjLoader.h"

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glwnd
{

struct Material
{
  int                    id = -1;
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

void Model::load(const std::string& obj_file_path)
{
  if (!utils::is_file_exist(obj_file_path))
  {
    throw std::runtime_error("the model file not found");
  }

  const auto dir = utils::extract_file_directory_t<std::string>(obj_file_path);

  // parsing meshes & materials

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  auto succeed = tinyobj::LoadObj(shapes, materials, obj_file_path.c_str(), dir.c_str());
  if (!succeed.empty())
  {
    throw std::runtime_error("load model failed");
  }

  auto fn_load_material_texture = [&](const std::string& file_name) -> std::unique_ptr<Tex2D>
  {
    auto image_file_path = dir + file_name;
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

      is_texture_material = ptr_material->tex2d_diffuse != nullptr;
      shader.set_variable("is_texture_material", is_texture_material);

      if (is_texture_material)
      {
        glBindTexture(GL_TEXTURE_2D, 0);
        shader.set_variable("texture_diffuse", 0);
        ptr_material->tex2d_diffuse->use(true);
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

}; // glwnd