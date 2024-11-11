#pragma once
#include "appframe.h"
#include "ObjectBase.h"
#include "ApplicationMain.h"

constexpr auto MOVE_SPEED = 1;
constexpr auto SAFE_CT = 5;
constexpr auto ROUTE_MAX = 100;


class Enemy : public ObjectBase {
public:

	// �G�̃C���X�^���X
	static Enemy* EnInstance;
	static Enemy* GetEnInstance() { return (Enemy*)EnInstance; }

	Enemy();
	~Enemy();

	bool Initialize()override;
	bool Terminate();
	bool Process()override;
	bool Render(int type) override;

	// �Q�b�^�[
	int GetEnemyHP() { return hitPoint; }
	bool GetIsMove() { return isMove; }
	bool GetIsSetRoute() { return isSetRoute; }
	int GetStartX() { return startX; }
	int GetStartY() { return startY; }
	int GetGoalX() { return goalX; }
	int GetGoalY() { return goalY; }

	// �Z�b�^�[
	void SetIsMove(bool trg) { isMove = trg; }
	void SetIsSetRoute(bool trg) { isSetRoute = trg; }

protected:

	// �G�̏��
	int enemyModel;
	int hitPoint;

	// �ړ��֘A
	bool isMove;
	bool isSetRoute;
	bool isGoal;
	int nodeNum;
	VECTOR moveLengh;
	VECTOR nextPos;
	int startX, startY;
	int goalX, goalY;

	// �_���[�W�֘A
	bool isHit;
	VECTOR plPos;
};