#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Constant.h"
#include "./Class/Object/Player/Player.h"
#include "./Class/Object/Bullet/Bullet.h"
#include "./Class/Object/Enemy/Enemy.h"

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
					Enemy::coolTime = (rand() % 90);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*-------------------
		    図形を描画する
		-------------------*/

		// プレイヤー
		player->Draw();

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i]->Draw();
		}

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
