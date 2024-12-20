#include "ModeGameTitle.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ApplicationMain.h"

ModeGameTitle::ModeGameTitle() {
	bgHandle = -1;
}

bool ModeGameTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	// 背景の読み込み
	bgHandle = LoadGraph("res/title.png");

	return true;
}

bool ModeGameTitle::Terminate() {
	base::Terminate();

	// 背景の解放
	DeleteGraph(bgHandle);

	return true;
}

bool ModeGameTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// タイトル画面の描画
	DrawGraph(0, 0, bgHandle, FALSE);

	// ゲームスタート
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