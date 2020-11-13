#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

//Pos is Top Left
struct BoundingBox {
public:

	//x = Width, y = Height
	glm::vec2 dimentions;

	glm::vec2 pos;

	inline BoundingBox() {
		dimentions = glm::vec2();
		pos = glm::vec2();
	}

	inline BoundingBox(glm::vec2 dimentions_, glm::vec2 pos_) {
		dimentions = dimentions_;
		pos = pos_;
	}

	//Is not in collision because Screen partition could not access it

	//General Idea is that boxs intersect if all min corners are smaller then max corners 
	inline bool Intersects(BoundingBox* box_) {

		glm::vec2 minCorner = pos;
		glm::vec2 maxCorner = pos + dimentions;

		glm::vec2 otherMinCorner = box_->pos;
		glm::vec2 otherMaxCorner = box_->pos + box_->dimentions;


		//Checks to see if its intersecting with itself (would like a better way to prevent this)
		if (minCorner == otherMinCorner && maxCorner == otherMaxCorner) { return false; }

		if (minCorner.x <= otherMaxCorner.x && otherMinCorner.x <= maxCorner.x  &&
			minCorner.y <= otherMaxCorner.y && otherMinCorner.y <= maxCorner.y ) {
			return true;
		}
		
		return false;
	}

	//Use this to find the how far the box's are colliding to push them appart.
	//the x is negative if the box comes from the right and the y is negative if 
	//it comes from the top.

	//Explain:
	//after getting all points, x


	inline glm::vec2 CollisionDepth(BoundingBox* box_) {
		glm::vec2 maxCorner = pos + dimentions;

		glm::vec2 otherMinCorner = box_->pos;
		glm::vec2 otherMaxCorner = box_->pos + box_->dimentions;

		float depthX = 0, depthY = 0;

		//First get which side is colliding

		//TODO: test if this works with objects of different size


		//Coming from the right
		float x1 = maxCorner.x - otherMinCorner.x;

		//Coming from the left
		float x2 = otherMaxCorner.x - pos.x;


		//Coming from the top
		float y1 = maxCorner.y - otherMinCorner.y;

		//Coming from the bottom
		float y2 = otherMaxCorner.y - pos.y;

		//if the object is colliding up or from the right make depth return negative to push it down or left respectively
		bool right = false, up = false;

		//TODO: improve this (push should be based on the direction the object is moving?)
		if (x1 < x2) {
			right = true;
			depthX = x1;
		}
		else {
			depthX = x2;
		}
		
		if (y1 < y2) {
			up = true;
			depthY = y1;
		}
		else {
			depthY = y2;
		}

		if (depthX < depthY) {
			return glm::vec2((depthX + 0.4f) * (right ? -1 : 1), 0.0f);
		}
		else {
			return glm::vec2(0.0f, (depthY + 0.4f) * (up ? -1 : 1));
		}
	}

	inline bool ClickIntersect(glm::vec2 point_) {
		if (point_.x >= pos.x &&
			point_.y >= pos.y &&
			point_.x <= pos.x + dimentions.x &&
			point_.y <= pos.y + dimentions.y) {

			return true;
		}
		return false;
	}
};


#endif // !BOUNDINGBOX_H
