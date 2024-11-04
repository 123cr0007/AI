#pragma once
#include "appframe.h"
#include "ObjectBase.h"
#include "ApplicationMain.h"

constexpr auto MOVE_TIME = 1 * 60;
constexpr auto SAFE_CT = 5;


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

	// �Z�b�^�[

protected:

	// �G�̏��
	int enemyModel;
	int hitPoint;

	// �ړ��֘A
	bool isMove;
	VECTOR moveLengh;

	// �_���[�W�֘A
	bool isHit;
	VECTOR plPos;
};