//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_SPRITE_H
#define HEIRLOOM_SPRITE_H

#include "Texture.h"
#include "glm/glm.hpp"

namespace Heirloom
{
	struct Sprite
	{
		[[nodiscard]] explicit Sprite(const glm::vec3& position     = glm::vec3(1.0f),
				const glm::vec2& size         = glm::vec2(1.0f),
				const float rotation          = 0.0f,
				const Ref<Texture2D>& texture = nullptr,
				const float tilingFactor      = 1.0f,
				const glm::vec4& tintColor    = glm::vec4(1.0f))
				: Position(position),
				  Size(size),
				  Rotation(rotation),
				  Texture(texture),
				  TilingFactor(tilingFactor),
				  TintColor(tintColor)
		{
		}

		glm::vec3 Position;
		glm::vec2 Size;
		float Rotation;
		Ref<Texture2D> Texture;
		float TilingFactor;
		glm::vec4 TintColor;
	};
}

#endif //HEIRLOOM_SPRITE_H
