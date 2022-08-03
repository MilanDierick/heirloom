//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_ORTHOGRAPHICCAMERACONTROLLER_H
#define HEIRLOOM_ORTHOGRAPHICCAMERACONTROLLER_H

#include "Heirloom/Core/Timestep.h"
#include "Heirloom/Events/ApplicationEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"
#include "Heirloom/Renderer/OrthographicCamera.h"

namespace Heirloom
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool rotation = false);

		void Update(Timestep ts);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera() const;
		float GetZoomLevel() const;
		void SetZoomLevel(float zoomLevel);

	private:
		void OnMouseScrolledEvent(MouseScrolledEventArgs eventArgs);
		void OnWindowResizedEvent(WindowResizedEventArgs eventArgs);
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition     = {0.0f, 0.0f, 0.0f};
		float m_CameraRotation         = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}

#endif //HEIRLOOM_ORTHOGRAPHICCAMERACONTROLLER_H
