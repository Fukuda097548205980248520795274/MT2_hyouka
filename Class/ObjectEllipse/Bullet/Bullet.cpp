#include "Bullet.h"

// 弾
int Bullet::countID;


/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
{
	// ID
	id_ = 0;

	// 発射されているかどうか（発射フラグ）
	isShot_ = false;

	// 移動
	translate_ = { 0.0f , 0.0f };
	LocalToScreen();

	// 図形の半径
	radius_ = 8.0f;

	// 移動速度
	vel_ = { 0.0f , 0.0f };
}

/// <summary>
/// 発射する
/// </summary>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="velX">X軸の移動速度</param>
/// <param name="velY">Y軸の移動速度</param>
void Bullet::Shot(float posX , float posY , float velX , float velY)
{
	// 発射されている（発射フラグがtrueである）弾は、発射させない
	if (isShot_)
	{
		return;
	}

	// 発射する（発射フラグがtrueになる）
	isShot_ = true;

	// ID
	id_ = ++countID;

	// 位置
	translate_ = { posX , posY };
	LocalToScreen();

	// 移動速度
	vel_ = { velX , velY };
}

/// <summary>
/// 動かす
/// </summary>
void Bullet::Move()
{
	// 発射されていない（発射フラグがfalseである）弾は、動かさない
	if (isShot_ == false)
	{
		return;
	}


	// 動かす
	translate_.x += vel_.x;
	translate_.y += vel_.y;
	LocalToScreen();

	// 画面外に出たら、消える（発射フラグがfalseになる）
	if (translate_.x + radius_ < static_cast<float>(-kCameraPosX) || translate_.x - radius_ > static_cast<float>(kScreenWidth - kCameraPosX) ||
		translate_.y + radius_ < static_cast<float>(-kCameraPosY) || translate_.y - radius_ > static_cast<float>(kScreenHeight - kCameraPosY))
	{
		isShot_ = false;

		// IDを消す
		id_ = 0;
		--countID;
	}
}

/// <summary>
/// 描画する
/// </summary>
void Bullet::Draw()
{
	// 発射されていない（発射フラグがfalseである）ときは、描画しない
	if (isShot_ == false)
	{
		return;
	}

	Novice::DrawEllipse
	(
		static_cast<int>(pos_.x), static_cast<int>(pos_.y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f, 0xFF0000FF, kFillModeSolid
	);
}