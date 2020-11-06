#pragma once

#include "../../Engine/Parser/XMLParser.h"
#include "../GameObjects/Monsters/Monster.h"
#include "../GameObjects/Monsters/Archer.h"


//TODO: I feel a much better way of doing this can exist (mabye doing multiple nodes each representing data then going through it?)

//TODO: If I want to create a XML document that will have the monsters info in it, then it might be a good idea to 
//allow for an improved version of the loader.  will most likely need the ability to load from a file without loseing 
//My place in another?

class MonsterLoader {
public:

	//This function will get the monsters and parse the information from the lines
	//Should the break be the number of children or will the nullptr check idea work here?
	static std::vector<std::shared_ptr<Monster>> LoadMonsters() {
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