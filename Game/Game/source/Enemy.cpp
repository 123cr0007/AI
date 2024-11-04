#include "Enemy.h"
#include "Stage.h"

Enemy* Enemy::EnInstance = nullptr;
Enemy::Enemy() {

	EnInstance = this;

	enemyModel = -1;
	hitPoint = 0;

	isMove = false;
	moveLengh = VGet(0, 0, 0);

	isHit = false;
	plPos = VGet(0,0,0);
}

Enemy::~Enemy() {
	MV1DeleteModel(enemyModel);
}

bool Enemy::Initialize() {

	// ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
	Load("res/UHilichurl/UHilichurl.mv1",1);
	hitPoint = 50;
	collision_r = 7.5f;
	return true;
}

bool Enemy::Terminate() {
	return true;
}

bool Enemy::Process() {

	return true;
}

bool Enemy::Render(int type) {

	type = 1;
	MV1SetPosition(handle, vPos);

	VECTOR vRot = VGet(0, 0, 0);
	vRot.y = atan2(vDir.x * - 1, vDir.z * -1);
	MV1SetRotationXYZ(handle, vRot);	

	// ƒ‚ƒfƒ‹‚Ì•`‰æ
	ObjectBase::Render(type);

#ifdef _DEBUG
	// “–‚½‚è”»’è‚Ì•`‰æ
	DrawCapsule3D(capsuleRow, capsuleTop, collision_r, 4, 4, GetColor(255, 0, 0), false);
#endif

	return true;
}