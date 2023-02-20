/**
 * @file   mesh.cpp
 * @author Vic P.
 * @brief  Mesh
 */

#include "glwnd/mesh.h"
#include "glwnd/utils.h"
#include "glwnd/defs.h"
#include "glwnd/vao.h"
#include "glwnd/tex2d.h"

#include "TinyObjLoader.h"

namespace glwnd
{

struct Material
{
  tinyobj::material_t    material;
  std::unique_ptr<Tex2D> tex2d_ambient;
  std::unique_ptr<Tex2D> tex2d_diffuse;
  std::unique_ptr<Tex2D> tex2d_specular;
  std::unique_ptr<Tex2D> tex2d_normal;
};

Mesh::Mesh() : m_ptr_vao(new VAO), m_ready(false)
{
}

Mesh::~Mesh()
{
  for (auto ptr : m_materials)
  {
    if (ptr != nullptr)
    {
      delete ptr;
    }
  }

  if (m_ptr_vao != nullptr)
  {
    delete m_ptr_vao;
  }
}

bool Mesh::ready() const
{
  return m_ready && m_ptr_vao->ready();
}

void Mesh::load(const std::string& obj_file_path)
{
  assert(!obj_file_path.empty());

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  const auto file_dir = utils::extract_file_directory_t<std::string>(obj_file_path);

  tinyobj::LoadObj(shapes, materials, obj_file_path.c_str(), file_dir.c_str());

  // positions

  m_positions.reserve(utils::align_up(shapes[0].mesh.positions.size() / 3));

  for (uint32 i = 0; i < shapes[0].mesh.positions.size(); i += 3)
  {
    m_positions.emplace_back(glm::vec3(
      shapes[0].mesh.positions[i],
      shapes[0].mesh.positions[i + 1],
      shapes[0].mesh.positions[i + 2]));
  }

  // texcoords

  m_texcoords.reserve(utils::align_up(shapes[0].mesh.texcoords.size() / 2));

  for (uint32 i = 0; i < shapes[0].mesh.texcoords.size(); i += 2)
  {
    m_texcoords.emplace_back(glm::vec2(
      shapes[0].mesh.texcoords[i],
      shapes[0].mesh.texcoords[i + 1]));
  }

  // normals

  m_normals.reserve(utils::align_up(shapes[0].mesh.normals.size() / 3));

  for (uint32 i = 0; i < shapes[0].mesh.normals.size(); i += 3)
  {
    m_normals.emplace_back(glm::vec3(
      shapes[0].mesh.normals[i],
      shapes[0].mesh.normals[i + 1],
      shapes[0].mesh.normals[i + 2]));
  }

  // m_indices

  m_indices.reserve(shapes[0].mesh.indices.size());

  for (uint32 i = 0; i < shapes[0].mesh.indices.size(); i++)
  {
    m_indices.emplace_back(shapes[0].mesh.indices[i]);
  }

  // m_materials

  auto fn_load_material_texture = [&](const std::string& file_name) -> std::unique_ptr<Tex2D>
  {
    auto image_file_path = file_dir + file_name;
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

  for (auto& material : materials)
  {
    m_materials.emplace_back(new Material);
    auto m = m_materials.back();

    m->material = material;

    try
    {
      m->tex2d_ambient  = fn_load_material_texture(material.ambient_texname);
      m->tex2d_diffuse  = fn_load_material_texture(material.diffuse_texname);
      m->tex2d_specular = fn_load_material_texture(material.specular_texname);
      m->tex2d_normal   = fn_load_material_texture(material.normal_texname);
    }
    catch (...)
    {
      // do nothing
    }
  }

  // Fatal error - one of the vectors is empty and it will cause problems with OpenGL buffers.
  // Program must be closed.

  if (m_positions.empty() || m_texcoords.empty() || m_normals.empty())
  {
    std::string info = "";

    if (m_positions.empty())
    {
      info.append("vertices");
    }

    if (m_texcoords.empty())
    {
      if (info.length() != 0)
      {
        info.append(", ");
      }

      info.append("uvs");
    }

    if (m_normals.empty())
    {
      if (info.length() != 0)
      {
        info.append(", ");
      }

      info.append("normals");
    }

    assert(0 && "no data in mesh from file");
  }

  m_ptr_vao->setup_begin();
  {
    // Note: The order depends on `assets\shader\lighting.[vs/fs]`
    m_ptr_vao->declare_position_format({ &m_positions[0], size_of(m_positions) }, 3, GL_FLOAT);
    m_ptr_vao->declare_normal_format({ &m_normals[0], size_of(m_normals) }, 3, GL_FLOAT);
    m_ptr_vao->declare_texcoord_format({ &m_texcoords[0], size_of(m_texcoords) }, 2, GL_FLOAT);
    m_ptr_vao->declare_index_format({ &m_indices[0], size_of(m_indices) }, 1, GL_UNSIGNED_SHORT);
  }
  m_ptr_vao->setup_end();

  m_ready = true;
}

void Mesh::render()
{
  if (!m_materials.empty())
  {
    glBindTexture(GL_TEXTURE_2D, 0);

    for (auto m : m_materials)
    {
      if (m->tex2d_diffuse)
      {
        m->tex2d_diffuse->use(true);
      }
    }
  }

  m_ptr_vao->render(GL_TRIANGLES);

  if (!m_materials.empty())
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}

}; // glwnd