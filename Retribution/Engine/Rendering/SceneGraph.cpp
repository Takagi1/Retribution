#include "SceneGraph.h"
#include "../Graphics/ShaderHandler.h"
#include "../Math/Physics2D.h"
#include "../Rendering/Types/Image.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::map<std::string, std::shared_ptr<GameObject>> SceneGraph::sceneGameObjects = std::map<std::string, std::shared_ptr<GameObject>>();
std::map<std::string, GUIObject*> SceneGraph::sceneGUIObjects = std::map<std::string, GUIObject*>();
std::map<unsigned int, std::vector<Image*>> SceneGraph::sceneImages = std::map<unsigned int, std::vector<Image*>>();

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
		std::string newName = name_ + std::to_string(loop);
		while(!check){
			if (sceneGameObjects.find(newName) == sceneGameObjects.end()) {
				check = true;
			}
			else {
				loop++;
				newName = name_ + std::to_string(loop);
			}
		}
		go_->SetName(newName);
		sceneGameObjects[newName] = go_;
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

int SceneGraph::AddImage(Image* im, unsigned int shaderProgram_)
{
	sceneImages[shaderProgram_].push_back(im);
	return sceneImages[shaderProgram_].size() - 1;
}

//TODO: Fix out of scope issue related to exiting the game 
void SceneGraph::RemoveImage(int loc_, unsigned int shaderProgram_)
{
	sceneImages[shaderProgram_][loc_] = nullptr;
	sceneImages[shaderProgram_].erase(sceneImages[shaderProgram_].begin() + loc_);
	for (size_t i = loc_; i < sceneImages[shaderProgram_].size(); i++) {
		sceneImages[shaderProgram_][i]->SetImageLoc(i);
	}
}


void SceneGraph::AddGUIObject(GUIObject* go, std::string name_)
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

//TODO: Create Seperate GUIObjects class and GUIImage class that has a surface sprite in it.

GUIObject* SceneGraph::GetGUIObject(std::string tag_)
{
	if (sceneGUIObjects.find(tag_) != sceneGUIObjects.end()) {
		return sceneGUIObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::AddDelayedUpdate(Component* comp)
{
	delayedUpdates.push_back(comp);
}

void SceneGraph::Pause()
{
	if (isPaused) {
		isPaused = false;
	}
	else {
		isPaused = true;
	}
}


void SceneGraph::Update(const float deltaTime_)
{

	if (!isPaused) {
		for (auto go : sceneGameObjects) {

			//First Update the object 

			go.second->Update(deltaTime_);

			//Check if the object should check collision with physics.

			bool coll = false;

			if (go.second->GetComponent<Physics2D>()) {
				//if the object has rigid body and is not static make it apply collision detection
				if (go.second->GetComponent<Physics2D>()->GetRigidBody() &&
					!go.second->GetComponent<Physics2D>()->GetStaticObj()) {

					coll = true;
				}
			}

			//Then check the collision

			while (true) {

				std::weak_ptr<GameObject> obj = CollisionHandler::GetInstance()->AABB(go.second->GetBoundingBox(), go.second->GetCollisionTags());

				if (obj.expired()) { break; }
				//First check if the object even has physics 

				if (coll) {
					if (obj.lock()->GetComponent<Physics2D>()) {
						if (obj.lock()->GetComponent<Physics2D>()->GetRigidBody()) {
							go.second->GetComponent<Physics2D>()->CollisionResponse(obj, deltaTime_);
						}
					}
				}

				//At the end do the manually programed collision responses for the game object
				go.second->CollisionResponse(obj);
			}
		}
	}

	for (auto go : sceneGUIObjects) {
		go.second->Update(deltaTime_);
	}

	prevDeltaTime = deltaTime_;
}

//TODO: Finish the depth draw system to allow for ease of drawing.
void SceneGraph::Draw(Camera* camera_)
{

	for (auto d : delayedUpdates) {
		d->Update(prevDeltaTime);
		d = nullptr;
	}
	delayedUpdates.clear();

	for (auto gl : sceneImages) {
		glUseProgram(gl.first);
		for (auto images : gl.second) {
			images->Draw();
		}
	}

	//Update GUI after objects to ignore depth
	
	//TODO: abstract the gui shader 
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
	//TODO: Delete Images
}

SceneGraph::SceneGraph() : isPaused(false), prevDeltaTime(0)
{
	delayedUpdates.reserve(10);
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}
