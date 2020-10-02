#include "MaterialLoader.h"
#include <algorithm>

MaterialLoader::~MaterialLoader()
{

}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("cannot open MTL file: " + filePath_,
			"MaterialLoader.cpp", __LINE__);
		return;
	}
	std::string line;
	Material m = Material();
	std::string matName = "";
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//Seriously did i miss this?
		//std::getline(in, line, '\t');

		//TODO: finish loading the relevent information
		//Tab space issue?

		else {
			line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
			if (line.substr(0, 3) == "Ns ") {
				std::istringstream v(line.substr(3));
				float x;
				v >> x;
				m.shiniess = x;
			}

			else if (line.substr(0, 2) == "d ") {
				std::istringstream v(line.substr(2));
				float x;
				v >> x;
				m.transparency = x;
			}

			else if (line.substr(0, 3) == "Ka ") {
				std::istringstream v(line.substr(3));
				float x, y, z;
				v >> x >> y >> z;
				m.ambient = glm::vec3(x, y, z);
			}

			else if (line.substr(0, 3) == "Kd ") {
				std::istringstream v(line.substr(3));
				float x, y, z;
			  	v >> x >> y >> z;
				m.diffuse = glm::vec3(x, y, z);
			}

			else if (line.substr(0, 3) == "Ks ") {
				std::istringstream v(line.substr(3));
				float x, y, z;
				v >> x >> y >> z;
				m.specular = glm::vec3(x, y, z);

			}
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}

	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{

	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_,
				"./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
