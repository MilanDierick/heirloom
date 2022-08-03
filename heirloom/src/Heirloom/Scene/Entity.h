//
// Created by developer on 14/12/2021.
//

#ifndef HEIRLOOM_ENTITY_H
#define HEIRLOOM_ENTITY_H

#include "Heirloom/Core/Core.h"
#include "Heirloom/Scene/Scene.h"
#include "Scene.h"
#include "entt/entt.hpp"

namespace Heirloom
{
	class Entity
	{
	public:
		inline Entity() = default;
		inline Entity(entt::entity handle, Scene* scene);

		template < typename ...T >
		[[nodiscard]] constexpr bool HasComponent() const;

		template < typename T >
		T& AddComponent();

		template < typename T, typename ...Args >
		T& AddComponent(Args&& ...args);

		template < typename ...T >
		size_t RemoveComponent();

		template < typename ...T >
		[[nodiscard]] constexpr std::tuple<T& ...> GetComponent() const;

		inline operator bool() const;

	private:
		entt::entity m_EntityHandle;
		Scene* m_Scene;
	};

	inline Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene)
	{
	}

	template < typename... T >
	constexpr bool Entity::HasComponent() const
	{
		HL_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityHandle), "Tried accessing invalid entity.")

		return m_Scene->m_Registry.all_of<T...>(m_EntityHandle);
	}

	template < typename T >
	T& Entity::AddComponent()
	{
		HL_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityHandle), "Tried accessing invalid entity.")
		HL_CORE_ASSERT(!HasComponent<T>(), "Tried adding a component to an entity that already has this component.")

		return m_Scene->m_Registry.emplace<T>(m_EntityHandle);
	}

	template < typename T, typename ...Args >
	T& Entity::AddComponent(Args&& ...args)
	{
		HL_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityHandle), "Tried accessing invalid entity.")
		HL_CORE_ASSERT(!HasComponent<T>(), "Tried adding a component to an entity that already has this component.")

		return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
	}

	template < typename... T >
	size_t Entity::RemoveComponent()
	{
		HL_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityHandle), "Tried accessing invalid entity.")
		HL_CORE_ASSERT(HasComponent<T...>(), "Tried removing non-existent component(s). ")

		return m_Scene->m_Registry.remove<T...>(m_EntityHandle);
	}

	template < typename ...T >
	constexpr std::tuple<T& ...> Entity::GetComponent() const
	{
		HL_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityHandle), "Tried accessing invalid entity.")
		HL_CORE_ASSERT(HasComponent<T...>(), "Tried getting non-existent component. ")

		return m_Scene->m_Registry.get<T...>(m_EntityHandle);
	}

	inline Entity::operator bool() const
	{
		if (m_Scene == nullptr)
		{
			return false;
		}

		return m_Scene->m_Registry.valid(m_EntityHandle);
	}
}


#endif //HEIRLOOM_ENTITY_H
