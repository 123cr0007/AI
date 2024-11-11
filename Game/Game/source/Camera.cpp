#include "Camera.h"
#include "Stage.h"

Camera* Camera::CamInstance = nullptr;
Camera::Camera() {

	CamInstance = this;
	// �J�����̐ݒ�i�킩��₷���ʒu�Ɂj

	_clipNear = 10.f;
	_clipFar = 500000.f;

	radY = DegToRad(-90);	//Y����]
	radH = DegToRad(90);		//�����̊p�x
	CamDist = START_DIST;	//�J�����Ƃ̋���
}

Camera::~Camera() {


}

bool Camera::Initialize() {

	_vTarget = VGet(0, 0, 0);
	vPos = VGet(0, 200, 0);


	return true;
}

bool Camera::Process() {

	GamePad::MULTIPAD pad = GamePad::GetInstance()->GetMultiPad(PLAYER_1);

	float rx, ry, lx, ly;	// ���E�A�i���O�X�e�B�b�N�̍��W
	float analogMin = 0.3f;	// �A�i���O臒l
	// Logicool�p�b�h�̏ꍇ
	rx = pad.RX / analogMin;
	ry = pad.RY / analogMin;
	lx = pad.LX / analogMin;
	ly = pad.LY / analogMin;

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �J��������
	{
		// �e���Ń^�[�Q�b�g�i�v���C���[�j�Ƃ̋������Ƃ�
		float sx = vPos.x - _vTarget.x;
		float sz = vPos.z - _vTarget.z;
		float sy = vPos.y - _vTarget.y;

		//���ʍ��W�ŃJ�����ƃv���C���[�̋������Ƃ�
		float lengthY = sqrt(sz * sz + sx * sx);

		//�ォ�猩�����ʍ��W��Y������]����
		if (rx > analogMin) { radY -= 0.05f; }
		if (rx < -analogMin) { radY += 0.05f; }

		/*if(key & KEY_INPUT_LEFT) { radY -= 0.05f; }
		if(key & KEY_INPUT_RIGHT) { radY += 0.05f; }*/

		//Y������
		vPos.x = _vTarget.x + cos(radY) * lengthY;
		vPos.z = _vTarget.z + sin(radY) * lengthY;

#ifdef _DEBUG
		// �����J�����̍����Ƌ�����ς��鏈��
		// #ifdef�̊O�ɏo��
		{
			//Y���̉�]�ʂƂǂꂾ�������邩�̊p�x�ŃJ�����̈ʒu��ݒ肷��i��]���Ă���킯�ł͂Ȃ��j
			if (radH <= 1.49) {
				if (ry > -analogMin) {

					radH += 0.05f;
				}
			}
			if (radH >= -1.49) {
				if (ry < analogMin) {

					radH -= 0.05f;
				}
			}

			//L1�{�^���ŃJ�����̋�����ς���
			if (pad.key & PAD_INPUT_5) {

				if (CamDist > 20) {
					CamDist -= 1.f;
				}
			}

			//R1�{�^���ŃJ�����̋�����ς���
			if (pad.key & PAD_INPUT_6) {

				if (CamDist < DEFAULT_DIST) {
					CamDist += 1.f;
				}
			}
		}
#endif
	
		//Y���̉�]�iradY�j��X���̉�]�iradX�j�𑫂��āA�������������ʒu�ɃJ������u�� CamDist sin(radY)
		//�ɍ��W�̕ϊ�
		// x = r*cos��*cos��
		// z = r*cos��*sin��
		// y = r*sin��
		//�{���͂��Ƃ����t�A�������_����̊p�x�Ȃ̂�sin�ɂȂ��Ă�
		vPos.x = _vTarget.x + CamDist * cos(radH) * cos(radY);
		vPos.z = _vTarget.z + CamDist * cos(radH) * sin(radY);
		vPos.y = _vTarget.y + CamDist * sin(radH);
	}

	return true;
}

bool Camera::Render() {

#ifdef _DEBUG

	DrawFormatString(0, 300, GetColor(0, 0, 0), "X:%.2f Y:%.2f Z:%.2f", vPos.x, vPos.y, vPos.z);
	DrawFormatString(0, 320, GetColor(0, 0, 0), "X:%.2f Y:%.2f Z:%.2f", _vTarget.x, _vTarget.y, _vTarget.z);
	DrawFormatString(0, 340, GetColor(0, 0, 0), "CamDist:%.2f", CamDist);
	DrawFormatString(0, 360, GetColor(0, 0, 0), "Lenth:%f", _vTarget.y - vPos.y);

#endif


	// �J�����ݒ�X�V
	SetCameraPositionAndTarget_UpVecY(vPos, _vTarget);
	SetCameraNearFar(_clipNear, _clipFar);

	return true;
}