
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

ModeGame::ModeGame() {

	// 変数の初期化
	Cam = nullptr;
	stage = nullptr;
	Mobj = nullptr;
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// カメラを定義
	Cam = new Camera();
	Cam->Initialize();

	// ステージを定義
	stage = new Stage();
	stage->Initialize();

	// オブジェクト定義
	Mobj = new ObjectManager();
	Mobj->Initialize();

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	// クラスの開放
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


	// カメラの更新
	Cam->Process();

	// ステージの更新
	stage->Process();

	// オブジェクト更新
	Mobj->Update();
	
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

	// カメラの描画
	Cam->Render();

	// オブジェクト描画
	Mobj->Draw();

	return true;
}