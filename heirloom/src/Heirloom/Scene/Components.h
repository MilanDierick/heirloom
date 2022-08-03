//
// Created by developer on 11/12/2021.
//

#ifndef HEIRLOOM_COMPONENTS_H
#define HEIRLOOM_COMPONENTS_H

#include "glm/glm.hpp"

namespace Heirloom
{
	struct TransformComponent
	{
		TransformComponent() = default;
		~TransformComponent() = default;

		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(TransformComponent&& other) noexcept = default;
		TransformComponent& operator=(const TransformComponent& other) = default;
		TransformComponent& operator=(TransformComponent&& other) noexcept = default;

		explicit TransformComponent(const glm::mat4& transform) : Transform(transform)
		{
		}

		glm::mat4 Transform{ 1.0F };
	};

	struct SpriteRendererComponent
	{
		SpriteRendererComponent() = default;
		~SpriteRendererComponent() = default;

		SpriteRendererComponent(const SpriteRendererComponent& other) = default;
		SpriteRendererComponent(SpriteRendererComponent&& other) noexcept = default;
		SpriteRendererComponent& operator=(const SpriteRendererComponent& other) = default;
		SpriteRendererComponent& operator=(SpriteRendererComponent&& other) noexcept = default;

		explicit SpriteRendererComponent(const glm::vec4& color) : Color(color)
		{
		}

		glm::vec4 Color{ 1.0F };
	};

	struct TagComponent
	{
		TagComponent() = default;
		~TagComponent() = default;

		TagComponent(const TagComponent& other) = default;
		TagComponent(TagComponent&& other) noexcept = default;
		TagComponent& operator=(const TagComponent& other) = default;
		TagComponent& operator=(TagComponent&& other) noexcept = default;

		explicit TagComponent(const std::string& tag) : Tag(tag)
		{
		}

		std::string Tag{};
	};
}

#endif //HEIRLOOM_COMPONENTS_H
