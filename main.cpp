#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Constant.h"
#include "./Class/ObjectQuad/Player/Player.h"
#include "./Class/ObjectEllipse/Bullet/Bullet.h"
#include "./Class/ObjectEllipse/Enemy/Enemy.h"

const char kWindowTitle[] = "LC1C_20_フクダソウワ_評価課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kScreenWidth, kScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 乱数
	unsigned int currentTimer = static_cast<unsigned int>(time(nullptr));
	srand(currentTimer);


	/*---------------
	    変数を作る
	---------------*/

	// プレイヤー
	Player* player = new Player();

	// 敵
	Enemy* enemy[kEnemyNum];
	for (int i = 0; i < kEnemyNum; i++)
	{
		enemy[i] = new Enemy();
	}


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

		// プレイヤーの操作
		player->Move(keys, preKeys);
		player->Shot(keys, preKeys);


		/*-------------
		    敵の処理
		-------------*/

		// クールタイムを進める
		if (Enemy::coolTime > 0)
		{
			Enemy::coolTime--;
		}

		// 敵を出現させる
		if (Enemy::coolTime <= 0)
		{
			for (int i = 0; i < kEnemyNum; i++)
			{
				if (enemy[i]->isArrival_ == false)
				{
					// クールタイムを開始する
					Enemy::coolTime = 20 + rand() % 30;

					enemy[i]->Arrival();

					break;
				}
			}
		}

		// 敵を動かす
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i]->Move();
		}


		/*---------------
		    当たり判定
		---------------*/

		// 弾（発射フラグがtrue） と 敵（出現フラグがtrue）
		for (int i = 0; i < kBulletNum; i++)
		{
			if (player->bullet[i]->isShot_)
			{
				for (int j = 0; j < kEnemyNum; j++)
				{
					if (enemy[j]->isArrival_)
					{
						// ぶつかったら、敵と弾が消える（発射、出現フラグがfalseになる）
						if (powf(player->bullet[i]->radius_ + enemy[j]->radius_, 2) >=
							powf(enemy[j]->translate_.x - player->bullet[i]->translate_.x, 2) +
							powf(enemy[j]->translate_.y - player->bullet[i]->translate_.y, 2))
						{
							player->bullet[i]->isShot_ = false;
							player->bullet[i]->id_ = 0;
							Bullet::countID--;

							enemy[j]->isArrival_ = false;

							// スコアに加点する
							Player::score += 100;
						}
					}
				}
			}
		}

		for (int i = 0; i < kEnemyNum; i++)
		{
			for (int j = 0; j < kEnemyNum; j++)
			{
				if (i != j)
				{
					enemy[i]->Hit(enemy[j]);
				}
			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*-------------------
		    図形を描画する
		-------------------*/

		// カメラの軸
		Novice::DrawLine(0, kScreenHeight - kCameraPosY, kScreenWidth, kScreenHeight - kCameraPosY, 0xFF0000FF);
		Novice::DrawLine(kCameraPosX, 0, kCameraPosX, kScreenHeight, 0x00FF00FF);

		// プレイヤー
		player->Draw();

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i]->Draw();
		}

		// スコア
		Novice::ScreenPrintf(8 , 8 , "Score : %d" , Player::score);

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


	/*--------------------------
	    インスタンスを削除する
	--------------------------*/

	// プレイヤー
	delete player;

	// 敵
	for (int i = 0; i < kEnemyNum; i++)
	{
		delete enemy[i];
	}


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
