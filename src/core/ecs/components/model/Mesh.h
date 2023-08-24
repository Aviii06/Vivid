#pragma once

#include "core/renderer/IndexBuffer.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/Texture.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/VertexBufferLayout.h"
#include "editor/Camera.h"
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
	class Mesh
	{
	private:
		Vector<Vertex> m_Vertices;
		Vector<GLuint> m_Indices;
		VertexBufferLayout m_Layout;
		Ref<VertexArray> m_Vao;
		IndexBuffer* m_Ebo;
		Ref<Shader> m_Shader;

		glm::mat4 m_ModelMatrix;

		void loadOBJ(const std::string& file_name);

	public:
		// Initializes the mesh
		Mesh() = default;
		Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds, VertexBufferLayout layout, glm::mat4 modelMatrix);
		Mesh(Vector<Vertex>& verts, Vector<unsigned int>& inds);
		explicit Mesh(Shape& shape);
		explicit Mesh(const std::string& file_name);
		explicit Mesh(const std::string& file_name, Ptr<Shader> shader);

		void Update(const glm::mat4& modelMatrix);

		void BindShader(Ref<Shader> shader);

		Vector<Vertex> GetVertices() { return m_Vertices; }
		Vector<unsigned int> GetIndices() { return m_Indices; };
		glm::mat4 GetModelMatrix() { return m_ModelMatrix; };
		Shader& GetShader() { return *m_Shader.get(); };

		void SetVertices(Vector<Vertex> vertices);
		void SetIndices(Vector<unsigned int> indices);

		// Draws the mesh
		void Draw();
	};
}
