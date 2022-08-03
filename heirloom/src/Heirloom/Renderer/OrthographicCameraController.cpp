//
// Created by developer on 09/12/2021.
//

#include "hlpch.h"
#include "OrthographicCameraController.h"
#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Input.h"
#include "Heirloom/Core/KeyCodes.h"

namespace Heirloom
{
	OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation)
			: m_AspectRatio(aspectRatio),
			  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
			  m_Rotation(rotation)
	{
		HL_PROFILE_FUNCTION()

		Input::MouseScrolledEvent += HL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent);
		Application::Get().GetWindow().WindowResizedEvent += HL_BIND_EVENT_FN(
				OrthographicCameraController::OnWindowResizedEvent);
	}

	void OrthographicCameraController::Update(const Timestep ts)
	{
		HL_PROFILE_FUNCTION()

		if (Input::IsKeyPressed(KeyCode::A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(KeyCode::D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(KeyCode::W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(KeyCode::S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(KeyCode::Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}

			if (Input::IsKeyPressed(KeyCode::E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}

			if (m_CameraRotation > 180.0f)
			{
				m_CameraRotation -= 360.0f;
			}
			else if (m_CameraRotation <= -180.0f)
			{
				m_CameraRotation += 360.0f;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnResize(const float width, const float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	OrthographicCamera& OrthographicCameraController::GetCamera()
	{
		return m_Camera;
	}

	const OrthographicCamera& OrthographicCameraController::GetCamera() const
	{
		return m_Camera;
	}

	float OrthographicCameraController::GetZoomLevel() const
	{
		return m_ZoomLevel;
	}

	void OrthographicCameraController::SetZoomLevel(const float zoomLevel)
	{
		m_ZoomLevel = zoomLevel;
	}

	void OrthographicCameraController::OnMouseScrolledEvent(const MouseScrolledEventArgs eventArgs)
	{
		m_ZoomLevel -= eventArgs.YOffset * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::OnWindowResizedEvent(const WindowResizedEventArgs eventArgs)
	{
		m_AspectRatio = static_cast<float>(eventArgs.Width) / static_cast<float>(eventArgs.Height);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
}

