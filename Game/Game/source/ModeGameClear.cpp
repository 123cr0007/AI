#include "ModeGameClear.h"
#include "ModeGameTitle.h"
#include "ApplicationMain.h"

ModeGameClear::ModeGameClear() {
	bgHandle = -1;
}

bool ModeGameClear::Initialize() {
	if (!base::Initialize()) { return false; }

	// �w�i�̓ǂݍ���
	bgHandle = LoadGraph("res/clear.png");

	return true;
}

bool ModeGameClear::Terminate() {
	base::Terminate();

	// �w�i�̉��
	DeleteGraph(bgHandle);

	return true;
}

bool ModeGameClear::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �N���A��ʂ̕`��
	DrawGraph(0, 0, bgHandle, FALSE);

	// �^�C�g���ɖ߂�
	if (trg & PAD_INPUT_1) {
		ModeGameTitle* title = new ModeGameTitle();

		ModeServer::GetInstance()->Add(title, 1, "title");
		ModeServer::GetInstance()->Del(this);
	}

	// �Q�[�����I���
	if (trg & PAD_INPUT_2) {
		ApplicationMain* AppMain = new ApplicationMain();
		ModeServer::GetInstance()->Del(this);
		AppMain->Terminate();
	}

	return true;
}

bool ModeGameClear::Render() {
	base::Render();

	DrawGraph(0, 0, bgHandle, FALSE);

	return true;
}