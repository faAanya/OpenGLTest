#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CAMERA_MOVEMENT {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//TODO: READ FROM JSON

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 15.0f;
const float ZOOM_SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

const float MAX_ZOOM = 150.0f;
const float MIN_ZOOM = 1;

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
        Up = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}
	
	void ProcessMovement(float deltaTime, CAMERA_MOVEMENT direction)
	{
		float velocity = MovementSpeed * deltaTime;

		if (direction == UP)
			Position += (Up * velocity);
		if (direction == DOWN)
			Position -= (Up * velocity);
		if (direction == LEFT)
			Position -= (Right * velocity);
		if (direction == RIGHT)
			Position += (Right * velocity);
	}

	void ProcessMouseRotation(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset * ZOOM_SPEED;
		if (Zoom < MIN_ZOOM)
			Zoom = MIN_ZOOM;
		if (Zoom > MAX_ZOOM)
			Zoom = MAX_ZOOM;
	}

private:

	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
	
		Right = glm::normalize(glm::cross(Front, WorldUp));  
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif