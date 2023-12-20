#include "Camera.h"

#include "input/InputManager.h"
#include "time/Time.h"

Camera::Camera()
{
	EventManager& eventManager = EventManager::Get();
	const auto UpdateCameraMouseView = [&](const EventManager::EventData& event)
	{
		UpdateMouseView(event.mouseMotion.xrel, event.mouseMotion.yrel);
	};
	eventManager.AddListener(UpdateCameraMouseView, EventType::MouseMove);

	UpdateProjMatrix();
}

Camera::Camera(glm::vec3 position) : m_position(position)
{ 
	UpdateProjMatrix();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAtRH(m_position, m_position + m_front, WORLD_UP);
}

void Camera::UpdateProjMatrix()
{
	m_projMatrix = glm::perspectiveRH(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);
	m_projMatrix[1][1] *= -1;
}

void Camera::Update()
{
	InputManager& inputManager = InputManager::Get();
	float deltaTime = Time::Get().GetDeltaTime();

	if (inputManager.IsActive(KeybindAction::MoveFront))
		MoveForward(deltaTime);
	if (inputManager.IsActive(KeybindAction::MoveBack))
		MoveBackward(deltaTime);
	if (inputManager.IsActive(KeybindAction::MoveLeft))
		MoveLeft(deltaTime);
	if (inputManager.IsActive(KeybindAction::MoveRight))
		MoveRight(deltaTime);
	if (inputManager.IsActive(KeybindAction::MoveUp))
		MoveUp(deltaTime);
	if (inputManager.IsActive(KeybindAction::MoveDown))
		MoveDown(deltaTime);
}

void Camera::UpdateMouseView(int mouseMotionX, int mouseMotionY)
{
	InputManager& inputManager = InputManager::Get();
	m_yaw += mouseMotionX * m_sensitivity;
	m_pitch -= mouseMotionY * m_sensitivity;

	if (m_pitch > 89.f)
		m_pitch = 89.f;
	if (m_pitch < -89.f)
		m_pitch = -89.f;

	UpdateAxis();
}

void Camera::UpdateAxis()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	newFront.y = sin(glm::radians(m_pitch));
	newFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(newFront);
}

void Camera::MoveForward(float deltaTime)
{
	m_position += m_front * m_speed * deltaTime;
}

void Camera::MoveBackward(float deltaTime)
{
	m_position -= m_front * m_speed * deltaTime;
}

void Camera::MoveLeft(float deltaTime)
{
	m_position -= glm::cross(m_front, WORLD_UP) * m_speed * deltaTime;
}

void Camera::MoveRight(float deltaTime)
{
	m_position += glm::cross(m_front, WORLD_UP) * m_speed * deltaTime;
}

void Camera::MoveUp(float deltaTime)
{
	m_position += WORLD_UP * m_speed * deltaTime;
}

void Camera::MoveDown(float deltaTime)
{
	 m_position -= WORLD_UP * m_speed * deltaTime;
}

void Camera::Print() const
{
	std::cout << "Camera: " << std::endl;
	std::cout << "Position: " << m_position.x << ", " << m_position.y << ", " << m_position.z << std::endl;
	std::cout << "Front: " << m_front.x << ", " << m_front.y << ", " << m_front.z << std::endl;
	std::cout << "Yaw: " << m_yaw << std::endl;
	std::cout << "Pitch: " << m_pitch << std::endl;
}