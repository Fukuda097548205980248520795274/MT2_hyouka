#include "QuadObject.h"

/// <summary>
/// ローカル座標をスクリーン座標に変換する
/// </summary>
void QuadObject::LocalToScreen()
{
	// 全てを結合した行列
	struct Matrix3x3 wvpVpMatrix;

	wvpVpMatrix = Multiply(MakeWorldMatrix(shape_.scale, shape_.theta, shape_.translate),
		MakeInverseMatrix(MakeWorldMatrix({ 1.0f , 1.0f }, 0.0f, { 0.0f , 0.0f })));

	wvpVpMatrix = Multiply(wvpVpMatrix, MakeOrthoMatrix(static_cast<float>(-kCameraPosX), static_cast<float>(kScreenHeight - kCameraPosY),
		static_cast<float>(kScreenWidth - kCameraPosX), static_cast<float>(-kCameraPosY)));

	wvpVpMatrix = Multiply(wvpVpMatrix, MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kScreenWidth), static_cast<float>(kScreenHeight)));

	pos_.screen.leftTop = Transform(pos_.local.leftTop, wvpVpMatrix);
	pos_.screen.rightTop = Transform(pos_.local.rightTop, wvpVpMatrix);
	pos_.screen.leftBottom = Transform(pos_.local.leftBottom, wvpVpMatrix);
	pos_.screen.rightBottom = Transform(pos_.local.rightBottom, wvpVpMatrix);
}