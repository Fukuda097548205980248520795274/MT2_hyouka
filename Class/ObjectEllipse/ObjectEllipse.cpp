#include "ObjectEllipse.h"

/// <summary>
/// ローカル座標をスクリーン座標に変換する
/// </summary>
void ObjectEllipse::LocalToScreen()
{
	// 全てを結合した行列
	struct Matrix3x3 wvpVpMatrix;

	wvpVpMatrix = Multiply(MakeWorldMatrix({0.0f , 0.0f}, 0.0f, translate_),
		MakeInverseMatrix(MakeWorldMatrix({ 1.0f , 1.0f }, 0.0f, { 0.0f , 0.0f })));

	wvpVpMatrix = Multiply(wvpVpMatrix, MakeOrthoMatrix(static_cast<float>(-kCameraPosX), static_cast<float>(kScreenHeight - kCameraPosY),
		static_cast<float>(kScreenWidth - kCameraPosX), static_cast<float>(-kCameraPosY)));

	wvpVpMatrix = Multiply(wvpVpMatrix, MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kScreenWidth), static_cast<float>(kScreenHeight)));

	pos_ = Transform({ 0.0f , 0.0f }, wvpVpMatrix);
}