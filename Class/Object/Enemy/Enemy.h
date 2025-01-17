#pragma once
#include "./Class/Object/Object.h"

class Enemy : public Object
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// 出現させる
	/// </summary>
	void Arrival();

	/// <summary>
	/// 動かす
	/// </summary>
	void Move();

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

	// 加速度
	struct Vec2 acceleration_;
};