#pragma once

// カメラの位置
const int kCameraPosX = 60;
const int kCameraPosY = 60;

// 画面のサイズ
const int kScreenWidth = 1280;
const int kScreenHeight = 720;

// 敵が出現する位置
const float kEnemySummonX = kScreenWidth - kCameraPosX;
const float kEnemySummonY = 100.0f;

// 敵の最大サイズ
const int kEnemyMaxSize = 56;

// 重力
const float kGravity = -9.8f;

// 空気抵抗の係数
const float k = 0.4f;

// 動摩擦係数
const float kMiu = 0.6f;


/*   数   */

// 弾の数
const int kBulletNum = 64;

// 敵の数
const int kEnemyNum = 64;

// 制御点の数
const int kPointNum = 9;

// 分割数
const int divisions = 16;