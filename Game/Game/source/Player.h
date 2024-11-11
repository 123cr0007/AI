#pragma once
#include "ObjectBase.h"
#include "appframe.h"
#include "ApplicationMain.h"

// プレイヤーの速度
constexpr auto PLAYER_SPEED = 3.0f;

class Player : public ObjectBase {
public:

	// インスタンス
	static Player* PlInstance;
	static Player* GetPlInstance() { return (Player*)PlInstance; }

	Player();
	~Player();

	bool Initialize()override;
	bool Terminate();
	bool Process()override;
	bool Render(int type) override;

	VECTOR Operate();

	// ゲッター
	bool GetIsAttack() { return isAttack; }

	// セッター
	void SetIsAttack(bool flag) { 
		isAttack = flag; }

protected:

	int graphX;
	int graphY;

	bool isAttack;
};