#include "SceneGraph.h"
#include "../Graphics/ShaderHandler.h"
#include "../Math/Physics2D.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::map<std::string, std::shared_ptr<GameObject>> SceneGraph::sceneGameObjects = std::map<std::string, std::shared_ptr<GameObject>>();
std::map<std::string, GameObject*> SceneGraph::sceneGUIObjects = std::map<std::string, GameObject*>();

SceneGraph * SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}


void SceneGraph::AddGameObject(std::shared_ptr<GameObject> go_, std::string name_)
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


	CollisionHandler::GetInstance()->AddObject(go_);
	go_.reset();
}

bool SceneGraph::RemoveGameObject(std::string name_)
{
	std::map<std::string,std::shared_ptr<GameObject>>::iterator obj = sceneGameObjects.find(name_);
	if (obj == sceneGameObjects.end()) {
		Debug::Error("No game object of that name has been found.", "SceneGraph.cpp", __LINE__);
		return false;
	}
	else {

		//TODO: remove obj from collision handler
		obj->second.reset();
		
		sceneGameObjects.erase(obj);
		
		return true;
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
}

std::weak_ptr<GameObject> SceneGraph::GetGameObject(std::string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return std::weak_ptr<GameObject>();
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
	
	//Collision update
	for (auto go : sceneGameObjects) {
		std::vector<std::weak_ptr<GameObject>> obj;
		obj.reserve(5);
		obj = CollisionHandler::GetInstance()->AABB(go.second->GetBoundingBox());

		//First check if the object even has physics 
		

		if (go.second->GetComponent<Physics2D>()) {
			//if the object has rigid body and is not static make it apply collision detection
			if (go.second->GetComponent<Physics2D>()->GetRigidBody() && 
				!go.second->GetComponent<Physics2D>()->GetStaticObj()) {

				go.second->GetComponent<Physics2D>()->CollisionResponse(obj, deltaTime_);
			}
		}

		//At the end do the manually programed collision responses for the game object
		go.second->CollisionResponse(obj);
	}


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
			go.second.reset();
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
