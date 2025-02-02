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

	// 移動
	translate_ = { 0.0f , 0.0f };
	LocalToScreen();

	// 移動速度
	vel_ = { 0.0f , 0.0f };

	// 質量
	mass_ = 3.0f;

	// 加速度
	acceleration_ = { 0.0f , 0.0f };

	// 制御点
	for (int i = 0; i < kPointNum; i++)
	{
		p_[i] = { 0.0f , 0.0f };
	}

	// フレーム
	frame_ = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	
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

	// 大きさ
	radius_ = static_cast<float>(rand() % kEnemyMaxSize) + 8.0f;
	

	// 位置
	translate_ = { kEnemySummonX - radius_ , static_cast<float>(rand() % 500) + kEnemySummonY };
	LocalToScreen();

	// 移動速度
	vel_ = { -6.0f , 0.0f };

	// フレーム
	frame_ = 0;


	// 制御点
	for (int i = 0; i < kPointNum; i++)
	{
		p_[i] = pos_;
	}
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
	if (translate_.y + vel_.y - radius_ < 0.0f)
	{
		vel_.y *= -(1.0f - (radius_ / 80.0f));
	}

	// 動かす
	translate_.x += vel_.x;
	translate_.y += vel_.y;
	LocalToScreen();

	// 画面の左右を越えたら、消える（出現フラグがfalseになる）
	if (translate_.x + radius_ < static_cast<float>(-kCameraPosX) || translate_.x - radius_ > static_cast<float>(kScreenWidth - kCameraPosX))
	{
		isArrival_ = false;

		// スコアを減点する
		Player::score -= 100;
	}


	/*---------------
	    軌跡を作る
	---------------*/

	// フレームを進める
	frame_++;

	// 60フレームで、初期化する
	if (frame_ >= 5)
	{
		frame_ = 0;
	}

	// 制御点の位置を更新する
	if (frame_ == 0)
	{
		for (int i = kPointNum - 1; i >= 0; i--)
		{
			if (i != 0)
			{
				p_[i] = p_[i - 1];
			}
			else
			{
				p_[i] = pos_;
			}
		}
	}
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="enemy"></param>
void Enemy::Hit(Enemy* enemy)
{
	// null を探す
	if (enemy == nullptr)
	{
		return;
	}

	// 出現していない（出現フラグがfalseである）場合は、処理をしない
	if (isArrival_ == false || enemy->isArrival_ == false)
	{
		return;
	}


	// ぶつかったら、反発する
	if (powf(radius_ + enemy->radius_, 2) >=
		powf(enemy->translate_.x - translate_.x, 2) + powf(enemy->translate_.y - translate_.y, 2))
	{
		// 敵のベクトル
		struct Vec2 vec = { enemy->translate_.x - translate_.x , enemy->translate_.y - translate_.y };
		vec = Normalize(vec);

		vel_.x = -(1.0f - (radius_ / 80.0f)) * (vec.x * 10.0f);
		vel_.y = -(1.0f - (radius_ / 80.0f)) * (vec.y * 10.0f);

		// 動かす
		translate_.x += vel_.x;
		translate_.y += vel_.y;
		LocalToScreen();


		// もう一体の敵のベクトル
		struct Vec2 enemyVec = { translate_.x - enemy->translate_.x , translate_.y - enemy->translate_.y };
		enemyVec = Normalize(enemyVec);

		enemy->vel_.x = -(1.0f - (enemy->radius_ / 80.0f)) * (enemyVec.x * 10.0f);
		enemy->vel_.y = -(1.0f - (enemy->radius_ / 80.0f)) * (enemyVec.y * 10.0f);

		// 動かす
		enemy->translate_.x += enemy->vel_.x;
		enemy->translate_.y += enemy->vel_.y;
		LocalToScreen();
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
	(static_cast<int>(pos_.x), static_cast<int>(pos_.y),static_cast<int>(radius_), static_cast<int>(radius_),0.0f, 0xFFFFFFFF, kFillModeSolid);

	// スプライン曲線
	for (int index = 0; index < divisions; index++)
	{
		// パラメータ
		float t0 = static_cast<float>(index) / static_cast<float>(divisions);
		float t1 = static_cast<float>(index + 1) / static_cast<float>(divisions);

		for (int i = 0; i < kPointNum - 1; i++)
		{
			if (i == 0)
			{
				struct Vec2 start = CatmullRom(p_[i], p_[i], p_[i + 1], p_[i + 2], t0);
				struct Vec2 end = CatmullRom(p_[i], p_[i], p_[i + 1], p_[i + 2], t1);

				Novice::DrawLine
				(
					static_cast<int>(start.x), static_cast<int>(start.y),
					static_cast<int>(end.x), static_cast<int>(end.y),
					0xFF0000FF
				);
			}
			else if(i == kPointNum - 2)
			{
				struct Vec2 start = CatmullRom(p_[i -1], p_[i], p_[i + 1], p_[i + 1], t0);
				struct Vec2 end = CatmullRom(p_[i - 1], p_[i], p_[i + 1], p_[i + 1], t1);

				Novice::DrawLine
				(
					static_cast<int>(start.x), static_cast<int>(start.y),
					static_cast<int>(end.x), static_cast<int>(end.y),
					0xFF0000FF
				);
			}
			else
			{
				struct Vec2 start = CatmullRom(p_[i - 1], p_[i], p_[i + 1], p_[i + 2], t0);
				struct Vec2 end = CatmullRom(p_[i - 1], p_[i], p_[i + 1], p_[i + 2], t1);

				Novice::DrawLine
				(
					static_cast<int>(start.x), static_cast<int>(start.y),
					static_cast<int>(end.x), static_cast<int>(end.y),
					0xFF0000FF
				);
			}
		}
	}
}