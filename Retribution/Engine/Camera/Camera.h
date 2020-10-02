#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../FX/LightSource.h"

struct BoundingBox;

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	glm::vec2 GetClippingPlanes() const;

	std::vector<LightSource*> GetLightSources() const;
	void AddLightSource(LightSource* source);

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseScroll(int y_);

	std::vector<glm::vec4> GetFrustumPlanes();

	bool FrustumCull(std::vector<glm::vec4> frustum_, BoundingBox* box_);

private: 
	void UpdateCameraVectors();
	
	glm::vec3 position;

	glm::mat4 perspective;
	glm::mat4 orthographic;

	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;

	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lightSources;

	void OnDestroy();
};

#endif // !CAMERA_H
