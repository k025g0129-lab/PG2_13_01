#include "Enemy.h"
#include <Novice.h>


Enemy::Enemy() {
	isAlive = true;
	posX_ = 300.0f;
	posY_ = 400.0f;
	radius_ = 20;
	moveSpeed_ = 10.0f;
}

void Enemy::Move() {
	posX_ += moveSpeed_;

	if (posX_ <= 0.0f + radius_) {
		posX_ = 0.0f + radius_;
		moveSpeed_ *= -1;
	}

	if (posX_ >= 1280.0f - radius_) {
		posX_ = 1280.0f - radius_;
		moveSpeed_ *= -1;
	}

	Drow();
}

void Enemy::Drow() {
	Novice::DrawEllipse(
		static_cast<int>(posX_),
		static_cast<int>(posY_),
		radius_,
		radius_,
		0.0f, 0xFF0000FF,
		kFillModeSolid
	);
}

