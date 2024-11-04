#include "Stage.h"
#include "ApplicationMain.h"

Stage* Stage::StInstance = nullptr;
Stage::Stage() {
	StInstance = this;
	stageModel = -1;
	stageCol = -1;
	skySphere = -1;
	stXNum = 0;
	stYNum = 0;
	for (int i = 0; i < ST_DIVNUM; i++) {
		for (int j = 0; j < ST_DIVNUM; j++) {
			stDivePos[i][j] = VGet(0, 0, 0);
		}
	}
	for (int i = 0; i < 4; i++) {
		stCornerPos[i] = VGet(0, 0, 0);
	}
	for (int i = 0; i < 2; i++) {
		checkHitStart[i] = false;
		checkHitEnd[i] = false;
	}

	checkGetSt = false;
	checkHit = false;
	stgChangeTime = 1;
	processCunt = 0;
	safepointCunt = 0;

	stPos = VGet(0, 0, 0);
	obstPos = VGet(0, 0, 0);
}

Stage::~Stage() {

	MV1DeleteModel(stageModel);
}

bool Stage::Initialize() {

	stageModel = MV1LoadModel("res/stage/stage.mv1");
	MV1SetupCollInfo(stageModel, stageCol, 32, 32, 32);
	skySphere = MV1LoadModel("res/stage/S_Skysphere.mv1");

#ifdef _DEBUG
	MV1SetOpacityRate(stageModel,0.3);

#endif


	//GetStageSize();
	return true;
}

bool Stage::Terminate() {

	return true;
}

bool Stage::Process() {

	// ステージのサイズを取得
	// 一回描画の処理を通してカメラの位置更新しないと取れないため以下の処理を行う

	if (processCunt > 0) {
		GetStageSize();
		processCunt = -1;
	}
	else if(processCunt == 0){
		// 一回だけ進める
		processCunt++;
	}

	return true;
}

bool Stage::Render() {

	MV1SetPosition(skySphere, VGet(0, 0, 0));
	MV1DrawModel(skySphere);

	MV1SetPosition(stageModel, stPos);
	MV1DrawModel(stageModel);

	//MV1DrawModel(obstModel);

	/*for (auto& obst : obstInfo) {
		MV1SetPosition(obst.obstHandle, obst.obstPos);
		MV1DrawModel(obst.obstHandle);
	}*/

#ifdef _DEBUG
	DrawFormatString(0, 200, GetColor(0, 0, 0), "stXNum:%d stYNum:%d", stXNum, stYNum);

	int n = 1;
	// ステージの描画
	for (auto& st : stInfo) {

		VECTOR pos1 = VGet(st.pos[0].x, st.pos[0].y + 0.1, st.pos[0].z);
		VECTOR pos2 = VGet(st.pos[1].x, st.pos[1].y + 0.1, st.pos[1].z);
		VECTOR pos3 = VGet(st.pos[2].x, st.pos[2].y + 0.1, st.pos[2].z);
		VECTOR pos4 = VGet(st.pos[3].x, st.pos[3].y + 0.1, st.pos[3].z);

		VECTOR sPos = VGet(st.centerPos.x, st.centerPos.y, st.centerPos.z);
		VECTOR sPos2 = VGet(st.centerPos.x, st.centerPos.y + 5.0f, st.centerPos.z);

		DrawLine3D(pos1, pos2, st.color);
		DrawLine3D(pos2, pos3, st.color);
		DrawLine3D(pos3, pos4, st.color);
		DrawLine3D(pos4, pos1, st.color);

		/*DrawLine3D(sPos, sPos2, st.color);*/
	}

	for (auto& st : safepointInfo) {

		DrawFormatString(0, 600 + (n * 20), GetColor(0, 0, 0),
			"pos %f %f %f", st.pos[0], st.pos[1], st.pos[2]);
		DrawFormatString(0, 600 + (n * 20 + 20), GetColor(0, 0, 0),
			"Array:%d %d", st.stXArray, st.stYArray);
		n += 2;
	}
	

	DrawFormatString(0, 620 + (n * 20 + 20), GetColor(0, 0, 0), "SafeNum %d", safepointInfo.size());
	DrawFormatString(0, 640 + (n * 20 + 20), GetColor(0, 0, 0), "SafeNum %d", stInfo.size());

#endif

	return true;
}

