#pragma once

#include "common/types/SmartPointers.h"
#include "utils/Error.h"
#include "Renderer.h"
#include "core/ecs/components/model/Mesh.h"
#include "editor/camera/movable/EditorCamera.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	/*!
	 * @struct Storage
	 * @brief A struct that contains the data of the shapes.
	 * @details Storage is a struct that contains the VertexArray, the shaders, and the vertices and indices of the shapes.
	 */
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

	/*!
	 * @class Renderer2D
	 * @brief This class provides an interface to draw 2D shapes.
	 * @details This class provides an interface to draw 2D shapes like quads, lines, ellipses, and circles.
	 * All the functions are static, so you don't need to create an instance of this class to use it.
	 * It uses the @struct Storage to store the data of the shapes.
	 */
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
		/*!
		 * @brief Initializes the Renderer2D.
		 * @details Initializes the Renderer2D by creating the VertexArray, the shaders, and the vertices and indices of the shapes.
		 * @param reserveVertices The number of vertices to reserve.
		 */
		static void Init(int reserveVertices = 10000);
		/*!
		 * @brief Begins the scene.
		 * @details Begins the scene by binding the VertexArray and the shaders.
		 */
		static void BeginScene();
		/*!
		 * @brief Ends the scene.
		 * @details Ends the scene by unbinding the VertexArray and the shaders. This is where the actual draw call is made.
		 */
		static void EndScene();


		/*!
		 * @brief Draws a quad.
		 * @details Draws a quad with specified center-positon, size, and color.
		 * @param x The x-coordinate of the center of the quad.
		 * @param y The y-coordinate of the center of the quad.
		 * @param width The width of the quad.
		 * @param height The height of the quad.
		 * @param color The color of the quad.
		 */
		static void DrawQuad(float x, float y, float width, float height, const Maths::Vec3& color);

		/*!
		 * @brief Draws a quad.
		 * @details Draws a quad with the specified vertices and color. The order of the vertices is important. The quad is drawn in the order vertex1, vertex2, vertex3, vertex4.
		 * @param vertex1 The first vertex of the quad.
		 * @param vertex2 The second vertex of the quad.
		 * @param vertex3 The third vertex of the quad.
		 * @param vertex4 The fourth vertex of the quad.
		 * @param color The color of the quad.
		 */
		static void DrawQuad(const Maths::Vec2& vertex1, const Maths::Vec2& vertex2, const Maths::Vec2& vertex3,
		    const Maths::Vec2& vertex4, const Maths::Vec3& color);

		/*!
		 * @brief Draws a line.
		 * @details Draws a line with the specified vertices and color. The line is drawn using a line shader.
		 * Which is a essentially a small quad with anti aliasing, to make the line look smooth.
		 * @param start The first vertex of the line.
		 * @param end The second vertex of the line.
		 * @param thickness The thickness of the line.
		 * @param color The color of the line.
		 */
		static void DrawLine(Maths::Vec2 start, Maths::Vec2 end, float thickness, Maths::Vec3 color);

		/*!
		 * @brief Draws an ellipse.
		 * @details Draws an ellipse with the specified center, radiusX, radiusY, and color. This is also a quad and is draw using a shader that makes it look like an ellipse.
		 * @param center The center of the ellipse.
		 * @param radiusX The radius of the ellipse in the x-axis.
		 * @param radiusY The radius of the ellipse in the y-axis.
		 * @param color The color of the ellipse.
		 */
		static void DrawEllipse(Maths::Vec2 center, float radiusX, float radiusY, Maths::Vec3 color);

		/*!
		 * @brief Draws a circle.
		 * @details Draws a circle with the specified center, radius, and color. This is also a quad and is draw using a shader that makes it look like a circle.
		 * @param center The center of the circle.
		 * @param radius The radius of the circle.
		 * @param color The color of the circle.
		 */
		static void DrawCircle(Maths::Vec2 center, float radius, Maths::Vec3 color);
	};
}
