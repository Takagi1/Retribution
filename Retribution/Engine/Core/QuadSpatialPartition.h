#ifndef QUADSPATIALPARTITION_H
#define QUADSPATIALPARTITION_H

#include "../Rendering/GameObject.h"

#define CHILDREN_NUMBER 4

enum class QuadChildren {
	QUAD_TL,
	QUAD_BL,
	QUAD_BR,
	QUAD_TR
};

class QuadNode {
public:
	QuadNode(glm::vec2 position_, float size_, QuadNode* parent_);
	~QuadNode();

	void OnDestroy();
	void Quadify(int depth_);

	QuadNode* GetParent();
	QuadNode* GetChild(QuadChildren childPosition_);
	void AddCollisionObject(std::weak_ptr<GameObject> obj_);
	void RemoveCollisionObject(int loc_);
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;

private:

	friend class QuadSpatialPartition;
	BoundingBox* quadBounds;
	QuadNode* parent;
	QuadNode* children[CHILDREN_NUMBER];
	std::vector<std::weak_ptr<GameObject>> objectList;
	float size;
	static int childNum;
};

class QuadSpatialPartition
{
public:

	QuadSpatialPartition(float worldSize_);
	~QuadSpatialPartition();
	void OnDestroy();
	void AddObject(std::weak_ptr<GameObject> obj_);

	std::weak_ptr<GameObject> GetCollision(BoundingBox box_, std::vector<std::string> tags_);
	std::vector<std::weak_ptr<GameObject>> GetCollisionAll(BoundingBox box, std::vector<std::string> tags_);
	std::weak_ptr<GameObject> GetCollision(glm::vec2 point_);
	//GameObject* GetCollision(Ray ray_);

	void RemoveObject(BoundingBox box_, std::string name_);

private:

	QuadNode* root;
	std::vector<QuadNode*> objIntersectionList;
	void AddObjectToCell(QuadNode* cell_, std::weak_ptr<GameObject> obj_);

	void PrepareCollisionQuery(QuadNode* cell_, BoundingBox box_);

	void PrepareCollisionQuery(QuadNode* cell_, glm::vec2 point_);
};
#endif // !QUADSPATIALPARTITION_H