bool Stage::GetStageSize() {

	// 一回しか判定取らないようにする
	if (checkGetSt) {
		return true;
	}

	// 色々初期化
	checkGetSt = true;
	MV1_COLL_RESULT_POLY HitPoly;
	VECTOR oldPos = VGet(0, 0, 0);

	// 横のサイズを画面の大きさ分for文で回して取得する
	for (int i = 0; i < DISP_W; i++) {

		VECTOR pos1 = VGet(0, 0, 0);
		VECTOR pos2 = VGet(0, 0, 0);

		pos1 = ConvScreenPosToWorldPos(VGet(i, DISP_H / 2, 0));
		pos2 = ConvScreenPosToWorldPos(VGet(i, DISP_H / 2, 1));

		HitPoly = MV1CollCheck_Line(stageModel, stageCol, pos1, pos2);

		if (HitPoly.HitFlag == TRUE) {

			if (!checkHitStart[0]) {
				// 当たっていたら最初だけ配列に入れることで端をとれる
				checkHitStart[0] = true;
				stCornerPos[0] = HitPoly.HitPosition;
			}

			oldPos = HitPoly.HitPosition;
		}
		else {
			
			// 当たらなかったときにすでにステージの判定を取っていたら
			// 一個前に取ったポジションをもう一個の端としておいておく
			if (checkHitStart[0] && !checkHitEnd[0]) {
				checkHitEnd[0] = true;
				stCornerPos[1] = oldPos;
			}
		}
	}

	// 縦のサイズを画面の大きさ分for文で回して取得する
	for (int i = 0; i < DISP_H; i++) {

		VECTOR pos1 = VGet(0, 0, 0);
		VECTOR pos2 = VGet(0, 0, 0);

		pos1 = ConvScreenPosToWorldPos(VGet(DISP_W / 2, i, 0));
		pos2 = ConvScreenPosToWorldPos(VGet(DISP_W / 2, i, 1));

		HitPoly = MV1CollCheck_Line(stageModel, stageCol, pos1, pos2);

		if (HitPoly.HitFlag == TRUE) {
			
			// 当たっていたら最初だけ配列に入れることで端をとれる
			if (!checkHitStart[1]) {
				checkHitStart[1] = true;
				stCornerPos[2] = HitPoly.HitPosition;
			}

			oldPos = HitPoly.HitPosition;
		}
		else {

			// 当たらなかったときにすでにステージの判定を取っていたら
			// 一個前に取ったポジションをもう一個の端としておいておく
			if (checkHitStart[1] && !checkHitEnd[1]) {
				checkHitEnd[1] = true;
				stCornerPos[3] = oldPos;
			}
		}
	}

	SetStDivePos();

	return true;
}



bool Stage::SetStDivePos() {

	// ステージのサイズを計算
	float stageSizeX = stCornerPos[1].x - stCornerPos[0].x;
	float stageSizeZ = stCornerPos[3].z - stCornerPos[2].z;

	// ステージを等分割して位置を設定
	for (int i = 0; i < ST_DIVNUM + 1; i++) {
		for (int j = 0; j < ST_DIVNUM + 1; j++) {

			stDivePos[i][j] = VGet(
				stCornerPos[0].x + (stageSizeX / ST_DIVNUM) * i,
				stCornerPos[0].y,
				stCornerPos[2].z + (stageSizeZ / ST_DIVNUM) * j
			);
		}
	}

	STAGE_INFO sInfo;
	int tempX = 0;
	int tempY = 0;

	for (int i = 0; i < ST_DIVNUM; i++) {
		for (int j = 0; j < ST_DIVNUM; j++) {

			sInfo.pos[0] = stDivePos[i][j];
			sInfo.pos[1] = stDivePos[i + 1][j];
			sInfo.pos[2] = stDivePos[i + 1][j + 1];
			sInfo.pos[3] = stDivePos[i][j + 1];

			sInfo.centerPos = VGet(
				(sInfo.pos[0].x + sInfo.pos[1].x + sInfo.pos[2].x + sInfo.pos[3].x) / 4,
				(sInfo.pos[0].y + sInfo.pos[1].y + sInfo.pos[2].y + sInfo.pos[3].y) / 4,
				(sInfo.pos[0].z + sInfo.pos[1].z + sInfo.pos[2].z + sInfo.pos[3].z) / 4);


			sInfo.stXArray = tempX;
			sInfo.stYArray = tempY;

			tempX++;
			if (tempX >= ST_DIVNUM) {
				tempX = 0;
				tempY++;
			}

			sInfo.fillFlag = false;
			sInfo.color = GetColor(0, 255, 0);

			sInfo.isSafety = false;
			sInfo.isObstacle = false;
			sInfo.isOpen = true;

			stInfo.push_back(sInfo);
		}
	}

	return true;
}