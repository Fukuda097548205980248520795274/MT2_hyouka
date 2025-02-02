#pragma once
#include "./Class/ObjectEllipse/ObjectEllipse.h"
#include "./Function/Spline/Spline.h"
#include "./Class/ObjectQuad/Player/Player.h"

class Enemy : public ObjectEllipse
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 出現させる
	/// </summary>
	void Arrival();

	/// <summary>
	/// 動かす
	/// </summary>
	void Move();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="enemy">敵</param>
	void Hit(Enemy* enemy);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	// 出現するクールタイム
	static int coolTime;

	// 出現しているかどうか（出現フラグ）
	int isArrival_;

	// 質量
	float mass_;

	// フレーム
	int frame_;

	// 制御点
	struct Vec2 p_[kPointNum];
};