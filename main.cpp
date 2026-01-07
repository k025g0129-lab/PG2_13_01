#include <Novice.h>
#include "Enemy.h"
#define _USE_MATH_DEFINES
#include <math.h>



const char kWindowTitle[] = "LC1B_19_シンモトキョウスケ_タイトル";


struct Vector2 {
	float x;
	float y;
};

struct Player {
	Vector2 pos;
	float moveSpeed;
};

struct Bullet {
	Vector2 pos;
	float moveSpeed;
	int isShot;
	float radius;
};

int Enemy::isAlive;

int B2EContact(Bullet bullet, Enemy* enemy) {
	float e2bXDistance = static_cast<float>(fabs(enemy->posX_ - bullet.pos.x) * fabs(enemy->posX_ - bullet.pos.x));
	float e2bYDistance = static_cast<float>(fabs(enemy->posY_ - bullet.pos.y) * fabs(enemy->posY_ - bullet.pos.y));
	float e2bRDistance = static_cast<float>((bullet.radius + enemy->radius_) * (bullet.radius + enemy->radius_));
	if (e2bRDistance >= e2bXDistance + e2bYDistance) {

		return true;
	} else {
		return false;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Enemy* enemy1 = new Enemy;
	Enemy* enemy2 = new Enemy;

	enemy2->posX_ += 100.0f;
	enemy2->posY_ += 100.0f;

	//========================================================================================
	//プレイヤー
	//========================================================================================	
	Player player;
	player.pos.x = 640.0f;
	player.pos.y = 360.0f;
	player.moveSpeed = 5.0f;

	//========================================================================================
	//弾
	//========================================================================================	
	Bullet bullet;
	bullet.pos.x = -640.0f;
	bullet.pos.y = -360.0f;
	bullet.moveSpeed = 5.0f;
	bullet.radius = 5.0f;
	bullet.isShot = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		//========================================================================================
		//プレイヤー
		//========================================================================================	
		if (keys[DIK_W]) {
			player.pos.y -= player.moveSpeed;
		}

		if (keys[DIK_S]) {
			player.pos.y += player.moveSpeed;
		}

		if (keys[DIK_A]) {
			player.pos.x -= player.moveSpeed;
		}

		if (keys[DIK_D]) {
			player.pos.x += player.moveSpeed;
		
		}
		
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			bullet.isShot = true;
			bullet.pos = player.pos;
		
		}
		//========================================================================================
		//弾
		//========================================================================================	
		if (bullet.isShot) {
			bullet.pos.y -= bullet.moveSpeed;

			if (bullet.pos.y <= 0.0f) {
				bullet.isShot = false;
				bullet.pos = {-100.0f-100.0f};
			}
		}


		//========================================================================================
		//敵
		//========================================================================================	
		if (Enemy::isAlive) {
			enemy1->Move();
			enemy2->Move();

		}

		if (keys[DIK_R]) {
			Enemy::isAlive = true;
		}

		//========================================================================================
		//当たり判定
		//========================================================================================	
		
		if (B2EContact(bullet, enemy1)) {
			bullet.pos = {-100.0f,-100.0f};
			Enemy::isAlive = false;
		}

		if (B2EContact(bullet, enemy2)) {
			bullet.pos = { -100.0f,-100.0f };
			Enemy::isAlive = false;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(
			static_cast<int>(bullet.pos.x),
			static_cast<int>(bullet.pos.y),
			static_cast<int>(bullet.radius),
			static_cast<int>(bullet.radius),
			0.0f, 0xFFFFFFFF,
			kFillModeSolid

		);

		Novice::DrawEllipse(
			static_cast<int>(player.pos.x),
			static_cast<int>(player.pos.y),
			20,
			20,
			0.0f, 0xFFFFFFFF,
			kFillModeSolid

		);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
