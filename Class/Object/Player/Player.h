#pragma once
#include "./Class/Object/Object.h"
#include "./Class/Object/Bullet/Bullet.h"

class Player : public Object
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

	// クールタイム
	int coolTime;
};