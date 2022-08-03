// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_ENTRYPOINT_H
#define HEIRLOOM_ENTRYPOINT_H

#include "hlpch.h"

int main()
{
	Heirloom::Log::Init();
	HL_CORE_INFO("Starting application...");

	HL_PROFILE_BEGIN_SESSION("Initialization", "HeirloomProfiling-Initialization.json");
	Heirloom::Application* app = Heirloom::CreateApplication();
	HL_PROFILE_END_SESSION();

	try
	{
		HL_PROFILE_BEGIN_SESSION("Runtime", "HeirloomProfiling-Runtime.json");
		app->Run();
		HL_PROFILE_END_SESSION();
	}
	catch (std::exception& exception)
	{
		HL_CORE_FATAL(exception.what());
	}

	HL_PROFILE_BEGIN_SESSION("Termination", "HeirloomProfiling-Termination.json");
	delete app;
	HL_PROFILE_END_SESSION();

	return EXIT_SUCCESS;
}


#endif //HEIRLOOM_ENTRYPOINT_H
