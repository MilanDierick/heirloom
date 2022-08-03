//
// Created by developer on 11/12/2021.
//

#include "Scene.h"
#include "Heirloom/Renderer/Renderer2D.h"
#include "Heirloom/Scene/Entity.h"

namespace Heirloom
{
	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity: group)
		{
			auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform.Transform, sprite.Color);
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };

		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();

		name.empty() ? tag.Tag = "Entity" : tag.Tag = name;

		return entity;
	}
}