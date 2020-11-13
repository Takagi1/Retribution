#include "SpriteSurface.h"
#include "../Graphics/TextureHandler.h"

std::vector<Vertex2D> SpriteSurface::vertexList = std::vector<Vertex2D>();
std::vector<Vertex2D> SpriteSurface::vertexListFlip = std::vector<Vertex2D>();

SpriteSurface::SpriteSurface(bool useView_, std::string name_)
{
	name = name_;

	useView = useView_;

	if (vertexList.size() == 0) {
		vertexList.reserve(4);
		vertexList.push_back(Vertex2D());
		vertexList.push_back(Vertex2D());
		vertexList.push_back(Vertex2D());
		vertexList.push_back(Vertex2D());


		vertexList[0].position = glm::vec2(0.0f, 1.0f);
		vertexList[0].texCoord = glm::vec2(0, 0);

		vertexList[1].position = glm::vec2(1.0f, 1.0f);
		vertexList[1].texCoord = glm::vec2(1, 0);

		vertexList[2].position = glm::vec2(0.0f, 0.0f);
		vertexList[2].texCoord = glm::vec2(0, 1);

		vertexList[3].position = glm::vec2(1.0f, 0.0f);
		vertexList[3].texCoord = glm::vec2(1, 1);
	}

	if (vertexListFlip.size() == 0) {
		vertexListFlip.reserve(4);
		vertexListFlip.push_back(Vertex2D());
		vertexListFlip.push_back(Vertex2D());
		vertexListFlip.push_back(Vertex2D());
		vertexListFlip.push_back(Vertex2D());


		vertexListFlip[0].position = glm::vec2(1.0f, 1.0f);
		vertexListFlip[0].texCoord = glm::vec2(0, 0);

		vertexListFlip[1].position = glm::vec2(0.0f, 1.0f);
		vertexListFlip[1].texCoord = glm::vec2(1, 0);

		vertexListFlip[2].position = glm::vec2(1.0f, 0.0f);
		vertexListFlip[2].texCoord = glm::vec2(0, 1);

		vertexListFlip[3].position = glm::vec2(0.0f, 0.0f);
		vertexListFlip[3].texCoord = glm::vec2(1, 1);
	}


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
	vertexList.clear();
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