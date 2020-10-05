#include "SceneGraph.h"
#include "../Graphics/ShaderHandler.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GameObject*> SceneGraph::sceneGUIObjects = std::map<std::string, GameObject*>();

SceneGraph * SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}


void SceneGraph::AddGameObject(GameObject * go_, std::string name_)
{

	if (sceneGameObjects.find(name_) == sceneGameObjects.end()) {
		go_->SetName(name_);
		sceneGameObjects[name_] = go_;
	}
	else {
		Debug::Warning("Trying to add a GameObject with a tag " + name_ +
			" that already exist.", "SceneGraph.cpp", __LINE__);

		bool check = false;
		int loop = 1;
		std::string newTag = name_ + std::to_string(loop);
		while(!check){
			if (sceneGameObjects.find(name_) == sceneGameObjects.end()) {
				check = true;
			}
			else {
				loop++;
				newTag = name_ + std::to_string(loop);
			}
		}
		go_->SetName(newTag);
		sceneGameObjects[newTag] = go_;
	}

	if (go_->GetComponent<BoundingBox>()) {
		CollisionHandler::GetInstance()->AddObject(go_);
	}
}


void SceneGraph::AddGUIObject(GameObject* go, std::string name_)
{
	if (sceneGUIObjects.find(name_) == sceneGUIObjects.end()) {
		go->SetName(name_);
		sceneGUIObjects[name_] = go;
	}
	else {
		Debug::Warning("Trying to add a Gamebject with a tag " + name_ +
			" that already exist.", "SceneGraph.cpp", __LINE__);

		bool check = false;
		int loop = 1;
		std::string newTag = name_ + std::to_string(loop);
		while (!check) {
			if (sceneGUIObjects.find(name_) == sceneGUIObjects.end()) {
				check = true;
			}
			else {
				loop++;
				newTag = name_ + std::to_string(loop);
			}
		}
		go->SetName(newTag);
		sceneGUIObjects[newTag] = go;
	}
	//TODO:
	//CollisionHandler::GetInstance()->AddObject(go);
}

GameObject * SceneGraph::GetGameObject(std::string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

GameObject* SceneGraph::GetGUIObject(std::string tag_)
{
	if (sceneGUIObjects.find(tag_) != sceneGUIObjects.end()) {
		return sceneGUIObjects[tag_];
	}
	return nullptr;
}


void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
	//Collision fixing here?

	for (auto go : sceneGUIObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Draw(Camera* camera_)
{

	glUseProgram(ShaderHandler::GetInstance()->GetShader("BasicShader"));

	for (auto g : sceneGameObjects) {
		g.second->Draw(camera_);
	}

	//Update GUI after objects to ignore depth

	glUseProgram(ShaderHandler::GetInstance()->GetShader("GUIShader"));

	for (auto g : sceneGUIObjects) {
		g.second->Draw(camera_);
	}
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}
}

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}
