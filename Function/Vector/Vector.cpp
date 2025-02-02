#include "Vector.h"

/// <summary>
/// ベクトルを正規化する
/// </summary>
/// <param name="vec">ベクトル</param>
/// <returns>正規化したベクトルを返却する</returns>
struct Vec2 Normalize(struct Vec2 vec)
{
	float length = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));

	if (length != 0.0f)
	{
		vec.x = vec.x / length;
		vec.y = vec.y / length;
	}

	return vec;
}