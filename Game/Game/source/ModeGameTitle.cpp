#include "ModeGameTitle.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ApplicationMain.h"

ModeGameTitle::ModeGameTitle() {
	bgHandle = -1;
}

bool ModeGameTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	// ”wŒi‚Ì“Ç‚Ýž‚Ý
	bgHandle = LoadGraph("res/title.png");

	return true;
}

bool ModeGameTitle::Terminate() {
	base::Terminate();

	// ”wŒi‚Ì‰ð•ú
	DeleteGraph(bgHandle);

	return true;
}

bool ModeGameTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì•`‰æ
	DrawGraph(0, 0, bgHandle, FALSE);

	// ƒQ[ƒ€ƒXƒ^[ƒg
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