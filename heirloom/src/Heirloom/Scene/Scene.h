//
// Created by developer on 11/12/2021.
//

#ifndef HEIRLOOM_SCENE_H
#define HEIRLOOM_SCENE_H

#include "Heirloom/Core/Core.h"
#include "Heirloom/Core/Timestep.h"
#include "Heirloom/Scene/Components.h"
#include "entt/entt.hpp"

namespace Heirloom
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) noexcept = default;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) noexcept = default;

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}


#endif //HEIRLOOM_SCENE_H
