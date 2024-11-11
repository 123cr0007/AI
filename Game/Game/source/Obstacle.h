#pragma once
#include "appframe.h"
#include "ApplicationMain.h"
#include "Stage.h"

constexpr auto OBSTACLE_NUM = 15;			// お邪魔の数

class Obstacle {
public:

	// お邪魔のインスタンス
	static Obstacle* ObstInstance;
	static Obstacle* GetObstInstance() { return (Obstacle*)ObstInstance; }

	Obstacle();
	~Obstacle();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	bool CheckSafety();		// お邪魔の安全な場所をチェックする
	bool SetObstacle();	// お邪魔の位置を設定する

	// ゲッター

	// セッター


protected:

	int tempModel;
	int obstModel[OBSTACLE_NUM];
	int obstCol[OBSTACLE_NUM];

	//int obstMap[ST_DIVNUM][ST_DIVNUM];

	bool setUpFlag;
};