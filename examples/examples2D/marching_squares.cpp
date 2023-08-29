#include "Vivid.h"

#include <thread>

#include <math.h>

int g_Dim;
float g_DimPerlin;
bool g_RenderQuad;
double Time;

float g_Thickness = 0.8f;
float* g_Color = new float[3] { 0.0f, 0.0f, 0.0f };

Vector<Vector<double>> val1, val2, val3, val4;

int a[256] = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
	140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148,
	247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
	57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
	74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
	60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
	65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
	200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64,
	52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212,
	207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213,
	119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
	129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104,
	218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
	81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157,
	184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
	222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 };

int p[512];

double fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double t, double a, double b)
{
	return a + t * (b - a);
}

double grad(int hash, double x, double y, double z)
{
	int h = hash & 15;
	double u = h < 8 ? x : y,
	       v = h < 4 ? y : h == 12 || h == 14 ? x
	                                          : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void noise(double x, double y, double z, double& value)
{
	int X = (int)floor(x) & 255,
	    Y = (int)floor(y) & 255,
	    Z = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	double u = fade(x),
	       v = fade(y),
	       w = fade(z);
	int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
	    B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	double val = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)), lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
	    lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
	        lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
	            grad(p[BB + 1], x - 1, y - 1, z - 1))));
	value = val * 0.5 + 0.5;
}

void GetNoiseVec(int x, int y, double time, Vector<Vector<double>>& vec)
{
	for (int i = -1000 / g_Dim; i <= 1000 / g_Dim; i++)
	{
		Vector<double> temp;
		temp.reserve(1000 / g_Dim * 2 + 1);
		for (int j = -1000 / g_Dim; j <= 1000 / g_Dim; j++)
		{
			double v;
			noise((i + x) * g_DimPerlin, (j + y) * g_DimPerlin, time, std::ref(v));
			//			temp.push_back(std::move(v));
			temp.push_back(std::move(v));
		}
		//		vec.emplace_back(std::move(temp));
		vec.emplace_back(std::move(temp));
	}
}

int GetState(const double& a, const double& b, const double& c, const double& d)
{
	int a1 = std::round(a);
	int b1 = std::round(b);
	int c1 = std::round(c);
	int d1 = std::round(d);

	return a1 * 8 + b1 * 4 + c1 * 2 + d1 * 1;
}

class ExampleInterface : public RenderingInterface
{
private:
public:
	void Setup() override
	{
		OPENGL_2D_CONFS

		for (int i = 0; i < 256; i++)
		{
			p[i] = a[i];
			p[256 + i] = a[i];
		}

		g_Dim = 2;
		g_DimPerlin = g_Dim * 0.020735;

		Time = 0;

		val1.reserve((1000 / g_Dim * 1000 / g_Dim) + 1000);
		val2.reserve((1000 / g_Dim * 1000 / g_Dim) + 1000);
		val3.reserve((1000 / g_Dim * 1000 / g_Dim) + 1000);
		val4.reserve((1000 / g_Dim * 1000 / g_Dim) + 1000);

		Vivid::Renderer2D::Init();
	}

