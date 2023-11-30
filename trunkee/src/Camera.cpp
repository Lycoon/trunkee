#include "Camera.h"

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::UpdateProjMatrix()
{
	m_projMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);
	//m_projMatrix[1][1] *= -1;
}

void Camera::Update()
{
	glm::vec3 newFront;
	std::cout << "pos: " << Camera::DEFAULT_POSITION.x << " " << Camera::DEFAULT_POSITION.y << " " << Camera::DEFAULT_POSITION.z << std::endl;

	newFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	newFront.y = sin(glm::radians(m_pitch));
	newFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(newFront);

	m_right = glm::normalize(glm::cross(m_front, DEFAULT_UP));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::MoveForward(float delta)
{
	m_position += m_direction * m_speed * delta;
}

void Camera::MoveBackward(float delta)
{
	m_position -= m_direction * m_speed * delta;
}

void Camera::MoveLeft(float delta)
{
	m_position -= glm::normalize(glm::cross(m_direction, DEFAULT_UP)) * m_speed * delta;
}

void Camera::MoveRight(float delta)
{
	m_position += glm::normalize(glm::cross(m_direction, DEFAULT_UP)) * m_speed * delta;
}