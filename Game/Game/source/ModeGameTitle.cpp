#include "ModeGameTitle.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ApplicationMain.h"

ModeGameTitle::ModeGameTitle() {
	bgHandle = -1;
}

bool ModeGameTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	// �w�i�̓ǂݍ���
	bgHandle = LoadGraph("res/title.png");

	return true;
}

bool ModeGameTitle::Terminate() {
	base::Terminate();

	// �w�i�̉��
	DeleteGraph(bgHandle);

	return true;
}

bool ModeGameTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �^�C�g����ʂ̕`��
	DrawGraph(0, 0, bgHandle, FALSE);

	// �Q�[���X�^�[�g
	if (trg & PAD_INPUT_1) {
		ModeGame* game = new ModeGame();

		ModeServer::GetInstance()->Add(game, 1, "game");
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

bool ModeGameTitle::Render() {
	base::Render();

	DrawGraph(0, 0, bgHandle, FALSE);

	return true;
}