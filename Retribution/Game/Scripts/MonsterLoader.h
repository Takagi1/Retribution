#pragma once

#include "../../Engine/Parser/XMLParser.h"
#include "../GameObjects/Monsters/Archer.h"




class MonsterLoader {
public:

	//This function will get the monsters and parse the information from the lines
	//Should the break be the number of children or will the nullptr check idea work here?
	static std::vector<std::shared_ptr<Monster>> LoadMonsters() {
		XMLParser::GetInstance()->Move("Monsters");

		std::vector<std::shared_ptr<Monster>> obj;
		obj.reserve(5);
		XMLParser::GetInstance()->ListBegin();
		while (true) {
			std::string name = XMLParser::GetInstance()->GetString("Name");

			//Load the info into the monster 

			std::shared_ptr<Monster> mon = std::move(GetMonster(name));
			mon->OnCreate();

			mon->SetPosition(XMLParser::GetInstance()->GetVec2("Location"));

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

private:
	static std::shared_ptr<Monster> GetMonster(std::string name_) {
		if (name_ == "Archer") { return std::make_shared<Archer>(); }
	}
};