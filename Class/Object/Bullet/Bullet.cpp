#include "Bullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
{
	// ID
	id_ = 0;

	// 発射されているかどうか（発射フラグ）
	isShot_ = false;

	// 図形
	shape_.scale = { 4.0f , 4.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 0.0f , 0.0f };

	// 位置
	pos_.local = { {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} };
	LocalToScreen();

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
	shape_.translate = { posX , posY };
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
	shape_.translate.x += vel_.x;
	shape_.translate.y += vel_.y;
	LocalToScreen();

	// 画面外に出たら、消える（発射フラグがfalseになる）
	if (shape_.translate.x + shape_.scale.x < static_cast<float>(-kCameraPosX) ||
		shape_.translate.x - shape_.scale.x > static_cast<float>(kScreenWidth - kCameraPosX) ||
		shape_.translate.y + shape_.scale.y < static_cast<float>(-kCameraPosY) ||
		shape_.translate.y - shape_.scale.y > static_cast<float>(kScreenHeight - kCameraPosY))
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
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(shape_.scale.x), static_cast<int>(shape_.scale.y),
		0.0f, 0xFF0000FF, kFillModeSolid
	);
}