#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

class Camera
{
public:
	constexpr static glm::vec3 DEFAULT_UP = { 0.f, 1.f, 0.f };
	constexpr static glm::vec3 DEFAULT_POSITION = { 0.f, 0.f, 3.f };
	constexpr static glm::vec3 DEFAULT_TARGET = { 0.f, 0.f, 0.f };

	constexpr static float DEFAULT_FOV = 75.f;
	constexpr static float DEFAULT_ASPECT = 1700.f / 900.f;
	constexpr static float DEFAULT_ZNEAR = 0.1f;
	constexpr static float DEFAULT_ZFAR = 200.f;
	constexpr static float DEFAULT_SPEED = 0.1f;
	constexpr static float DEFAULT_YAW = -90.0f;
	constexpr static float DEFAULT_PITCH = 0.0f;

	Camera(): 
		m_up(DEFAULT_UP),
		m_position(DEFAULT_POSITION),
		m_front(glm::normalize(DEFAULT_TARGET - DEFAULT_POSITION))
	{ UpdateProjMatrix(); Update(); }

	Camera(glm::vec3 position) : m_position(position) { UpdateProjMatrix(); }

	Camera& WithFOV(float fov) { m_fov = fov; UpdateProjMatrix(); return *this; }
	Camera& WithAspect(float aspect) { m_aspect = aspect; UpdateProjMatrix(); return *this; }
	Camera& WithZNear(float zNear) { m_zNear = zNear; UpdateProjMatrix(); return *this; }
	Camera& WithZFar(float zFar) { m_zFar = zFar; UpdateProjMatrix(); return *this; }
	Camera& WithSpeed(float speed) { m_speed = speed; return *this; }

	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetPosition() const { return m_position; }
	glm::mat4 GetProjMatrix() const { return m_projMatrix; }
	float GetFOV(float fov) const { return m_fov; }
	float GetAspect(float aspect) const { return m_aspect; }
	float GetZNear(float zNear) const { return m_zNear; }
	float GetZFar(float zFar) const { return m_zFar; }

	void MoveForward(float delta);
	void MoveBackward(float delta);
	void MoveLeft(float delta);
	void MoveRight(float delta);

	void Update();
	void UpdateProjMatrix();

private:
	glm::mat4 m_projMatrix{};

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_up;

	float m_fov = DEFAULT_FOV;
	float m_aspect = DEFAULT_ASPECT;
	float m_zNear = DEFAULT_ZNEAR;
	float m_zFar = DEFAULT_ZFAR;
	float m_speed = DEFAULT_SPEED;
	float m_yaw = DEFAULT_YAW;
	float m_pitch = DEFAULT_PITCH;
};