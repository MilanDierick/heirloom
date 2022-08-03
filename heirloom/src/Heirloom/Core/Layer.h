// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_LAYER_H
#define HEIRLOOM_LAYER_H

#include <string>
#include <vector>
#include "Heirloom/Core/Timestep.h"
//#include "Heirloom/Gameplay/GameObject.h"

namespace Heirloom
{
	class Layer
	{
	public:
		explicit Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		Layer(const Layer& other)                = delete;
		Layer(Layer&& other) noexcept            = delete;
		Layer& operator=(const Layer& other)     = delete;
		Layer& operator=(Layer&& other) noexcept = delete;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnRender() = 0;
		virtual void OnImGuiRender() = 0;

		const std::string& GetName() const;

	protected:
		std::string m_DebugName;
//		std::vector<GameObject> m_GameObjects; // TODO: Add GameObjects
	};
}


#endif //HEIRLOOM_LAYER_H
