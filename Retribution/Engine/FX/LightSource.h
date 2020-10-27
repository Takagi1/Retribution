#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/vec3.hpp>
class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambientLoc_, float diffuseLoc_, glm::vec3 colourLoc_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float GetAmbientLoc() const;
	float GetDiffuseLoc() const;
	glm::vec3 GetColourLoc() const;

	void SetPosition(glm::vec3 position_);
	void SetAmbientLoc(float ambientLoc_);
	void SetDiffuseLoc(float diffuseLoc_);
	void SetColourLoc(glm::vec3 colourLoc_);

private:
	glm::vec3 position, colourLoc;
	float ambientLoc, diffuseLoc;
};
#endif // !LIGHTSOURCE_H
