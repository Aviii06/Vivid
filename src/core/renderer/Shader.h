#pragma once

#include "glm/glm.hpp"
#include "VertexBuffer.h"
#include "common/maths/Vec.h"
#include <string>
#include <unordered_map>

namespace Vivid
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string PixelSource;
	};

	// Shader should contain all the uniforms that are required by it to run.
	// We can bind those uniforms to the shader and then use them automatically. Or we can have them Statically Bind them, which doesn;t put them into the shader's object. Just binds them for some time.
	class Shader
	{
	private:
		std::string m_FilePathVS;
		std::string m_FilePathPS;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		Shader(const String& filepathVertexShader, const String& filepathPixelShader);

		~Shader();

		static Ref<Shader> Create(const std::string& filepathVertexShader, const std::string& filepathPixelShader);

		void Bind() const;

		void Unbind() const;

		// Set uniforms
		void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

		void SetUniform4f(const std::string& name, const glm::vec4& matrix);

		void SetUniform3f(const std::string& name, float f0, float f1, float f2);

		void SetUniform3f(const std::string& name, Maths::Vec3& value);

		void SetUniform1f(const std::string& name, float value);

		void SetUniform1i(const std::string& name, int value);

		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

		String GetVertexShaderPath() { return m_FilePathVS; }
		String GetPixelShaderPath() { return m_FilePathPS; }

		unsigned int GetRendererID() { return m_RendererID; }

	private:
		int GetUniformLocation(const std::string& name);

		struct ShaderProgramSource
		ParseShader(const std::string& filepathVertexShader, const std::string& filepathPixelShader);

		unsigned int CompileShader(unsigned int type, const std::string& source);

		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	};
}