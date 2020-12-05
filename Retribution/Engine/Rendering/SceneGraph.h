#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "GameObject.h"
#include "../Math/CollisionHandler.h"
#include "GUI/GUIObject.h"

class SpriteSurface;
class Image;
class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator =(const SceneGraph&) = delete;
	SceneGraph& operator =(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();

	void AddGameObject(std::shared_ptr<GameObject> go_, std::string name_ = "GameObject");
	std::weak_ptr<GameObject> GetGameObject(std::string tag_);
	bool RemoveGameObject(std::string name_);

	int AddImage(Image* im, unsigned int shaderProgram_);
	void RemoveImage(int loc_, unsigned int shaderProgram_);

	void Update(const float deltaTime_);
	void Draw(Camera* camera_);
	void OnDestroy();

	void AddGUIObject(GUIObject* go, std::string name_ = "GUI_Object"); //Use to add objects to gui
	GUIObject* GetGUIObject(std::string tag_);	//Use to get objects from GUI

	void AddDelayedUpdate(Component* comp);

	void Pause();

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::map<unsigned int, std::vector<Image*>> sceneImages;
	static std::map<std::string, std::shared_ptr<GameObject>> sceneGameObjects;

	//Used to store objects for GUI
	static std::map<std::string, GUIObject*> sceneGUIObjects;

	std::vector<Component*> delayedUpdates;

	std::vector<std::string> deletionLoc;
	float prevDeltaTime;

	bool isPaused;
};
#endif // !SCENEGRAPH_H


