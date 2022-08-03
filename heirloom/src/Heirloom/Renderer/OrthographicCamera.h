//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_ORTHOGRAPHICCAMERA_H
#define HEIRLOOM_ORTHOGRAPHICCAMERA_H

#include <glm/glm.hpp>

namespace Heirloom
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		glm::mat4& GetProjectionMatrix();
		glm::mat4& GetViewMatrix();
		glm::mat4& GetViewProjectionMatrix();
		glm::vec3& GetPosition();
		void SetPosition(const glm::vec3& position);
		float& GetRotation();
		void SetRotation(float rotation);

		void SetProjection(float left, float right, float bottom, float top);

	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}

#endif //HEIRLOOM_ORTHOGRAPHICCAMERA_H
