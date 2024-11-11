#pragma once

#include "appframe.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Stage.h"
#include "Obstacle.h"
#include "UI.h"
#include "Astar.h"
#include <string>

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGame();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	// カメラ
	Camera* Cam;

	// ステージ
	Stage* stage;

	// 障害物
	Obstacle* obst;

	// オブジェクト管理
	ObjectManager* Mobj;

	// UI
	UI* ui;

	// A*
	Astar* astar;
}; 
