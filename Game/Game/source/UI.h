#pragma once
#include "appframe.h"

// 敵のHPアイコンを設置する高さの割合
// 0.0で画面上部、1.0で画面下部
constexpr auto ENEMY_HP_HIGHT = 0.05;	// 敵のHPアイコンの高さ

// 敵のHPアイコンの間隔
constexpr auto ENEMY_HP_ICON_DISTANS = 150;


// UIのクラス

class UI {
 public:

	// UIのインスタンス
	 static UI* UIInstance;
	 static UI* GetUIInstance() { return (UI*)UIInstance; }

	UI();
	~UI();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	// ゲッター
	
	// セ

 protected:

	// UIの情報
	int enemyHPIcon;

};