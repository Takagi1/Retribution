#include "SpriteSurface.h"
#include "../Graphics/TextureHandler.h"



SpriteSurface::SpriteSurface(bool useView_, std::string name_)
{
	name = name_;

	useView = useView_;

	if (!TextureHandler::GetInstance()->GetTexture(name)) {
		TextureHandler::GetInstance()->CreateTexture(name_,
			"./Resources/Textures/" + name_);
	}
	textureID = TextureHandler::GetInstance()->GetTextureData(name)->textureID;
	height = TextureHandler::GetInstance()->GetTextureData(name)->height;
	width = TextureHandler::GetInstance()->GetTextureData(name)->width;

	scale = glm::vec2(width, height);
}

SpriteSurface::~SpriteSurface() {

}

float SpriteSurface::GetWidth() const
{
	return width;
}

float SpriteSurface::GetHeight() const
{
	return height;
}

glm::vec2 SpriteSurface::GetScale() const
{
	return scale;
}