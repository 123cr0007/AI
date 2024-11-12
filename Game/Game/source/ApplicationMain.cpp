
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameTitle.h"

namespace AMG_0007{
	bool isModeDebug = false;
}


ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// ƒ‚[ƒh‚Ì“o˜^

#ifdef _DEBUG
	ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
#else
	ModeServer::GetInstance()->Add(new ModeGameTitle(), 1, "title");
#endif


	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	return true;
}

