#pragma once

#include "util/Vector.h"

class Camera {
public:
	Camera(const Vec3f &position, const Vec3f &direction, const Vec3f &up, float nearPlane) : nearPlane(nearPlane) {
		setPosition(position);
		setDirection(direction, false);
		setUp(up, true);
	}
	
	Vec3f getPointLookedAt(float xOffset, float yOffset) const {
		const Vec3f screenOffsetVector = direction * nearPlane;
		const Vec3f xOffsetVector = right * xOffset;
		const Vec3f yOffsetVector = up * yOffset;
		Vec3f result{ position };
		return result.add(screenOffsetVector).add(xOffsetVector).add(yOffsetVector);
	}

	void calculateRight() {
		right = direction.cross(up).normalize();
	}

	void setPosition(const Vec3f &arg) { 
		this->position = arg; 
	}

	void setDirection(const Vec3f &arg, bool calculateRight = true) {
		this->direction = arg;
		this->direction.normalize();
		if (calculateRight) this->calculateRight();
	}

	void setUp(const Vec3f &arg, bool calculateRight = true) {
		this->up = arg;
		this->up.normalize();
		if (calculateRight) this->calculateRight();
	}

	const Vec3f &getPosition() const { return position; }
	const Vec3f &getDirection() const { return direction; }
	const Vec3f &getUp() const { return up; }
	const Vec3f &getRight() const { return right; }
	float getNearPlane() const { return nearPlane; }

private:
	float nearPlane;
	Vec3f position;
	Vec3f direction;
	Vec3f up;
	Vec3f right;
};