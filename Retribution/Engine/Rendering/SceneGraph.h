#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "GameObject.h"
#include "../Math/CollisionHandler.h"
#include "GUI/GUIObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator =(const SceneGraph&) = delete;
	SceneGraph& operator =(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();
	void AddGameObject(GameObject* go_, std::string tag_ = "GameObject");
	void AddGUIObject(GUIObject* go, std::string tag_ = "GUI_Object");
	
	GameObject* GetGameObject(std::string tag_);
	GUIObject* GetGUIObject(std::string tag_);
	void Update(const float deltaTime_);
	void Draw(Camera* camera_);
	void OnDestroy();


private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::map<std::string, GameObject*> sceneGameObjects;
	static std::map<std::string, GUIObject*> sceneGUIObjects;

};
#endif // !SCENEGRAPH_H


