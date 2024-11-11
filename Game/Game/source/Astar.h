#pragma once
#include "appframe.h"
#include "ApplicationMain.h"
#include <vector>

constexpr auto OPEN_NUM = 4;	// �X�e�[�W�𕪊����鐔

class Astar {
public:
	
	// �C���X�^���X
	static Astar* AsInstance;
	static Astar* GetAsInstance() { return (Astar*)AsInstance; }

	Astar();
	~Astar();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	// A*�A���S���Y��
	bool AstarAlgorithm(int startX, int startY,int goalX, int goalY);

	// ���[�g���̐ݒ�
	void SetShiftInfo();

	// �Q�b�^�[

	// �Z�b�^�[
	void SetStartX(int x) { startX = x; }
	void SetStartY(int y) { startY = y; }
	void SetGoalX(int x) { goalX = x; }
	void SetGoalY(int y) { goalY = y; }

protected:
	// �m�[�h�̏��
	struct ROUTE_INFO {
		
		VECTOR goalPos;		// �S�[���̍��W
		int nodeX;			// �m�[�h��X���W
		int nodeY;			// �m�[�h��Y���W
		bool isMoved;		// �ړ��������ǂ���
	};
	// ���[�g
	std::vector<ROUTE_INFO> routeInfo;

	struct SHIFT_INFO {

		int shiftX;		// X���̃V�t�g
		int shiftY;		// Y���̃V�t�g
	};
	// �V�t�g
	std::vector<SHIFT_INFO> shiftInfo;

	int startX, startY;
	int goalX, goalY;

public:
	// �Q�b�^�[
	const std::vector<ROUTE_INFO>& GetRouteInfo() const
	{
		return routeInfo;
	}

	// �Z�b�^�[
	bool SetIsMoved(int index, bool trg)
	{
		if (index < routeInfo.size())
		{
			routeInfo[index].isMoved = trg;
			return true;
		}
		return false;
	}
};