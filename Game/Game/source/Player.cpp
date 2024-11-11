#include "ApplicationMain.h"
#include "Player.h"
#include "Stage.h"
#include "Camera.h"

Player* Player::PlInstance = nullptr;
Player::Player() {
	PlInstance = this;

	graphX = 0;
	graphY = 0;
	isAttack = false;
}

Player::~Player() {
}

bool Player::Initialize() {
	Load("res/Player/target.png",0);
	GetGraphSize(handle, &graphX, &graphY);
	gSize = 10.0f;
	vPos = VGet(0, 20, 0);
	
	x = DISP_W / 2 - graphX / 2;
	y = DISP_H / 2 - graphY / 2;
	return true;
}

bool Player::Terminate() {
	return true;
}

bool Player::Process() {

	// �L�[����
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	/*VECTOR planePos = VAdd(VGet(x, y, 0), Operate());

	x = planePos.x;
	y = planePos.y;*/

	// �㉺���E�L�[�������ꂽ��
	if (key & KEY_INPUT_UP) {
		y -= PLAYER_SPEED;
	}

	if (key & PAD_INPUT_DOWN) {
		y += PLAYER_SPEED;
	}

	if (key & KEY_INPUT_LEFT) {
		x -= PLAYER_SPEED;
	}

	if (key & KEY_INPUT_RIGHT) {
		x += PLAYER_SPEED;
	}

	// x,y����vPos���X�V
	VECTOR pos1 = ConvScreenPosToWorldPos(VGet(x, y, 0.0f));
	VECTOR pos2 = ConvScreenPosToWorldPos(VGet(x, y, 1.0f));

	//pos1,2����vPos���X�V�����Ԑ����ƃX�e�[�W�̌�_��vPos�ɂ���
	MV1_COLL_RESULT_POLY HitPoly;
	HitPoly = MV1CollCheck_Line(Stage::GetStInstance()->GetStageModel(), 
		Stage::GetStInstance()->GetStageCol(), pos1, pos2);
	if (HitPoly.HitFlag == true) {
		vPos = HitPoly.HitPosition; 
	}


	// z�L�[�������ꂽ��
	if (trg & PAD_INPUT_1) {

		// �U���t���O�𗧂Ă�
		isAttack = true;	
	}
	else {
		isAttack = false;
	}

	return true;
}

bool Player::Render(int type) {
	type = 2;
	ObjectBase::Rend(type);

#ifdef _DEBUG
	DrawFormatString(0, 100, GetColor(0, 0, 0), "x:%d y:%d",x,y);
	DrawFormatString(0, 120, GetColor(0, 0, 0), "isAttack:%d", isAttack);
#endif

	return true;
}

VECTOR Player::Operate() {

	VECTOR v = { 0,0,0 };	// �ړ���

	//�p�b�h���͂��擾   
	GamePad::MULTIPAD pad = GamePad::GetInstance()->GetMultiPad(PLAYER_1);

	//�J�����̈ʒu������
	VECTOR camPos = Camera::GetCamInstance()->GetCamPos();
	VECTOR camTgtPos = Camera::GetCamInstance()->GetTgtPos();

	if (pad.LX != 0 || pad.LY != 0) // ���͂�������
	{
		VECTOR lstick = { 0,0,0 };	// ���E�A�i���O�X�e�B�b�N�̍��W
		float analogMin = 0.3f;	// �A�i���O臒l

		lstick.x = pad.LX;
		lstick.y = pad.LY;

		// ���͂�ϊ�
		lstick = VNorm(lstick);

		// �J�����̌����Ă���p�x���擾
		float sx = camPos.x - camTgtPos.x;
		float sy = camPos.y - camTgtPos.y;
		float camrad = atan2(sy, sx);

		// �L�����ړ�(�J�����ݒ�ɍ��킹��)
		float mvSpeed = PLAYER_SPEED;

		// �A�i���O���X�e�B�b�N�p
		float length = sqrt(lstick.x * lstick.x + lstick.y * lstick.y);
		float rad = atan2(lstick.x, lstick.y);
		if (length < analogMin) {
			// ���͂������������瓮���Ȃ��������Ƃɂ���
			length = 0.f;
		}
		else {
			length = mvSpeed;
		}

		// v��rad����]&�ړ�������
		v.x -= cos(rad + camrad) * length;
		v.y = sin(rad + camrad) * length;
	}
	
	return v;
}
