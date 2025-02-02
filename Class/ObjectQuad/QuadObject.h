#pragma once
#include <Novice.h>
#include "Structure.h"
#include "Constant.h"
#include "./Function/Matrix/Matrix.h"
#include "./Function/Vector/Vector.h"

class QuadObject
{
public:

	/// <summary>
	/// ローカル座標をスクリーン座標に変換する
	/// </summary>
	void LocalToScreen();

	// 図形
	struct Shape shape_;

	// 位置
	struct Pos2 pos_;

	// 加速度
	struct Vec2 acceleration_;

	// 移動速度
	struct Vec2 vel_;
};