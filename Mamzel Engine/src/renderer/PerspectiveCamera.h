#pragma once

#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

class PerspectiveCamera
{
private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;

	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;

	float m_Pitch, m_Yaw, m_Roll;
	float m_FOV;
	float m_AspectRatio;

	float m_LastMouseX, m_LastMouseY;

	float m_Speed;
	float m_MouseSens;

	void handleMouseMovement(GLFWwindow* window);

public:

	PerspectiveCamera(float windowWidth, float windowHeight, float fov);
	~PerspectiveCamera();

	void SetPosition(const glm::vec3& position);
	void SetMoveSpeedAndMouseSens(float moveSpeed, float mouseSens);
	void SetAspectRatio(float newAspectRatio);

	void Update(float frameTime);

	inline const glm::mat4& GetMatrixVP() const { return m_ViewProjectionMatrix; }
	inline const glm::vec3& GetPosition() const { return m_Position; }
};