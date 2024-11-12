
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameClear.h"

ModeGame::ModeGame() {

	// �ϐ��̏�����
	Cam = nullptr;
	stage = nullptr;
	obst = nullptr;
	Mobj = nullptr;
	ui = nullptr;
	astar = nullptr;
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// �J�������`
	Cam = new Camera();
	Cam->Initialize();

	// �X�e�[�W���`
	stage = new Stage();
	stage->Initialize();

	// ��Q�����`
	obst = new Obstacle();
	obst->Initialize();

	// �I�u�W�F�N�g��`
	Mobj = new ObjectManager();
	Mobj->Initialize();

	// UI��`
	ui = new UI();
	ui->Initialize();

	// A*�A���S���Y��
	astar = new Astar();
	astar->Initialize();

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	// �N���X�̊J��
	delete Cam;
	Cam = nullptr;	

	delete stage;
	stage = nullptr;

	delete obst;
	obst = nullptr;

	delete Mobj;
	Mobj = nullptr;

	delete ui;
	ui = nullptr;

	delete astar;
	astar = nullptr;

	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (key) {
		int a = 0;
	/*	if (AMG_0007::isModeDebug) {
			AMG_0007::isModeDebug = false;
		}
		else {
			AMG_0007::isModeDebug = true;
		}*/
		
	}


	// �J�����̍X�V
	Cam->Process();

	// �X�e�[�W�̍X�V
	stage->Process();

	// ��Q���̍X�V
	obst->Process();

	// �I�u�W�F�N�g�X�V
//	Mobj->Update();

	// UI�X�V
	ui->Process();

	// A*�A���S���Y��
	astar->Process();

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// �X�e�[�W�̕`��
	stage->Render();

	// ��Q���̕`��
	obst->Render();

	// �J�����̕`��
	Cam->Render();

	// �I�u�W�F�N�g�`��
	Mobj->Draw();

	// UI�`��
	ui->Render();

	// A*�A���S���Y��
	astar->Render();

	DrawFormatString(1200, 20, GetColor(255, 255, 255), "st = %d", Stage::GetStInstance()->GetStageInfo().size());

	return true;
}