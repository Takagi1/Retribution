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
	inline bool Intersects(BoundingBox* box_) {
		//return (glm::abs((point.x + width / 2) - (box_->point.x + box_->width / 2)) * 2 < (width + box_->width)) &&
		//	(glm::abs((point.y + height / 2) - (box_->point.y + box_->height / 2)) * 2 < (height + box_->height));

		glm::vec2 minCorner = pos;
		glm::vec2 maxCorner = GetTransformedPoint(pos, dimentions);

		glm::vec2 otherMinCorner = box_->pos;
		glm::vec2 otherMaxCorner = GetTransformedPoint(box_->pos, box_->dimentions);

		if (minCorner.x <= otherMaxCorner.x && maxCorner.x >= otherMinCorner.x &&
			minCorner.y <= otherMaxCorner.y && maxCorner.y >= otherMinCorner.y) {
			return true;
		}

		return false;
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

private:
	inline glm::vec2 GetTransformedPoint(glm::vec2 position_, glm::vec2 dimentions_ = glm::vec2(0)) {
		return glm::vec2(position_.x, position_.y) + dimentions_;
	}
};


#endif // !BOUNDINGBOX_H
