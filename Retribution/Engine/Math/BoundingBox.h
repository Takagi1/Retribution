#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

//Pos is Top Left
struct BoundingBox {
public:

	//x = Width, y = Height
	glm::vec2 dimentions;

	glm::vec2 pos;

	glm::vec2 maxCorner;

	inline BoundingBox() {
		dimentions = glm::vec2();
		pos = glm::vec2();
		maxCorner = glm::vec2();
	}

	inline BoundingBox(glm::vec2 dimentions_, glm::vec2 pos_) {
		dimentions = dimentions_;
		pos = pos_;
		maxCorner = pos + dimentions;
	}

	//Is not in collision because Screen partition could not access it

	//General Idea is that boxs intersect if all min corners are smaller then max corners 
	inline bool Intersects(BoundingBox* box_) {

		glm::vec2 otherMaxCorner = box_->pos + box_->dimentions;


		//Checks to see if its intersecting with itself (would like a better way to prevent this)
		if (pos == box_->pos && maxCorner == otherMaxCorner) { return false; }

		if (pos.x <= otherMaxCorner.x && box_->pos.x <= maxCorner.x  &&
			pos.y <= otherMaxCorner.y && box_->pos.y <= maxCorner.y ) {
			return true;
		}
		
		return false;
	}

	//Use this to find the how far the box's are colliding to push them appart.
	//the x is negative if the box comes from the right and the y is negative if 
	//it comes from the top.

	//Explain:
	//Works with negative because max is always bigger thus getting the difference.

	inline glm::vec2 CollisionDepth(BoundingBox* box_) {

		glm::vec2 otherMaxCorner = box_->maxCorner;

		glm::vec2 depth;

	//First get which side is colliding

		//Coming from the right	
		float x1 = maxCorner.x - box_->pos.x;

		//Coming from the left
		float x2 = otherMaxCorner.x - pos.x;

		//Coming from the top
		float y1 = maxCorner.y - box_->pos.y;

		//Coming from the bottom
		float y2 = otherMaxCorner.y - pos.y;

		//TODO: improve this (push should be based on the direction the object is moving?) for now defualts too 2


		//Simplifed the if statement
		x1 < x2 ? depth.x = -x1 - 0.4f : depth.x = x2 + 0.4f;

		y1 < y2 ? depth.y = -y1 - 0.4f : depth.y = y2 + 0.4f;

		depth.x < depth.y ? depth.y = 0 : depth.x = 0;

		//Equal too

		/*if (x1 < x2) {
			depth.x = -x1 - 0.4f;
		}
		else {
			depth.x = x2 + 0.4f;
		}
		
		if (y1 < y2) {
			depth.y = -y1 - 0.4f;
		}
		else {
			depth.y = y2 + 0.4f;
		}

		if (depth.x < depth.y) {
			depth.y = 0;
		}
		else {
			depth.x = 0;
		}
		*/

		return depth;
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
