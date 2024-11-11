#include "UI.h"
#include "Enemy.h"
#include "ApplicationMain.h"

UI* UI::UIInstance = nullptr;
UI::UI() {
	UIInstance = this;
}

UI::~UI() {

}

bool UI::Initialize() {

	enemyHPIcon = LoadGraph("res/UI/EnemyIcon.png");

	return true;
}

bool UI::Terminate() {

	return true;
}

bool UI::Process() {

	return true;
}

bool UI::Render() {

	// “G‚ÌHPƒAƒCƒRƒ“‚ð•`‰æ
#ifdef _DEBUG
#else
	for (int i = 0; i < Enemy::GetEnInstance()->GetEnemyHP() / 10; i++) {
		int y = (int)(DISP_H * ENEMY_HP_HIGHT);
		DrawGraph(10 + i * ENEMY_HP_ICON_DISTANS, y, enemyHPIcon, true);
	}
#endif

	return true;
}