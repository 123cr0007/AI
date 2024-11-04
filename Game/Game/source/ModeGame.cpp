
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

ModeGame::ModeGame() {

	// �ϐ��̏�����
	Cam = nullptr;
	stage = nullptr;
	Mobj = nullptr;
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// �J�������`
	Cam = new Camera();
	Cam->Initialize();

	// �X�e�[�W���`
	stage = new Stage();
	stage->Initialize();

	// �I�u�W�F�N�g��`
	Mobj = new ObjectManager();
	Mobj->Initialize();

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	// �N���X�̊J��
	delete Cam;
	Cam = nullptr;	

	delete stage;
	stage = nullptr;

	delete Mobj;
	Mobj = nullptr;

	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();


	// �J�����̍X�V
	Cam->Process();

	// �X�e�[�W�̍X�V
	stage->Process();

	// �I�u�W�F�N�g�X�V
	Mobj->Update();
	
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

	// �J�����̕`��
	Cam->Render();

	// �I�u�W�F�N�g�`��
	Mobj->Draw();

	return true;
}