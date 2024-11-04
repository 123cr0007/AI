#pragma once
#include "DxLib.h"
#include <cmath>
#include "../Collision/Collision.h"

// 1ボーンIK
void OneBoneIK(VECTOR targetPos, VECTOR& bonePos, VECTOR& boneDir);

// 2ボーンIK
void TwoBoneIK(VECTOR targetPos, VECTOR& joint1Pos, VECTOR& joint1Dir,
	VECTOR& joint2Pos, VECTOR& joint2Dir, float bone1Length, float bone2Length);