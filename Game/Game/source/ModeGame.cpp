
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameClear.h"

ModeGame::ModeGame() {

	// 変数の初期化
	Cam = nullptr;
	stage = nullptr;
	obst = nullptr;
	Mobj = nullptr;
	ui = nullptr;
	astar = nullptr;
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// カメラを定義
	Cam = new Camera();
	Cam->Initialize();

	// ステージを定義
	stage = new Stage();
	stage->Initialize();

	// 障害物を定義
	obst = new Obstacle();
	obst->Initialize();

	// オブジェクト定義
	Mobj = new ObjectManager();
	Mobj->Initialize();

	// UI定義
	ui = new UI();
	ui->Initialize();

	// A*アルゴリズム
	astar = new Astar();
	astar->Initialize();

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	// クラスの開放
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


	// カメラの更新
	Cam->Process();

	// ステージの更新
	stage->Process();

	// 障害物の更新
	obst->Process();

	// オブジェクト更新
//	Mobj->Update();

	// UI更新
	ui->Process();

	// A*アルゴリズム
	astar->Process();

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ステージの描画
	stage->Render();

	// 障害物の描画
	obst->Render();

	// カメラの描画
	Cam->Render();

	// オブジェクト描画
	Mobj->Draw();

	// UI描画
	ui->Render();

	// A*アルゴリズム
	astar->Render();

	DrawFormatString(1200, 20, GetColor(255, 255, 255), "st = %d", Stage::GetStInstance()->GetStageInfo().size());

	return true;
}