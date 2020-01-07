#include "PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../util/Input.h"

#include "../debug/Instrumentor.h"

void PerspectiveCamera::handleMouseMovement(GLFWwindow* window)
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	float xOffset = (xPos - m_LastMouseX) * m_MouseSens;
	float yOffset = (yPos - m_LastMouseY) * m_MouseSens;
	m_LastMouseX = xPos;
	m_LastMouseY = yPos;

	m_Yaw += xOffset;
	m_Pitch -= yOffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	front.y = sin(glm::radians(m_Pitch));
	front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
	m_Front = glm::normalize(front);
}

PerspectiveCamera::PerspectiveCamera(float windowWidth, float windowHeight, float fov)
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_LastMouseX = windowWidth / 2.0f;
	m_LastMouseY = windowHeight / 2.0f;

	m_Speed = 0.03f;
	m_MouseSens = 1.0f;

	m_Pitch = 0.0f;
	m_Yaw = 270.0f;
	m_Roll = 0.0f;

	m_FOV = fov;
	m_AspectRatio = windowWidth / windowHeight;

	m_ProjectionMatrix = glm::perspective(glm::radians(fov), windowWidth / windowHeight, 0.01f, 500.0f);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void PerspectiveCamera::SetMoveSpeedAndMouseSens(float moveSpeed, float mouseSens)
{
	m_Speed = moveSpeed;
	m_MouseSens = mouseSens;
}

void PerspectiveCamera::SetAspectRatio(float newAspectRatio)
{
	m_AspectRatio = newAspectRatio;
}

void PerspectiveCamera::Update(float frameTime)
{	
	//handleMouseMovement(window);

	// Mouse emulation
	{
		if (Input::KeyPressed(GLFW_KEY_LEFT))
			m_Yaw -= m_MouseSens * m_FOV / 45.0f * frameTime;
		if (Input::KeyPressed(GLFW_KEY_RIGHT))
			m_Yaw += m_MouseSens * m_FOV / 45.0f * frameTime;
		if (Input::KeyPressed(GLFW_KEY_UP))
			m_Pitch += m_MouseSens * m_FOV / 45.0f * frameTime;
		if (Input::KeyPressed(GLFW_KEY_DOWN))
			m_Pitch -= m_MouseSens * m_FOV / 45.0f * frameTime;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		if (m_Yaw >= 360.0f)
			m_Yaw -= 360.0f;
		if (m_Yaw < 0.0f)
			m_Yaw = 360.0f + m_Yaw;

		glm::vec3 front;
		front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
		front.y = sin(glm::radians(m_Pitch));
		front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
		m_Front = glm::normalize(front);
	}

	// Mouse scroll emulation
	{
		if (Input::KeyPressed(GLFW_KEY_PAGE_UP))
			m_FOV -= 0.05 * frameTime;
		if (Input::KeyPressed(GLFW_KEY_PAGE_DOWN))
			m_FOV += 0.05 * frameTime;

		if (m_FOV < 0.5f)
			m_FOV = 0.5f;
		if (m_FOV > 150.0f)
			m_FOV = 150.0f;

		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.01f, 500.0f);
	}
	
	// Movement
	{
		if (Input::KeyPressed(GLFW_KEY_W))
			m_Position += m_Front * m_Speed * frameTime;
		if (Input::KeyPressed(GLFW_KEY_S))
			m_Position -= m_Front * m_Speed * frameTime;
		if (Input::KeyPressed(GLFW_KEY_A))
			m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed * frameTime;
		if (Input::KeyPressed(GLFW_KEY_D))
			m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed * frameTime;
		if (Input::KeyPressed(GLFW_KEY_LEFT_SHIFT))
			m_Position += m_Up * m_Speed * frameTime;
		if (Input::KeyPressed(GLFW_KEY_LEFT_CONTROL))
			m_Position -= m_Up * m_Speed * frameTime;
	}

	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

