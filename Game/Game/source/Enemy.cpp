#include "Enemy.h"
#include "Stage.h"
#include "Astar.h"
#include "Player.h"

Enemy* Enemy::EnInstance = nullptr;
Enemy::Enemy() 
{

	EnInstance = this;

	enemyModel = -1;
	hitPoint = 0;

	isMove = false;
	isSetRoute = false;
	isGoal = false;
	nodeNum = 0;
	moveLengh = VGet(0, 0, 0);
	startX = 0;
	startY = 0;
	goalX = 5;
	goalY = 5;

	isHit = false;
	plPos = VGet(0,0,0);
}

Enemy::~Enemy() 
{
	MV1DeleteModel(enemyModel);
}

bool Enemy::Initialize() 
{

	// モデルの読み込み
	Load("res/UHilichurl/UHilichurl.mv1",1);
	hitPoint = 50;
	collision_r = 7.5f;

	if (Stage::GetStInstance()->GetStageInfo().size() > 0) {
	}
	return true;
}

bool Enemy::Terminate() 
{
	MV1DeleteModel(enemyModel);
	return true;
}

bool Enemy::Process() 
{
	// 目標位置の設定
	int tempRouteIndex = -1;
	if (!isMove) {
		for (auto&& aster : Astar::GetAsInstance()->GetRouteInfo()) {
			tempRouteIndex++;
			nodeNum = tempRouteIndex;
			if (!aster.isMoved) {
				Astar::GetAsInstance()->SetIsMoved(tempRouteIndex,true);
				isMove = true;
				nextPos = aster.goalPos;
				break;
			}
		}
	}

	// 移動
	if (isMove) {
		// 目標位置と現在位置の差分を使用して方向を計算
		float deltaX = nextPos.x - vPos.x;
		float deltaZ = nextPos.z - vPos.z;
		float dir = atan2f(deltaZ, deltaX);

		// プレイヤーの向きに反映する
		vDir.y = -(dir + 90.0f);

		// 移動値に速度と角度を代入
		vPos.x += MOVE_SPEED * cosf(dir);
		vPos.z += MOVE_SPEED * sinf(dir);

		// 目的地に近づいたらフラグを切り替える
		if (VSize(VSub(nextPos, vPos)) < 1.0f) 
		{
			isMove = false;
		}
	}

	// goalに到達したらフラグを切り替える
	int tempRouteNum = Astar::GetAsInstance()->GetRouteInfo().size() - 1;
	if (!isMove
		&& tempRouteNum > 0
		&& tempRouteIndex >= tempRouteNum)
	{
		isGoal = true;
		isSetRoute = false;
	}

	return true;
}

bool Enemy::Render(int type) 
{

	type = 1;
	MV1SetPosition(handle, vPos);
	MV1SetRotationXYZ(handle, vDir);

	// モデルの描画
	ObjectBase::Render(type);

#ifdef _DEBUG
	// 当たり判定の描画
	DrawCapsule3D(capsuleRow, capsuleTop, collision_r, 4, 4, GetColor(255, 0, 0), false);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "nodeNum:%d", nodeNum);
	DrawFormatString(0, 520, GetColor(255, 255, 255), "Size:%d", Astar::GetAsInstance()->GetRouteInfo().size());
#endif

	return true;
}