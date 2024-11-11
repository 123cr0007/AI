#include "Camera.h"
#include "Stage.h"

Camera* Camera::CamInstance = nullptr;
Camera::Camera() {

	CamInstance = this;
	// カメラの設定（わかりやすい位置に）

	_clipNear = 10.f;
	_clipFar = 500000.f;

	radY = DegToRad(-90);	//Y軸回転
	radH = DegToRad(90);		//高さの角度
	CamDist = START_DIST;	//カメラとの距離
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

	float rx, ry, lx, ly;	// 左右アナログスティックの座標
	float analogMin = 0.3f;	// アナログ閾値
	// Logicoolパッドの場合
	rx = pad.RX / analogMin;
	ry = pad.RY / analogMin;
	lx = pad.LX / analogMin;
	ly = pad.LY / analogMin;

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// カメラ操作
	{
		// 各軸でターゲット（プレイヤー）との距離をとる
		float sx = vPos.x - _vTarget.x;
		float sz = vPos.z - _vTarget.z;
		float sy = vPos.y - _vTarget.y;

		//平面座標でカメラとプレイヤーの距離をとる
		float lengthY = sqrt(sz * sz + sx * sx);

		//上から見た平面座標でY軸を回転する
		if (rx > analogMin) { radY -= 0.05f; }
		if (rx < -analogMin) { radY += 0.05f; }

		/*if(key & KEY_INPUT_LEFT) { radY -= 0.05f; }
		if(key & KEY_INPUT_RIGHT) { radY += 0.05f; }*/

		//Y軸を回す
		vPos.x = _vTarget.x + cos(radY) * lengthY;
		vPos.z = _vTarget.z + sin(radY) * lengthY;

#ifdef _DEBUG
		// ここカメラの高さと距離を変える処理
		// #ifdefの外に出す
		{
			//Y軸の回転量とどれだけあげるかの角度でカメラの位置を設定する（回転しているわけではない）
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

			//L1ボタンでカメラの距離を変える
			if (pad.key & PAD_INPUT_5) {

				if (CamDist > 20) {
					CamDist -= 1.f;
				}
			}

			//R1ボタンでカメラの距離を変える
			if (pad.key & PAD_INPUT_6) {

				if (CamDist < DEFAULT_DIST) {
					CamDist += 1.f;
				}
			}
		}
#endif
	
		//Y軸の回転（radY）にX軸の回転（radX）を足して、距離をかけた位置にカメラを置く CamDist sin(radY)
		//極座標の変換
		// x = r*cosθ*cosΦ
		// z = r*cosθ*sinΦ
		// y = r*sinθ
		//本来はｚとｙが逆、ｙが原点からの角度なのでsinになってる
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


	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(vPos, _vTarget);
	SetCameraNearFar(_clipNear, _clipFar);

	return true;
}