	void Draw() override
	{
		Vivid::Renderer2D::BeginScene();

		//		GetNoiseVec(0, 0, Time, std::ref(val1));
		//		GetNoiseVec(1, 0, Time, std::ref(val2));
		//		GetNoiseVec(1, 1, Time, std::ref(val3));
		//		GetNoiseVec(0, 1, Time, std::ref(val4));

		std::thread t1(GetNoiseVec, 0, 0, Time, std::ref(val1));
		std::thread t2(GetNoiseVec, 1, 0, Time, std::ref(val2));
		std::thread t3(GetNoiseVec, 1, 1, Time, std::ref(val3));
		std::thread t4(GetNoiseVec, 0, 1, Time, std::ref(val4));

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		for (int i = -1000 / g_Dim; i <= 1000 / g_Dim; i++)
		{
			for (int j = -1000 / g_Dim; j <= 1000 / g_Dim; j++)
			{
				double v1, v2, v3, v4;
				v1 = val1[i + 1000 / g_Dim][j + 1000 / g_Dim];
				v2 = val2[i + 1000 / g_Dim][j + 1000 / g_Dim];
				v3 = val3[i + 1000 / g_Dim][j + 1000 / g_Dim];
				v4 = val4[i + 1000 / g_Dim][j + 1000 / g_Dim];

				int x = i * g_Dim;
				int y = j * g_Dim;

				Vec2 x1 = Vec2(x, y);
				Vec2 x2 = Vec2(x + g_Dim, y);
				Vec2 x3 = Vec2(x + g_Dim, y + g_Dim);
				Vec2 x4 = Vec2(x, y + g_Dim);

				if (g_RenderQuad)
				{
					Vivid::Renderer2D::DrawQuad(x1.x, x1.y, g_Dim, g_Dim, Vec3(v1, v1, v1));
				}

				Vec2 a = x1 + (x2 - x1) * (float)(v1 / (v1 + v2));
				Vec2 b = x2 + (x3 - x2) * (float)(v2 / (v2 + v3));
				Vec2 c = x3 + (x4 - x3) * (float)(v3 / (v3 + v4));
				Vec2 d = x4 + (x1 - x4) * (float)(v4 / (v4 + v1));

				Vec3 col = Vec3(g_Color[0], g_Color[1], g_Color[2]);
				float thickness = g_Thickness;
				switch (GetState(v1, v2, v3, v4))
				{
				case 1:
					Vivid::Renderer2D::DrawLine(c, d, thickness, col);
					break;
				case 2:
					Vivid::Renderer2D::DrawLine(b, c, thickness, col);
					break;
				case 3:
					Vivid::Renderer2D::DrawLine(b, d, thickness, col);
					break;
				case 4:
					Vivid::Renderer2D::DrawLine(a, b, thickness, col);
					break;
				case 5:
					Vivid::Renderer2D::DrawLine(a, d, thickness, col);
					Vivid::Renderer2D::DrawLine(b, c, thickness, col);
					break;
				case 6:
					Vivid::Renderer2D::DrawLine(a, c, thickness, col);
					break;
				case 7:
					Vivid::Renderer2D::DrawLine(a, d, thickness, col);
					break;
				case 8:
					Vivid::Renderer2D::DrawLine(d, a, thickness, col);
					break;
				case 9:
					Vivid::Renderer2D::DrawLine(c, a, thickness, col);
					break;
				case 10:
					Vivid::Renderer2D::DrawLine(a, b, thickness, col);
					Vivid::Renderer2D::DrawLine(c, d, thickness, col);
					break;
				case 11:
					Vivid::Renderer2D::DrawLine(a, b, thickness, col);
					break;
				case 12:
					Vivid::Renderer2D::DrawLine(b, d, thickness, col);
					break;
				case 13:
					Vivid::Renderer2D::DrawLine(b, c, thickness, col);
					break;
				case 14:
					Vivid::Renderer2D::DrawLine(d, c, thickness, col);
					break;
				}
			}
		}

		Time += 0.025;

		val1.clear();
		val2.clear();
		val3.clear();
		val4.clear();
		Vivid::Renderer2D::EndScene();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Settings");
		//	ImGui::SliderFloat3("Translation Model 1", &suzannePosition.x, -500.0f, 500.0f);
		//	// ImGui::SliderFloat3("Translation Model 2", &lightPosition.x, -300.0f, 300.0f);
		//	ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::SliderFloat("Thickness", &g_Thickness, 0.0f, 10.0f);
		ImGui::SliderInt("Dimension", &g_Dim, 2.0f, 10.0f);
		ImGui::SliderFloat("Perlin Dimension", &g_DimPerlin, 0.0f, 1.0f);
		ImGui::Checkbox("RenderQuad", &g_RenderQuad);
		ImGui::ColorPicker3("Color", g_Color);
		ImGui::End();
	}
};

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Marching Squares");

	OrthoCamera* orthoCamera = new OrthoCamera(0, 1920, 0, 1080);
	app->SetCamera(orthoCamera);
	app->SetRenderingInterface(new ExampleInterface);
	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}