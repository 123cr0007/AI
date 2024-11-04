#pragma once
#include "appframe.h"
#include "ApplicationMain.h"

constexpr auto ST_DIVNUM = 10;				// �X�e�[�W�𕪊����鐔
constexpr auto STAGE_CANGETIME = -1 * 60;	// �X�e�[�W�̎擾����(-1���ƕύX�Ȃ�)
constexpr auto OBSITACLE_NUM = 4;			// ���ז��̐�
constexpr auto OBST_DISTANS_X = 3;			// ���ז��̊Ԋu
constexpr auto OBST_DISTANS_Y = 1;			// ���ז��̊Ԋu

class Stage {
 public:

	// �X�e�[�W�̃C���X�^���X
	 static Stage* StInstance;
	 static Stage* GetStInstance() { return (Stage*)StInstance; }

	Stage();
	~Stage();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	bool GetStageSize();	// �����`����ŃX�e�[�W�̑傫�����擾�ł���
	bool SetStDivePos();	// �X�e�[�W�̑傫�����킩���Ă�����X�e�[�W�𕪊����Ă���

	// �Q�b�^�[
	int GetStageModel() { return stageModel; }
	int GetStageCol() { return stageCol; }
	

	// �Z�b�^�[
	void SetCheckGetSt(bool trg) { checkGetSt = trg; }

 protected:

	// �X�e�[�W�̏��
	int stageModel;
	int stageCol;
	int skySphere;
	int stXNum;
	int stYNum;

	struct STAGE_INFO {

		VECTOR pos[4];		// �X�e�[�W�̎O�p�`�̍��W
		VECTOR centerPos;	// �X�e�[�W�̒��S���W

		int stXArray;		// �X�e�[�W��X(���E)���̔z��ԍ�
		int stYArray;		// �X�e�[�W��Y(�㉺)���̔z��ԍ�
		bool fillFlag;		// �h��Ԃ��t���O
		int color;			// �X�e�[�W�̐F
		bool isSafety;		// ���S�ȏꏊ���ǂ���
		bool isObstacle;	// ���ז������邩�ǂ���
		bool isOpen;		// �X�e�[�W���J���Ă��邩�ǂ���
	};
	std::vector<STAGE_INFO> stInfo;
	std::vector<STAGE_INFO> safepointInfo;

	// �������ꂽ�X�e�[�W�̏��
	VECTOR stDivePos[ST_DIVNUM + 1][ST_DIVNUM + 1];
	VECTOR sdDiveTripos[ST_DIVNUM * ST_DIVNUM * 2];
	VECTOR stCornerPos[4];
	bool checkHitStart[2];
	bool checkHitEnd[2];

	// ����p
	bool checkGetSt;
	bool checkHit;
	int stgChangeTime;
	int processCunt;
	int safepointCunt;

	VECTOR stPos;
	VECTOR obstPos;

	float sizeX;

public:

	// std::vector����̃Q�b�^�[�ƃZ�b�^�[
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