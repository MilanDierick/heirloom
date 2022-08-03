//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_HEIRLOOM_H
#define HEIRLOOM_HEIRLOOM_H

// ==== Core ======================================================
#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Core.h"
#include "Heirloom/Core/Input.h"
#include "Heirloom/Core/KeyCodes.h"
#include "Heirloom/Core/Layer.h"
#include "Heirloom/Core/Log.h"
#include "Heirloom/Core/MouseCodes.h"
#include "Heirloom/Core/Timestep.h"
#include "Heirloom/ImGui/ImGuiLayer.h"
// =================================================================

#include "Heirloom/Scene/Scene.h"
#include "Heirloom/Scene/Entity.h"
#include "Heirloom/Scene/Components.h"

// ==== Renderer ===================================================
#include "Heirloom/Renderer/FrameBuffer.h"
#include "Heirloom/Renderer/OrthographicCamera.h"
#include "Heirloom/Renderer/OrthographicCameraController.h"
#include "Heirloom/Renderer/Renderer.h"
#include "Heirloom/Renderer/Renderer2D.h"
#include "Heirloom/Renderer/Texture.h"
// =================================================================

#include "Heirloom/Profiler/Instrumentation.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "imgui.h"

#endif //HEIRLOOM_HEIRLOOM_H
