#pragma once

#include "common/types/SmartPointers.h"
#include "utils/Error.h"
#include "Renderer.h"
#include "core/ecs/components/model/Mesh.h"
#include "editor/camera/movable/EditorCamera.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	struct Storage
	{
		Ref<VertexArray> vao;
		Ref<Shader> quadShader;
		Ref<Shader> lineShader;
		Ref<Shader> ellipseShader;
		Vector<Vertex> quadVertices;
		Vector<unsigned int> quadIndices;
		Vector<Vertex> ellipseVertices;
		Vector<unsigned int> ellipseIndices;
		Vector<Vertex> lineVertices;
		Vector<unsigned int> lineIndices;
	};

	class Renderer2D
	{
	private:
		static Storage s_Storage;

		Renderer2D() = default;

		~Renderer2D() = default;

		static void drawQuad(Maths::Vec2 vertex1, Maths::Vec2 vertex2, Maths::Vec2 vertex3, Maths::Vec2 vertex4, Maths::Vec3 color);

		static void drawQuad(float x, float y, float width, float height, const Maths::Vec3& color);

		static void drawEllipse(Maths::Vec2 center, float radiusX, float radiusY, Maths::Vec3 color);

		static void drawLine(Maths::Vec2 vertex1, Maths::Vec2 vertex2, Maths::Vec2 vertex3, Maths::Vec2 vertex4, Maths::Vec3 color);

	public:
		static void Init(int reserveVertices = 10000);

		static void Shutdown();

		static void BeginScene();

		static void EndScene();

		static void DrawQuad(float x, float y, float width, float height, const Maths::Vec3& color);

		static void DrawQuad(const Maths::Vec2& vertex1, const Maths::Vec2& vertex2, const Maths::Vec2& vertex3,
		    const Maths::Vec2& vertex4, const Maths::Vec3& color);

		static void DrawLine(Maths::Vec2 start, Maths::Vec2 end, float thickness, Maths::Vec3 color);

		static void DrawEllipse(Maths::Vec2 center, float radiusX, float radiusY, Maths::Vec3 color);

		static void DrawCircle(Maths::Vec2 center, float radius, Maths::Vec3 color);
	};
}
