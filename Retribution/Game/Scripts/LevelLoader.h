#pragma once

#include <vector>
#include "../GameObjects/Tile.h"
#include "../../Engine/Parser/XMLParser.h"


class LevelLoader {
public:

	static std::vector<std::shared_ptr<Tile>> LoadTiles() {
		std::vector<std::shared_ptr<Tile>> obj;
		obj.reserve(5);
		XMLParser::GetInstance()->ListBegin();
		while (true) {
			std::string name = XMLParser::GetInstance()->GetString("Image");

			//Load the info into the monster 

			std::shared_ptr<Tile> mon = std::make_shared<Tile>();
			mon->OnCreate(XMLParser::GetInstance()->GetVec2("Location"));

			obj.push_back(std::move(mon));

			//If done return the object

			if (!XMLParser::GetInstance()->HasSibling()) {
				XMLParser::GetInstance()->Return();
				return obj;
			}

			//Else go to the next sibiling

			XMLParser::GetInstance()->NextNode();
		}
	}
};