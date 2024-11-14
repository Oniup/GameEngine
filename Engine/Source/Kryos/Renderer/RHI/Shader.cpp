#include "Kryos/Renderer/RHI/Shader.h"
#include "Kryos/Core/Log.h"
#include <glad/glad.h>
#include <cstdio>

namespace Kryos
{

	ShaderSource::ShaderSource(const std::string& glslVersion, const std::string_view& path, ShaderType type, bool compiled)
	{
		std::FILE* file = std::fopen(path.data(), "rb");
		if (!file)
		{
			KY_ERROR("Shader source path '{}' doesn't exist", path);
			return;
		}

		std::fseek(file, 0, SEEK_END);
		Source.resize(std::ftell(file) + glslVersion.size());
		std::fseek(file, 0, SEEK_SET);

		std::strncpy(Source.data(), glslVersion.data(), glslVersion.size());
		Source[glslVersion.size()] = '\n';
		std::fread(Source.data() + glslVersion.size() + 1, 1, Source.size(), file);
		Source[Source.size()] = '\0';

		std::fclose(file);
		Type = type;
		Compiled = compiled;
	}

	std::string_view ShaderSource::TypeToString(ShaderType type)
	{
		switch (type)
		{
		case ShaderType_Fragment:	return "Fragment";
		case ShaderType_Vertex:		return "Vertex";
		case ShaderType_Geometry:	return "Geometry";
		case ShaderType_Compute:	return "Compute";
		default:					return "Invalid";
		}
	}

	Shader::Shader(const std::vector<ShaderSource>& sources)
	{
		constexpr size_t errorMessageLength = 512;
		std::vector<uint32_t> shaders;
		shaders.reserve(sources.size());

		auto pfnDestroyShaders = [&shaders]()
		{
			for (uint32_t shader : shaders)
				glDeleteShader(shader);
		};

		for (const ShaderSource& source : sources)
		{
			shaders.push_back(glCreateShader(static_cast<int>(source.Type)));
			uint32_t shader = shaders.back();

			if (!source.Compiled)
			{
				const char* src = source.Source.data();
				glShaderSource(shader, 1, &src, nullptr);
				glCompileShader(shader);

				int result;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
				if (!result)
				{
					char errorMessage[errorMessageLength];
					glGetShaderInfoLog(shader, errorMessageLength, nullptr, errorMessage);
					KY_ERROR("Failed to compile {} shader: {}", ShaderSource::TypeToString(source.Type), errorMessage);
					pfnDestroyShaders();
					return;
				}
			}
			else
			{
				// TODO: ...
				KY_ERROR("Created shader from a compiled shader is not supported yet...");
				pfnDestroyShaders();
				return;
			}
		}

		m_Program = glCreateProgram();
		for (uint32_t shader : shaders)
			glAttachShader(m_Program, shader);
		glLinkProgram(m_Program);

		int result;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &result);
		if (!result)
		{
			char errorMessage[errorMessageLength];
			glGetProgramInfoLog(m_Program, errorMessageLength, nullptr, errorMessage);
			KY_ERROR("Failed to link shader programs: {}", errorMessage);
			m_Program = KY_INVALID32;
		}

		pfnDestroyShaders();
	}

	Shader::Shader(Shader&& shader)
		: m_Program(shader.m_Program)
	{
		shader.m_Program = KY_INVALID32;
	}

	Shader::~Shader()
	{
		Destroy();
	}

	Shader& Shader::operator=(Shader&& shader)
	{
		Destroy();
		m_Program = shader.m_Program;
		shader.m_Program = KY_INVALID32;
		return *this;
	}

	void Shader::Destroy()
	{
		if (m_Program != KY_INVALID32)
		{
			glDeleteProgram(m_Program);
			m_Program = KY_INVALID32;
		}
	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::Uniform(const std::string_view& location, uint32_t val)
	{
		glUniform1i(glGetUniformLocation(m_Program, location.data()), val);
	}

	void Shader::Uniform(const std::string_view& location, const glm::ivec2& val)
	{
		glUniform2i(glGetUniformLocation(m_Program, location.data()), val.x, val.y);
	}

	void Shader::Uniform(const std::string_view& location, const glm::ivec3& val)
	{
		glUniform3i(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.y);
	}

	void Shader::Uniform(const std::string_view& location, const glm::ivec4& val)
	{
		glUniform4i(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.y, val.w);
	}

	void Shader::Uniform(const std::string_view& location, float val)
	{
		glUniform1f(glGetUniformLocation(m_Program, location.data()), val);
	}

	void Shader::Uniform(const std::string_view& location, const glm::vec2& val)
	{
		glUniform2f(glGetUniformLocation(m_Program, location.data()), val.x, val.y);
	}

	void Shader::Uniform(const std::string_view& location, const glm::vec3& val)
	{
		glUniform3f(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.y);
	}

	void Shader::Uniform(const std::string_view& location, const glm::vec4& val)
	{
		glUniform4f(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.y, val.w);
	}

	void Shader::Uniform(const std::string_view& location, const glm::mat2& val)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_Program, location.data()), 1, GL_FALSE, &val[0][0]);
	}

	void Shader::Uniform(const std::string_view& location, const glm::mat3& val)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_Program, location.data()), 1, GL_FALSE, &val[0][0]);
	}

	void Shader::Uniform(const std::string_view& location, const glm::mat4& val)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Program, location.data()), 1, GL_FALSE, &val[0][0]);
	}

}
