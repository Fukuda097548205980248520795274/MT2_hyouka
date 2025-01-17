#include "Enemy.h"

// 出現するクールタイム
int Enemy::coolTime = 0;


/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	// 出現しているかどうか（出現フラグ）
	isArrival_ = false;

	// 図形
	shape_.scale = { 0.0f , 0.0f };
	shape_.theta = 0.0f;
	shape_.translate = { 0.0f , 0.0f };

	// 位置
	pos_.local = { {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} };
	LocalToScreen();

	// 移動速度
	vel_ = { 6.0f , 0.0f };

	// 質量
	mass_ = 3.0f;

	// 加速度
	acceleration_ = { 0.0f , 0.0f };
}

/// <summary>
/// 出現させる
/// </summary>
void Enemy::Arrival()
{
	// 出現している（出現フラグがtrueである）敵は、処理を中断する
	if (isArrival_)
	{
		return;
	}


	// 出現させる（出現フラグをtrueにする）
	isArrival_ = true;


	/*   図形   */

	// 位置
	shape_.translate = { kEnemySummonX , static_cast<float>(rand() % 500) + kEnemySummonY };

	// 大きさ
	float radius = static_cast<float>(rand() % kEnemyMaxSize) + 8.0f;
	shape_.scale = { radius , radius };

	// 座標変換
	LocalToScreen();

	// 移動速度
	vel_ = { -6.0f , 0.0f };
}

/// <summary>
/// 動かす
/// </summary>
void Enemy::Move()
{
	// 出現していない（出現フラグがfalseである）敵は、動かさない
	if (isArrival_ == false)
	{
		return;
	}


	/*-------------
	    空気抵抗
	-------------*/

	// 空気抵抗
	struct Vec2 airResistance = { k * -vel_.x , k * -vel_.y };

	// 空気抵抗の加速度
	struct Vec2 airResistanceAcceleration = { airResistance.x / mass_ , airResistance.y / mass_ };

	// 空気抵抗を足した加速度を求める
	acceleration_ = { airResistanceAcceleration.x , kGravity + airResistanceAcceleration.y };

	// 加速度を加算する
	vel_.x += acceleration_.x / 60.0f;
	vel_.y += acceleration_.y / 60.0f;


	// 地面についたら、反発する
	if (shape_.translate.y + vel_.y - shape_.scale.y < 0.0f)
	{
		vel_.y *= -(1.0f - (shape_.scale.y / static_cast<float>(kEnemyMaxSize * 2)));
	}

	// 動かす
	shape_.translate.x += vel_.x;
	shape_.translate.y += vel_.y;
	LocalToScreen();

	// 画面右端を越えたら、消える（出現フラグがfalseになる）
	if (shape_.translate.x + shape_.scale.x < static_cast<float>(-kCameraPosX))
	{
		isArrival_ = false;
	}
}

/// <summary>
/// 描画する
/// </summary>
void Enemy::Draw()
{
	// 出現していない（出現フラグがfalseである）敵は、描画しない
	if (isArrival_ == false)
	{
		return;
	}

	Novice::DrawEllipse
	(
		static_cast<int>(pos_.screen.leftTop.x), static_cast<int>(pos_.screen.leftTop.y),
		static_cast<int>(shape_.scale.x), static_cast<int>(shape_.scale.y),
		0.0f, 0xFFFFFFFF, kFillModeSolid
	);
}