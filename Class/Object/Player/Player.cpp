#include "Player.h"

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

	// 移動速度
	vel_ = { 0.0f , 0.0f };
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

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


	// 移動速度を初期化する
	vel_ = { 0.0f , 0.0f };

	// Wキーで、上に移動する
	if (keys[DIK_W])
	{
		if (shape_.translate.y + shape_.scale.y < static_cast<float>(kScreenHeight - kCameraPosY))
		{
			vel_.y = 4.0f;
		}
	}

	// Sキーで、下に移動する
	if (keys[DIK_S])
	{
		if (shape_.translate.y - shape_.scale.y > static_cast<float>(-kCameraPosY))
		{
			vel_.y = -4.0f;
		}
	}

	// 動かす
	shape_.translate.y += vel_.y;
	LocalToScreen();
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
}