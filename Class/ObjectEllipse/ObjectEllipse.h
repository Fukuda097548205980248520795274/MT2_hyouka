#pragma once
#include <Novice.h>
#include "Structure.h"
#include "Constant.h"
#include "./Function/Matrix/Matrix.h"

class ObjectEllipse
{
public:

	/// <summary>
	/// ローカル座標をスクリーン座標に変換する
	/// </summary>
	void LocalToScreen();

	// 移動
	struct Vec2 translate_;

	// 位置
	struct Vec2 pos_;

	// 加速度
	struct Vec2 acceleration_;

	// 移動速度
	struct Vec2 vel_;

	// 図形の半径
	float radius_;
};

