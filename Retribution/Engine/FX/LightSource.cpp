#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambientLoc_, float diffuseLoc_, glm::vec3 colourLoc_)
{
	position = position_;
	ambientLoc = ambientLoc_;
	diffuseLoc = diffuseLoc_;
	colourLoc = colourLoc_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

float LightSource::GetAmbientLoc() const
{
	return ambientLoc;
}

float LightSource::GetDiffuseLoc() const
{
	return diffuseLoc;
}

glm::vec3 LightSource::GetColourLoc() const
{
	return colourLoc;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbientLoc(float ambientLoc_)
{
	ambientLoc = ambientLoc_;
}

void LightSource::SetDiffuseLoc(float diffuseLoc_)
{
	diffuseLoc = diffuseLoc_;
}

void LightSource::SetColourLoc(glm::vec3 colourLoc_)
{
	colourLoc = colourLoc_;
}
