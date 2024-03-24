#include "Renderer.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	struct Storage3D
	{
		Ref<VertexArray> vao;
		Ref<Shader> quadShader;
		Vector<Vertex> quadVertices;
		Vector<unsigned int> quadIndices;
		Ref<Shader> triangleShader;
		Vector<Vertex> triangleVertices;
		Vector<unsigned int> triangleIndices;
	};

	class Renderer3D
	{
	private:
		static Storage3D s_Storage3D;

	public:
		Renderer3D() = default;

		~Renderer3D() = default;

		static void Init();

		static void BeginScene();

		static void EndScene();

		static void DrawQuad(Maths::Vec3 vertex1, Maths::Vec3 vertex2, Maths::Vec3 vertex3, Maths::Vec3 vertex4, Maths::Vec3 color);

		static void DrawTriangle(Maths::Vec3 vertex1, Maths::Vec3 vertex2, Maths::Vec3 vertex3, Maths::Vec3 color);

		static void DrawCube(Maths::Vec3 center, float edgeLength, Maths::Vec3 color);
	};

}
