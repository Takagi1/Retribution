#include "SceneGraph.h"
#include "../Graphics/ShaderHandler.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GUIObject*> SceneGraph::sceneGUIObjects = std::map<std::string, GUIObject*>();

SceneGraph * SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}


void SceneGraph::AddGameObject(GameObject * go_, std::string tag_)
{

	if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else {
		Debug::Warning("Trying to add a GameObject with a tag " + tag_ +
			" that already exist.", "SceneGraph.cpp", __LINE__);

		bool check = false;
		int loop = 1;
		std::string newTag = tag_ + std::to_string(loop);
		while(!check){
			if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
				check = true;
			}
			else {
				loop++;
				newTag = tag_ + std::to_string(loop);
			}
		}
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}

	if (go_->GetComponent<BoundingBox>()) {
		CollisionHandler::GetInstance()->AddObject(go_);
	}
}


void SceneGraph::AddGUIObject(GUIObject* go, std::string tag_)
{
	if (sceneGUIObjects.find(tag_) == sceneGUIObjects.end()) {
		go->SetTag(tag_);
		sceneGUIObjects[tag_] = go;
	}
	else {
		Debug::Warning("Trying to add a GUI_Object with a tag " + tag_ +
			" that already exist.", "SceneGraph.cpp", __LINE__);

		bool check = false;
		int loop = 1;
		std::string newTag = tag_ + std::to_string(loop);
		while (!check) {
			if (sceneGUIObjects.find(tag_) == sceneGUIObjects.end()) {
				check = true;
			}
			else {
				loop++;
				newTag = tag_ + std::to_string(loop);
			}
		}
		go->SetTag(newTag);
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

GUIObject* SceneGraph::GetGUIObject(std::string tag_)
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
}


void SceneGraph::Draw(Camera* camera_)
{
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(ShaderHandler::GetInstance()->GetShader("BasicShader"));

	for (auto g : sceneGameObjects) {
		g.second->Draw(camera_);
	}
	glEnable(GL_DEPTH_TEST);
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
