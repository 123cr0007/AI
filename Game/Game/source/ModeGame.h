#pragma once

#include "appframe.h"
#include "Camera.h"
#include "Stage.h"
#include "ObjectManager.h"
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

	// �I�u�W�F�N�g�Ǘ�
	ObjectManager* Mobj;
}; 
