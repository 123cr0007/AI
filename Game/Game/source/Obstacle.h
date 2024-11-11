#pragma once
#include "appframe.h"
#include "ApplicationMain.h"
#include "Stage.h"

constexpr auto OBSTACLE_NUM = 15;			// ���ז��̐�

class Obstacle {
public:

	// ���ז��̃C���X�^���X
	static Obstacle* ObstInstance;
	static Obstacle* GetObstInstance() { return (Obstacle*)ObstInstance; }

	Obstacle();
	~Obstacle();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	bool CheckSafety();		// ���ז��̈��S�ȏꏊ���`�F�b�N����
	bool SetObstacle();	// ���ז��̈ʒu��ݒ肷��

	// �Q�b�^�[

	// �Z�b�^�[


protected:

	int tempModel;
	int obstModel[OBSTACLE_NUM];
	int obstCol[OBSTACLE_NUM];

	//int obstMap[ST_DIVNUM][ST_DIVNUM];

	bool setUpFlag;
};