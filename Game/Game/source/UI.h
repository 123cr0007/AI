#pragma once
#include "appframe.h"

// �G��HP�A�C�R����ݒu���鍂���̊���
// 0.0�ŉ�ʏ㕔�A1.0�ŉ�ʉ���
constexpr auto ENEMY_HP_HIGHT = 0.05;	// �G��HP�A�C�R���̍���

// �G��HP�A�C�R���̊Ԋu
constexpr auto ENEMY_HP_ICON_DISTANS = 150;


// UI�̃N���X

class UI {
 public:

	// UI�̃C���X�^���X
	 static UI* UIInstance;
	 static UI* GetUIInstance() { return (UI*)UIInstance; }

	UI();
	~UI();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	// �Q�b�^�[
	
	// �Z

 protected:

	// UI�̏��
	int enemyHPIcon;

};