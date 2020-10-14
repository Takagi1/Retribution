#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "GameObject.h"
#include "../Math/CollisionHandler.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator =(const SceneGraph&) = delete;
	SceneGraph& operator =(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void AddGameObject(std::shared_ptr<GameObject> go_, std::string name_ = "GameObject");
	bool RemoveGameObject(std::string name_);


	std::weak_ptr<GameObject> GetGameObject(std::string tag_);

	void Update(const float deltaTime_);
	void Draw(Camera* camera_);
	void OnDestroy();

	//Use to add objects to gui
	void AddGUIObject(GameObject* go, std::string name_ = "GUI_Object");

	//Use to get objects from GUI
	GameObject* GetGUIObject(std::string tag_);

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::map<std::string, std::shared_ptr<GameObject>> sceneGameObjects;

	//Used to store objects for GUI
	static std::map<std::string, GameObject*> sceneGUIObjects;


};
#endif // !SCENEGRAPH_H


