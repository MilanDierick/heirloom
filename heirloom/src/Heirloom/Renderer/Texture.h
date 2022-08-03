// Author: Milan Dierick
// Solution: Heirloom

//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_TEXTURE_H
#define HEIRLOOM_TEXTURE_H

#include "Heirloom/Core/Core.h"
#include "glm/fwd.hpp"

namespace Heirloom
{
	class Texture
	{
	public:
		Texture()          = default;
		virtual ~Texture() = default;

		Texture(const Texture& other)                = delete;
		Texture(Texture&& other) noexcept            = delete;
		Texture& operator=(const Texture& other)     = delete;
		Texture& operator=(Texture&& other) noexcept = delete;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};
}

#endif //HEIRLOOM_TEXTURE_H
