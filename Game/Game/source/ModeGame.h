#pragma once

#include "appframe.h"
#include "Camera.h"
#include "Stage.h"
#include "ObjectManager.h"
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

	// オブジェクト管理
	ObjectManager* Mobj;
}; 
