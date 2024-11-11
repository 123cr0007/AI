#pragma once

#include "appframe.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Stage.h"
#include "Obstacle.h"
#include "UI.h"
#include "Astar.h"
#include <string>

// ���[�h
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

	// �J����
	Camera* Cam;

	// �X�e�[�W
	Stage* stage;

	// ��Q��
	Obstacle* obst;

	// �I�u�W�F�N�g�Ǘ�
	ObjectManager* Mobj;

	// UI
	UI* ui;

	// A*
	Astar* astar;
}; 
