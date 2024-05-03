#include "Mesh.h"
#include "common/maths/Vec.h"
#include "imgui.h"
#include "editor/assets/Assets.h"
#include "core/os/FileDialogue.h"

namespace Vivid
{
	unsigned int Mesh::s_ID = 0;
	Mesh::Mesh()
	    : m_Instances(1)
	{
		m_ID = s_ID;
		s_ID++;
	}

	Mesh::Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout, glm::mat4 modelMatrix, unsigned int instances)
	    : m_Instances(instances)
	{
		m_ID = s_ID;
		s_ID++;

		m_Vertices = verts;
		m_Indices = inds;
		m_Layout = layout;
		m_ModelMatrix = modelMatrix;

		m_Ebo = new IndexBuffer(m_Indices);
		m_Vao = VertexArray::Create();

		normalizeVertices();
	}

	Mesh::Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, unsigned int instances)
	    : m_Instances(instances)
	{
		m_ID = s_ID;
		s_ID++;

		m_Vertices = verts;
		m_Indices = inds;

		m_Layout.AddFloat(3); // Position
		m_Layout.AddFloat(2); // Texcoord
		m_Layout.AddFloat(3); // Color
		m_Layout.AddFloat(3); // Normal

		m_ModelMatrix = glm::mat4(1.0f);

		m_Ebo = new IndexBuffer(m_Indices);
		m_Vao = VertexArray::Create();

		normalizeVertices();
	}

	Mesh::Mesh(const std::string& file_name, unsigned int instances)
	    : m_Instances(instances)
	{
		m_ID = s_ID;
		s_ID++;

		loadOBJ(file_name);
	}

	Mesh::Mesh(const std::string& file_name, Ptr<Shader> shader, unsigned int instances)
	    : m_Instances(instances)
	{
		m_ID = s_ID;
		s_ID++;

		BindShader(std::move(shader));
		loadOBJ(file_name);
	}

	Mesh::Mesh(Shape& shape, unsigned int instances)
	    : m_Instances(instances)
	{
		m_ID = s_ID;
		s_ID++;

		m_Vertices = shape.GetPositions();
		m_Indices = shape.GetIndices();
		m_Layout.AddFloat(3); // Position
		m_Layout.AddFloat(2); // Texcoord
		m_Layout.AddFloat(3); // Color
		m_Layout.AddFloat(3); // Normal

		m_Ebo = new IndexBuffer(m_Indices);
		m_Vao = VertexArray::Create();

		normalizeVertices();
	}

	void Mesh::Update(const glm::mat4& modelMatrix)
	{
		m_ModelMatrix = modelMatrix;
	}

	void Mesh::BindShader(Ref<Shader> shader)
	{
		m_Shader = shader;
		m_VertexShaderPath = shader->GetVertexShaderPath();
		m_PixelShaderPath = shader->GetPixelShaderPath();
		m_Shader->Bind();
	}

	void Mesh::loadOBJ(const std::string& file_name)
	{
		// Default Layout is of type Vertex
		m_Layout.AddFloat(3); // Positions
		m_Layout.AddFloat(2); // Tex coords
		m_Layout.AddFloat(3); // Colors
		m_Layout.AddFloat(3); // Normal

		// Vertex portions
		Vector<Maths::Vec3> vertex_positions;
		Vector<Maths::Vec2> vertex_texcoords;
		Vector<Maths::Vec3> vertex_normals;

		// Face vectors
		std::vector<GLint> vertex_position_indicies;
		std::vector<GLint> vertex_texcoord_indicies;
		std::vector<GLint> vertex_normal_indicies;

		std::stringstream ss;
		std::ifstream in_file(file_name.c_str());
		std::string line = "";
		std::string prefix = "";
		Maths::Vec3 temp_vec3;
		Maths::Vec2 temp_vec2;
		GLint temp_glint = 0;

		// File open error check
		if (!in_file.is_open())
		{
			throw "ERROR::OBJLOADER::Could not open file.";
		}

		// Read one line at a time
		while (std::getline(in_file, line))
		{
			// Get the prefix of the line
			ss.clear();
			ss.str(line);
			ss >> prefix;

			// Vertex position
			if (prefix == "v")
			{
				ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				vertex_positions.push_back(temp_vec3);
			}
			// Vertex texture
			else if (prefix == "vt")
			{
				ss >> temp_vec2.x >> temp_vec2.y;
				vertex_texcoords.push_back(temp_vec2);
			}
			// Vertex normal
			else if (prefix == "vn")
			{
				ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				vertex_normals.push_back(temp_vec3);
			}
			// Face
			else if (prefix == "f")
			{
				int counter = 0;
				while (ss >> temp_glint)
				{
					// Pushing indices into correct arrays
					if (counter == 0)
						vertex_position_indicies.push_back(temp_glint);
					else if (counter == 1)
						vertex_texcoord_indicies.push_back(temp_glint);
					else if (counter == 2)
						vertex_normal_indicies.push_back(temp_glint);

					// Handling characters
					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						counter = 0;
						ss.ignore(1, ' ');
					}

					// Reset the counter
					if (counter > 2)
					{
						counter = 0;
					}
				}
			}
		}

		m_Vertices.resize(vertex_position_indicies.size(), Vertex());
		vertex_texcoord_indicies.resize(vertex_position_indicies.size(), GLint(0));
		vertex_normal_indicies.resize(vertex_position_indicies.size(), GLint(0));
		m_Indices.resize(vertex_position_indicies.size(), GLint(0));

		// TODO: Optimize this
		for (size_t i = 0; i < m_Vertices.size(); ++i)
		{
			if (vertex_texcoord_indicies[i] == 0)
			{
				m_Vertices[i].texcoord = Maths::Vec2(1.0, 0.0);
			}
			else
			{
				m_Vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
			}

			if (vertex_normal_indicies[i] == 0)
			{
				m_Vertices[i].normal = Maths::Vec3(1.0, 0.0, 0.0);
			}
			else
			{
				m_Vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
			}
			m_Vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
			m_Vertices[i].color = Maths::Vec3(0.0f, 0.0f, 1.0f);
			m_Indices[i] = i;
		}

		m_Ebo = new IndexBuffer(m_Indices);
		m_Vao = VertexArray::Create();
		// Loaded success
		std::cout << "OBJ file loaded!"
		          << "\n";

		normalizeVertices();
	}

	void Mesh::SetVertices(Vector<Vertex> vertices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			m_Vertices[i] = vertices[i];
		}

		normalizeVertices();
	}

	void Mesh::SetIndices(Vector<unsigned int> indices)
	{
		for (int i = 0; i < indices.size(); i++)
		{
			m_Indices[i] = indices[i];
		}
	}

	void Mesh::recompileShader()
	{
		m_Shader = Shader::Create(m_VertexShaderPath, m_PixelShaderPath);
		m_Shader->Bind();
	}

	void Mesh::Draw(Camera* camera)
	{
		if (m_Shader == nullptr)
		{
			std::cout << "Shader is not bound to the mesh!" << std::endl;
			return;
		}
		m_Shader->Bind();

		VertexBuffer vbo(m_Vertices);
		vbo.Bind(m_Vertices);

		m_Vao->AddVertexBuffer(vbo, m_Layout, m_Vertices);
		m_Vao->AddIndexBuffer(*m_Ebo);

		m_Shader->SetUniformMat4f("u_Model", m_ModelMatrix);
		m_Shader->SetUniformMat4f("u_View", camera->GetViewMatrix());
		m_Shader->SetUniformMat4f("u_Proj", camera->GetProjectionMatrix());

		// Bind Texture
		if (m_Texture != nullptr)
		{
			m_Texture->Bind(0);
			m_Shader->SetUniform1i("texture", 0);
		}

		Vivid::Renderer::Draw(m_Vao, m_Ebo->GetCount(), m_Instances);
	}

	void Mesh::normalizeVertices()
	{
		float maxMag = 0;
		for (int i = 0; i < m_Vertices.size(); i++)
		{
			float mag = sqrt(m_Vertices[i].position.x * m_Vertices[i].position.x + m_Vertices[i].position.y * m_Vertices[i].position.y + m_Vertices[i].position.z * m_Vertices[i].position.z);
			maxMag = std::max(mag, maxMag);
		}

		for (int i = 0; i < m_Vertices.size(); i++)
		{
			m_Vertices[i].position = m_Vertices[i].position * (1 / maxMag);
		}
	}

	void Mesh::EditMesh()
	{
		m_IsEditing = true;
	}

	void Mesh::ImGuiRender()
	{
		if (m_IsEditing)
		{
			ImGui::Begin("Mesh Editor");
			ImGui::PushID("MeshEditor" + m_ID);
			if (ImGui::Button("Close Mesh Editor"))
			{
				m_IsEditing = false;
			}
			ImGui::Text("Mesh ID: %d", m_ID);
			ImGui::Text("Vertices: %d", m_Vertices.size());
			ImGui::Text("Indices: %d", m_Indices.size());
			ImGui::Text("Instances: %d", m_Instances);
			ImGui::SeparatorText("Model Matirx");
			ImGui::InputFloat4("##ModelMatrix1", &m_ModelMatrix[0][0]);
			ImGui::InputFloat4("##ModelMatrix2", &m_ModelMatrix[1][0]);
			ImGui::InputFloat4("##ModelMatrix3", &m_ModelMatrix[2][0]);
			ImGui::InputFloat4("##ModelMatrix4", &m_ModelMatrix[3][0]);

			ImGui::SeparatorText("Shader");
			ImGui::Text("Vertex Shader");
			if (!m_VertexShaderPath.empty())
			{
				ImGui::Text(m_VertexShaderPath.c_str());
			}
			else
			{
				ImGui::Text("No Vertex Shader");
			}
			ImGui::SameLine();
			ImGui::PushID("VertexShader");
			unsigned int texId = VividGui::Assets::GetInstance()->GetTexOpen()->GetRendererID();
			if (ImGui::ImageButton((ImTextureID)texId,
			        ImVec2(VividGui::Assets::GetInstance()->GetButtonWidth(), VividGui::Assets::GetInstance()->GetButtonWidth()),
			        ImVec2(0.0, 0.0), ImVec2(1.0, 1.0), 2))
			{
				std::string file = FileDialogue::OpenFile({}, {});
				if (!file.empty())
				{
					m_VertexShaderPath = file;
				}
			}
			ImGui::PopID();

			ImGui::Text("Pixel Shader");
			if (!m_PixelShaderPath.empty())
			{
				ImGui::Text(m_PixelShaderPath.c_str());
			}
			else
			{
				ImGui::Text("No Pixel Shader");
			}
			ImGui::SameLine();
			ImGui::PushID("PixelShader");
			if (ImGui::ImageButton((ImTextureID)texId,
			        ImVec2(VividGui::Assets::GetInstance()->GetButtonWidth(), VividGui::Assets::GetInstance()->GetButtonWidth()),
			        ImVec2(0.0, 0.0), ImVec2(1.0, 1.0), 2))
			{
				std::string file = FileDialogue::OpenFile({}, {});
				if (!file.empty())
				{
					m_PixelShaderPath = file;
				}
			}
			ImGui::PopID();

			if (ImGui::Button("Compile Shader"))
			{
				if (!m_VertexShaderPath.empty() && !m_PixelShaderPath.empty())
				{
					recompileShader();
				}
			}
			ImGui::PopID();

			// TODO: Add a Texture editing feature here.
			ImGui::End();
		}
	}
}
