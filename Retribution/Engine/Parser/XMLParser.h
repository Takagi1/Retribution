#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <rapidxml.hpp>
//#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <sstream>
#include <glm/glm.hpp>

class XMLParser {
public:
	XMLParser(const XMLParser&) = delete;
	XMLParser(XMLParser&&) = delete;
	XMLParser& operator =(const XMLParser&) = delete;
	XMLParser& operator =(XMLParser&&) = delete;

	static XMLParser* GetInstance();

	//Input file name to parse.
	void ParseFile(const std::string & fileName_);


	//Used to find node's
	void FindNode(std::string attribute_);
	rapidxml::xml_node<>* NodeQuery(rapidxml::xml_node<>* currentNode_, std::string attribute_);

	std::string GetString(std::string elementName_);
	float GetFloat(std::string className_);
	float GetFloat(std::string className_, std::string attributeName_);
	glm::vec2 GetVec2(std::string elementName_);
	glm::vec3 GetVec3(std::string elementName_);

	//Treat this like going to an new folder
	void Enter(std::string elementName_);
	void Move(std::string elementName_);
	void Return();

	//First call in getting a list, sets root to first node in a list
	bool ListBegin();

	//Last call in getting a list, sets the node to is next sibling
	void NextNode();

	//Used to check if this is the last node in a list
	bool HasSibling();

	void OnDestroy();
private:
	XMLParser();
	~XMLParser();

	static std::unique_ptr<XMLParser> parserInstance;
	friend std::default_delete<XMLParser>;

	rapidxml::xml_node<>* root;
	std::string content;
};
#endif // !XMLPARSER_H