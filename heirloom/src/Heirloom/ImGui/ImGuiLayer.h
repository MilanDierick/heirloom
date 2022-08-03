// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_IMGUILAYER_H
#define HEIRLOOM_IMGUILAYER_H

#include "Heirloom/Core/Layer.h"

namespace Heirloom
{
	class ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		ImGuiLayer(const ImGuiLayer& other)                = delete;
		ImGuiLayer(ImGuiLayer&& other) noexcept            = delete;
		ImGuiLayer& operator=(const ImGuiLayer& other)     = delete;
		ImGuiLayer& operator=(ImGuiLayer&& other) noexcept = delete;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep) override;
		void OnRender() override;

		void OnImGuiRender() override;

		void Begin();
		void End();
	};
}

#endif //HEIRLOOM_IMGUILAYER_H
