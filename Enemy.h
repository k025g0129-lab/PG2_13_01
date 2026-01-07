#pragma once
class Enemy {

public:
	static int isAlive;
	float posX_;
	float posY_;
	float moveSpeed_;
	int radius_;

public:
	Enemy();
	void Move();
	void Drow();
};

