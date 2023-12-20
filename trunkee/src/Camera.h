#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

class Camera
{
public:
	constexpr static glm::vec3 WORLD_UP = { 0.f, 1.f, 0.f };
	constexpr static glm::vec3 DEFAULT_POSITION = { 0.f, 0.f, 3.f };
	constexpr static glm::vec3 DEFAULT_TARGET = { 0.f, 0.f, 0.f };

	constexpr static float DEFAULT_FOV = 75.f;
	constexpr static float DEFAULT_ASPECT = 1700.f / 900.f;
	constexpr static float DEFAULT_ZNEAR = 0.1f;
	constexpr static float DEFAULT_ZFAR = 200.f;
	constexpr static float DEFAULT_SPEED = 12.f;
	constexpr static float DEFAULT_YAW = -90.f;
	constexpr static float DEFAULT_PITCH = 0.f;
	constexpr static float DEFAULT_SENSITIVITY = 0.1f;

	Camera();
	Camera(glm::vec3 position);

	Camera& WithFOV(float fov) { m_fov = fov; UpdateProjMatrix(); return *this; }
	Camera& WithAspect(float aspect) { m_aspect = aspect; UpdateProjMatrix(); return *this; }
	Camera& WithZNear(float zNear) { m_zNear = zNear; UpdateProjMatrix(); return *this; }
	Camera& WithZFar(float zFar) { m_zFar = zFar; UpdateProjMatrix(); return *this; }
	Camera& WithSpeed(float speed) { m_speed = speed; return *this; }

	float GetFOV(float fov) const { return m_fov; }
	float GetAspect(float aspect) const { return m_aspect; }
	float GetZNear(float zNear) const { return m_zNear; }
	float GetZFar(float zFar) const { return m_zFar; }

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix() const { return m_projMatrix; }
	glm::vec3 GetPosition() const { return m_position; }

	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);

	void Print() const;
	void Update();
	void UpdateMouseView(int mouseX, int mouseY);
	void UpdateAxis();
	void UpdateProjMatrix();

private:
	glm::mat4 m_projMatrix;

	glm::vec3 m_front = glm::normalize(DEFAULT_TARGET - DEFAULT_POSITION);
	glm::vec3 m_position = DEFAULT_POSITION;

	float m_fov = DEFAULT_FOV;
	float m_aspect = DEFAULT_ASPECT;
	float m_zNear = DEFAULT_ZNEAR;
	float m_zFar = DEFAULT_ZFAR;
	float m_speed = DEFAULT_SPEED;
	float m_yaw = DEFAULT_YAW;
	float m_pitch = DEFAULT_PITCH;
	float m_sensitivity = DEFAULT_SENSITIVITY;

	bool m_firstMouse = true;
};