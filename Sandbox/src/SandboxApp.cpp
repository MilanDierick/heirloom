// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#include "Heirloom.h"
#include "Sandbox2D.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Heirloom/Core/EntryPoint.h"

class SandboxApplication final : public Heirloom::Application
{
public:
	SandboxApplication()
	{
		HL_PROFILE_FUNCTION()

		PushLayer(new Sandbox2D);
		HL_INFO("Initialized Sandbox application");
	}
};

Heirloom::Application* Heirloom::CreateApplication()
{
	HL_PROFILE_FUNCTION()

	return new SandboxApplication();
}
