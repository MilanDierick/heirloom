//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_SHADER_H
#define HEIRLOOM_SHADER_H

#include "Heirloom/Core/Core.h"
#include "glm/glm.hpp"
#include "glm/gtx/compatibility.hpp"

namespace Heirloom
{
	class Shader
	{
	public:
		Shader()          = default;
		virtual ~Shader() = default;

		// Copy & move operations
		Shader(const Shader& other)                = delete;
		Shader(Shader&& other) noexcept            = delete;
		Shader& operator=(const Shader& other)     = delete;
		Shader& operator=(Shader&& other) noexcept = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, glm::float2 value) = 0;
		virtual void SetFloat3(const std::string& name, glm::float3 value) = 0;
		virtual void SetFloat4(const std::string& name, glm::float4 value) = 0;
		virtual void SetMat4(const std::string& name, glm::mat4 value) = 0;

		virtual const std::string& GetName() = 0;

		/**
		 * \brief Creates a new shader asset depending on the current graphics API being used from a file
		 * \param filePath File that contains the shader
		 * \return Returns a reference to the newly created
		 */
		static Ref<Shader> Create(const std::string& filePath);

		/**
		 * \brief Creates a new shader asset depending on the current graphics API being used
		 * \param name The name of the shader assets
		 * \param vertexSource A string containing the code of the vertex shader
		 * \param fragmentSource A string containing the code of the fragment shader
		 * \return Returns a reference to the newly created
		 */
		static Ref<Shader> Create(const std::string& name,
				const std::string& vertexSource,
				const std::string& fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		/**
		 * \brief Adds a pre-existing shader to the shader library with a custom name
		 * \param name The name of the shader asset
		 * \param shader A reference to a pre-existing shader
		 */
		void Add(const std::string& name, Ref<Shader> shader);

		/**
		 * \brief Adds a pre-existing shader to the shader library, where the name will be read from the filename
		 * \param shader A reference to a pre-existing shader
		 */
		void Add(Ref<Shader> shader);

		/**
		 * \brief Loads a new shader from a file and adds it to the shader library, where the name will be read from a filename
		 * \param filePath File that contains a shader
		 * \return Returns a reference to the newly added shader
		 */
		Ref<Shader> Load(const std::string& filePath);

		/**
		 * \brief Loads a new shader from a file and adds it to the shader library with a given name
		 * \param name The name of the shader asset
		 * \param filePath File that contains a shader
		 * \return Returns a reference to the newly added shader
		 */
		Ref<Shader> Load(const std::string& name, const std::string& filePath);

		/**
		 * \brief Gets a shader from the shader library with a given name
		 * \param name The name of the requested shader
		 * \return Returns a reference to the requested shader
		 */
		Ref<Shader> Get(const std::string& name);

		/**
		 * \brief Checks if a specific shader exists in the shader library
		 * \param name The name of the requested shader
		 * \return Returns a boolean indicating if the shader exists
		 */
		bool Exists(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}

#endif //HEIRLOOM_SHADER_H
