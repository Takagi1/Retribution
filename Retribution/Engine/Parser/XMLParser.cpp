#include "XMLParser.h"
#include "../Core/Debug.h"
std::unique_ptr<XMLParser> XMLParser::parserInstance = nullptr;



XMLParser* XMLParser::GetInstance()
{
	if (parserInstance.get() == nullptr) {
		parserInstance.reset(new XMLParser);
	}
	return parserInstance.get();
}

void XMLParser::ParseFile(const std::string & fileName_)
{
	std::ifstream file(fileName_);
	rapidxml::xml_document<> doc;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	content = (buffer.str());
	doc.parse<0>(&content[0]);
	root = doc.first_node();
}

void XMLParser::FindNode(std::string elementName_)
{
	root = NodeQuery(root, elementName_);
}


rapidxml::xml_node<>* XMLParser::NodeQuery(rapidxml::xml_node<>* currentNode_, std::string elementName_)
{
	rapidxml::xml_node<>* nodea_ = currentNode_->next_sibling();

	if (currentNode_->type() == 1) {
		//Return value if found
	//	if (currentNode_->name() == elementName_) { return currentNode_->first_attribute(attribute_.c_str())->value(); }

		//if its not found go to its first child and search there
	//	NodeQuery(currentNode_->first_node(0), attribute_, node_);

		//if it has no children or the return is 0 then go to the next sibling.
	//	NodeQuery(currentNode_->next_sibling(), attribute_, node_);

		//std::string line = root->first_node(className_.c_str())->first_node(elementName_.c_str())->value();
	}
	return nullptr;
}

glm::vec3 XMLParser::GetVec3(std::string elementName_)
{
	std::string line = root->first_node(elementName_.c_str())->value();

	std::istringstream v(line.substr(1));
	float x, y, z;
	v >> x >> y >> z;

	return glm::vec3(x, y, z);
}

glm::vec2 XMLParser::GetVec2(std::string elementName_)
{
	std::string line = root->first_node(elementName_.c_str())->value();

	std::istringstream v(line.substr(1));
	float x, y;
	v >> x >> y;

	return glm::vec2(x, y);
}

std::string XMLParser::GetString(std::string elementName_)
{
	return root->first_node(elementName_.c_str())->value();
}

float XMLParser::GetFloat(std::string className_)
{
	std::string line = root->first_node(className_.c_str())->value();

	std::istringstream v(line.substr(1));
	float x;
	v >> x;

	return x;
}

float XMLParser::GetFloat(std::string className_, std::string attributeName_)
{
	std::string line = root->first_node(className_.c_str())->first_attribute(attributeName_.c_str())->value();

	std::istringstream v(line.substr(1));
	float x;
	v >> x;

	return x;
}

void XMLParser::Enter(std::string elementName_)
{
	rapidxml::xml_node<>* node_ = root->first_node(elementName_.c_str());

	if (node_ == nullptr) {
		Debug::Error("Element not found", "XMLParser.cpp", __LINE__);
		return;
	}

	root = node_;
	node_ = nullptr;
}

void XMLParser::Move(std::string elementName_)
{
	rapidxml::xml_node<>* node_ = root->parent()->first_node(elementName_.c_str());

	if (node_ == nullptr) {
		Debug::Error("Element not found", "XMLParser.cpp", __LINE__);
		return;
	}

	root = node_;
	node_ = nullptr;
}

void XMLParser::Return()
{
	if (!root->parent()) {
		Debug::Error("Parent not found", "XMLParser.cpp", __LINE__);
	}

	root = root->parent();
}

void XMLParser::ListBegin()
{
	root = root->first_node();
}

void XMLParser::NextNode()
{
	root = root->next_sibling();
}

bool XMLParser::HasSibling()
{
	if (root->next_sibling() != nullptr) {
		return true;
	}
	return false;
}

void XMLParser::OnDestroy()
{
}

XMLParser::XMLParser() : root(nullptr) {

}

XMLParser::~XMLParser()
{
	OnDestroy();
}
