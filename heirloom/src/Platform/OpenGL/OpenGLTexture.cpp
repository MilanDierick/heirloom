#include "hlpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace Heirloom
{
	OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height)
			: m_Width(width), m_Height(height)
	{
		HL_PROFILE_FUNCTION()

		m_InternalFormat = GL_RGBA8;
		m_DataFormat     = GL_RGBA;

		// Create the actual texture on the GPU
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		// Configure some parameters for the texture
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
			: m_Path(path), m_InternalFormat(0), m_DataFormat(0)
	{
		HL_PROFILE_FUNCTION()

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HL_CORE_ASSERT(data, "Failed to load image!");
		m_Width  = width;
		m_Height = height;

		if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat     = GL_RGBA;
		}
		else if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat     = GL_RGB;
		}

		HL_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		// Create the actual texture on the GPU
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		// Configure some parameters for the texture
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Upload the texture to the GPU
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		// Clean up our texture data
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		HL_PROFILE_FUNCTION()

		glDeleteTextures(1, &m_RendererID);
	}

	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	uint32_t OpenGLTexture2D::GetRendererID() const
	{
		return m_RendererID;
	}

	void OpenGLTexture2D::SetData(void* data, const uint32_t size)
	{
		HL_PROFILE_FUNCTION()

		const uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		HL_CORE_ASSERT(size == m_Width * m_Height * bpp,
				"Data must be the entire texture!"); // Size is not referenced here when we're not using asserts
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(const uint32_t slot)
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	bool OpenGLTexture2D::operator==(const Texture& other) const
	{
		return m_RendererID == reinterpret_cast<const OpenGLTexture2D&>(other).m_RendererID;
	}
}
