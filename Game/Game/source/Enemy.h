#pragma once
#include "appframe.h"
#include "ObjectBase.h"
#include "ApplicationMain.h"

constexpr auto MOVE_TIME = 1 * 60;
constexpr auto SAFE_CT = 5;


class Enemy : public ObjectBase {
public:

	// 敵のインスタンス
	static Enemy* EnInstance;
	static Enemy* GetEnInstance() { return (Enemy*)EnInstance; }

	Enemy();
	~Enemy();

	bool Initialize()override;
	bool Terminate();
	bool Process()override;
	bool Render(int type) override;

	// ゲッター
	int GetEnemyHP() { return hitPoint; }

	// セッター

protected:

	// 敵の情報
	int enemyModel;
	int hitPoint;

	// 移動関連
	bool isMove;
	VECTOR moveLengh;

	// ダメージ関連
	bool isHit;
	VECTOR plPos;
};