#include "Spline.h"

/// <summary>
/// 線形補間の点を作る
/// </summary>
/// <param name="start">開始位置</param>
/// <param name="end">終了位置</param>
/// <param name="t">パラメータ</param>
/// <returns>線形補間の点を返却する</returns>
struct Vec2 Leap(const struct Vec2& start, const struct Vec2& end ,float t)
{
	return { (1.0f - t) * start.x + t * end.x , (1.0f - t) * start.y + t * end.y };
}

/// <summary>
/// スプライン曲線上の点を作る
/// </summary>
/// <param name="p0">制御点0</param>
/// <param name="p1">制御点1</param>
/// <param name="p2">制御点2</param>
/// <param name="p3">制御点3</param>
/// <param name="t">パラメータ</param>
/// <returns>スプライン曲線上の点を返却する</returns>
struct Vec2 CatmullRom(const struct Vec2& p0, const struct Vec2& p1, const struct Vec2& p2, const struct Vec2& p3, float t)
{

	return
	{
		0.5f * ((-p0.x + (3 * p1.x) - (3 * p2.x) + p3.x) * powf(t,3) + ((2 * p0.x) - (5 * p1.x) + (4 * p2.x) - p3.x) * powf(t,2) +
		(-p0.x + p2.x) * t + (2 * p1.x))
		,
		0.5f * ((-p0.y + (3 * p1.y) - (3 * p2.y) + p3.y) * powf(t,3) + ((2 * p0.y) - (5 * p1.y) + (4 * p2.y) - p3.y) * powf(t,2) +
		(-p0.y + p2.y) * t + (2 * p1.y))
	};
}