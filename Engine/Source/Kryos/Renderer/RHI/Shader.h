#pragma once

#include "Kryos/Core/Defines.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Kryos
{

	enum ShaderType
	{
		ShaderType_Invalid	= -1,
		ShaderType_Fragment	= 0x8B30,
		ShaderType_Vertex	= 0x8B31,
		ShaderType_Geometry = 0x8DD9,
		ShaderType_Compute	= 0x91B9,
	};

	struct ShaderSource
	{
		ShaderType Type = ShaderType_Invalid;
		bool Compiled = false;
		std::string Source;

		ShaderSource(const std::string& glslVersion, const std::string_view& path, ShaderType type, bool compiled = false);
		static std::string_view TypeToString(ShaderType type);
	};

	class Shader
	{
	public:
		Shader() = default;
		Shader(const std::vector<ShaderSource>& sources);
		Shader(Shader&& shader);
		~Shader();

		Shader& operator=(Shader&& shader);

		inline uint32_t GetProgram() const { return m_Program; }

		void Destroy();
		void Bind();
		void Unbind();

		void Uniform(const std::string_view& location, uint32_t val);
		void Uniform(const std::string_view& location, const glm::ivec2& val);
		void Uniform(const std::string_view& location, const glm::ivec3& val);
		void Uniform(const std::string_view& location, const glm::ivec4& val);

		void Uniform(const std::string_view& location, float val);
		void Uniform(const std::string_view& location, const glm::vec2& val);
		void Uniform(const std::string_view& location, const glm::vec3& val);
		void Uniform(const std::string_view& location, const glm::vec4& val);

		void Uniform(const std::string_view& location, const glm::mat2& val);
		void Uniform(const std::string_view& location, const glm::mat3& val);
		void Uniform(const std::string_view& location, const glm::mat4& val);

	private:
		uint32_t m_Program = KY_INVALID32;

		Shader(const Shader& shader) = delete;
		Shader& operator=(const Shader& shader) = delete;
	};

}
