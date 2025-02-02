#pragma once
#include "./Class/ObjectQuad/QuadObject.h"
#include "./Class/ObjectEllipse/Bullet/Bullet.h"

class Player : public QuadObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 移動させる
	/// </summary>
	/// <param name="keys">キー</param>
	/// <param name="preKeys">前のキー</param>
	void Move(const char* keys, const char* preKeys);

	/// <summary>
	/// 発射させる
	/// </summary>
	/// <param name="keys">キー</param>
	/// <param name="preKeys">前のキー</param>
	void Shot(const char* keys, const char* preKeys);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	// 弾
	Bullet* bullet[kBulletNum];

	// 質量
	float mass_;

	// クールタイム
	int coolTime_;

	// スコア
	static int score;
};