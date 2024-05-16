#pragma once

#include "core/renderer/IndexBuffer.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/Texture.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/VertexBufferLayout.h"
#include "editor/camera/Camera.h"
#include "core/renderer/shapes/Shape.h"

#include "common/types/SmartPointers.h"
#include "utils/Error.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace Vivid
{
	class TypesOfTexture
	{
	public:
		enum class Type
		{
			DIFFUSE,
			NORMAL,
			SPECULAR,
			DISPLACEMENT
		};
	};
	class Mesh
	{
	private:
		bool m_IsEditing = false;
		static unsigned int s_ID;
		unsigned int m_ID;
		Vector<Vertex> m_Vertices;
		Vector<GLuint> m_Indices;
		VertexBufferLayout m_Layout;
		Vector<Ref<Texture>> m_Textures;
		Ref<VertexArray> m_Vao;
		IndexBuffer* m_Ebo;
		Ref<Shader> m_Shader;
		String m_VertexShaderPath;
		String m_PixelShaderPath;

		glm::mat4 m_ModelMatrix;
		float m_Shininess = 1;
		float m_AmbientStrength = 0.5f;
		float m_SpecularStrength = 0.5f;

		const unsigned int m_Instances;

		void loadOBJ(const std::string& file_name);
		void normalizeVertices();

	public:
		// Initializes the mesh
		Mesh();

		Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout, glm::mat4 modelMatrix, unsigned int instances = 1);

		Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, unsigned int instances = 1);

		explicit Mesh(Shape& shape, unsigned int instances = 1);

		explicit Mesh(const std::string& file_name, unsigned int instances = 1);

		explicit Mesh(const std::string& file_name, Ptr<Shader> shader, unsigned int instances = 1);

		void Update(const glm::mat4& modelMatrix);

		void BindShader(Ref<Shader> shader);

		Vector<Vertex> GetVertices() { return m_Vertices; }

		Vector<unsigned int> GetIndices() { return m_Indices; };

		glm::mat4 GetModelMatrix() { return m_ModelMatrix; };

		Shader& GetShader() { return *m_Shader.get(); };

		void SetVertices(Vector<Vertex> vertices);

		void SetIndices(Vector<unsigned int> indices);

		// Draws the mesh
		void Draw(Camera* camera);

		unsigned int GetID() { return m_ID; };

		void EditMesh();
		void ImGuiRender();

		void AddTexture(String file_name) { m_Textures.push_back(Ref<Texture>(new Texture(file_name))); }
		Ref<Texture> GetTexture(int index) { return m_Textures[index]; }

	private:
		void recompileShader();
	};
}
