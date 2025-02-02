#include "Player.h"

// スコア
int Player::score = 0;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	// 図形
	shape_.scale = { 16.0f , 16.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 60.0f , 100.0f };

	// 位置
	pos_.local = { {-1.0f , 1.0f} , {1.0f , 1.0f} , {-1.0f , -1.0f} , {1.0f, -1.0f} };
	LocalToScreen();

	// 加速度
	acceleration_ = { 0.0f , 0.0f };

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// 弾
	for (int i = 0; i < kBulletNum; i++)
	{
		bullet[i] = new Bullet();
	}

	// 質量
	mass_ = 3.0f;

	// クールタイム
	coolTime_ = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// 弾
	for (int i = 0; i < kBulletNum; i++)
	{
		delete bullet[i];
	}
}

/// <summary>
/// 移動させる
/// </summary>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void Player::Move(const char* keys, const char* preKeys)
{
	// null を探す
	if (keys == nullptr || preKeys == nullptr)
	{
		return;
	}


	// Wキーで、上に移動する
	if (!preKeys[DIK_W] && keys[DIK_W])
	{
		vel_.y = 70.0f;
	}

	// Sキーで、下に移動する
	if (!preKeys[DIK_S] && keys[DIK_S])
	{
		vel_.y = -70.0f;
	}

	// 移動中に摩擦が生じる
	if (fabs(vel_.y) > 0.01f || fabs(vel_.y) < -0.01f)
	{
		// 動摩擦力の大きさ
		float magnitude = kMiu * (-mass_ * kGravity);

		// 摩擦力の方向
		float frictionDirectionY = 0.0f;

		if (vel_.y > 0.0f)
		{
			frictionDirectionY = -1.0f;
		}
		else if (vel_.y < 0.0f)
		{
			frictionDirectionY = 1.0f;
		}

		// 動摩擦力
		float frictionalForceY = magnitude * frictionDirectionY;

		// 加速度を求める
		acceleration_.y = frictionalForceY / mass_;

		if (fabs(acceleration_.y / 30.0f) > fabs(vel_.y))
		{
			acceleration_.y = vel_.y * 30.0f;
		}

		// 加速度を加算する
		vel_.y += acceleration_.y / 30.0f;

		// 動かす
		shape_.translate.y += vel_.y / 30.0f;


		// 画面外に出たら、移動速度が止まる
		if (shape_.translate.y + shape_.scale.y > static_cast<float>(kScreenHeight - kCameraPosY))
		{
			shape_.translate.y = static_cast<float>(kScreenHeight - kCameraPosY) - shape_.scale.y;
		}

		if (shape_.translate.y - shape_.scale.y < static_cast<float>(-kCameraPosY))
		{
			shape_.translate.y = static_cast<float>(-kCameraPosY) + shape_.scale.y;
		}
	}

	// 座標変換
	LocalToScreen();
}

/// <summary>
/// 発射させる
/// </summary>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void Player::Shot(const char* keys, const char* preKeys)
{
	// null を探す
	if (keys == nullptr || preKeys == nullptr)
	{
		return;
	}


	// クールタイムを進める
	if (coolTime_ > 0)
	{
		coolTime_--;
	}

	// スペースキーで、弾を発射する
	if (keys[DIK_SPACE])
	{
		// クールタイムが完了している
		if (coolTime_ <= 0)
		{
			for (int i = 0; i < kBulletNum; i++)
			{
				if (bullet[i]->id_ == 0)
				{
					// クールタイムを開始する
					coolTime_ = 10;

					bullet[i]->Shot(shape_.translate.x, shape_.translate.y, 8.0f, 0.0f);

					break;
				}
			}
		}
	}

	// 弾を動かす
	for (int i = 0; i < kBulletNum; i++)
	{
		bullet[i]->Move();
	}
}

/// <summary>
/// 描画する
/// </summary>
void Player::Draw()
{
	// 白い画像
	int ghWhite = Novice::LoadTexture("./NoviceResources/white1x1.png");

	Novice::DrawQuad
	(
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(pos_.screen.rightTop.x), static_cast<int>(pos_.screen.rightTop.y),
		static_cast<int>(pos_.screen.leftBottom.x), static_cast<int>(pos_.screen.leftBottom .y),
		static_cast<int>(pos_.screen.rightBottom.x), static_cast<int>(pos_.screen.rightBottom.y),
		0,0,1,1,ghWhite,0xFF0000FF
	);

	// 弾
	for (int i = 0; i < kBulletNum; i++)
	{
		bullet[i]->Draw();
	}
}