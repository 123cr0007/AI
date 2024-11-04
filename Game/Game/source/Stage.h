#pragma once
#include "appframe.h"
#include "ApplicationMain.h"

constexpr auto ST_DIVNUM = 10;				// ステージを分割する数
constexpr auto STAGE_CANGETIME = -1 * 60;	// ステージの取得時間(-1だと変更なし)
constexpr auto OBSITACLE_NUM = 4;			// お邪魔の数
constexpr auto OBST_DISTANS_X = 3;			// お邪魔の間隔
constexpr auto OBST_DISTANS_Y = 1;			// お邪魔の間隔

class Stage {
 public:

	// ステージのインスタンス
	 static Stage* StInstance;
	 static Stage* GetStInstance() { return (Stage*)StInstance; }

	Stage();
	~Stage();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	bool GetStageSize();	// 正方形限定でステージの大きさを取得できる
	bool SetStDivePos();	// ステージの大きさがわかっていたらステージを分割していく

	// ゲッター
	int GetStageModel() { return stageModel; }
	int GetStageCol() { return stageCol; }
	

	// セッター
	void SetCheckGetSt(bool trg) { checkGetSt = trg; }

 protected:

	// ステージの情報
	int stageModel;
	int stageCol;
	int skySphere;
	int stXNum;
	int stYNum;

	struct STAGE_INFO {

		VECTOR pos[4];		// ステージの三角形の座標
		VECTOR centerPos;	// ステージの中心座標

		int stXArray;		// ステージのX(左右)軸の配列番号
		int stYArray;		// ステージのY(上下)軸の配列番号
		bool fillFlag;		// 塗りつぶしフラグ
		int color;			// ステージの色
		bool isSafety;		// 安全な場所かどうか
		bool isObstacle;	// お邪魔があるかどうか
		bool isOpen;		// ステージが開いているかどうか
	};
	std::vector<STAGE_INFO> stInfo;
	std::vector<STAGE_INFO> safepointInfo;

	// 分割されたステージの情報
	VECTOR stDivePos[ST_DIVNUM + 1][ST_DIVNUM + 1];
	VECTOR sdDiveTripos[ST_DIVNUM * ST_DIVNUM * 2];
	VECTOR stCornerPos[4];
	bool checkHitStart[2];
	bool checkHitEnd[2];

	// 判定用
	bool checkGetSt;
	bool checkHit;
	int stgChangeTime;
	int processCunt;
	int safepointCunt;

	VECTOR stPos;
	VECTOR obstPos;

	float sizeX;

public:

	// std::vector周りのゲッターとセッター
	const std::vector<STAGE_INFO>& GetStageInfo() const {
		return stInfo;
	}

	const std::vector<STAGE_INFO>& GetSafePointInfo() const {
		return safepointInfo;
	}

	bool SetStageFillFlag(int x, int y, bool flag) {
		for (auto& st : stInfo) {
			if (st.stXArray == x && st.stYArray == y) {
				st.fillFlag = flag;
				return true;
			}
		}
		return false;
	}

	bool SetStIsObstacle(int x, int y, bool flag) {
		for (auto& st : stInfo) {
			if (st.stXArray == x && st.stYArray == y) {
				st.isObstacle = flag;
				return true;
			}
		}
		return false;
	}


	VECTOR GetStDivePos(int x, int y) {

		for (auto& st : stInfo) {
			if (st.stXArray == x && st.stYArray == y) {
				return st.centerPos;
			}
		}
		return VGet(0, 0, 0);
	}

	bool GetStIsObstacle(int x, int y) {

		for (auto& st : stInfo) {
			if (st.stXArray == x && st.stYArray == y) {
				return st.isObstacle;
			}
		}
		return false;
	}
};