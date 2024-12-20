#pragma once
#include "appframe.h"
#include "ApplicationMain.h"
#include <vector>
#include <cmath>


constexpr auto OPEN_NUM = 4;	// ステージを分割する数

class Astar {
public:
	
	// インスタンス
	static Astar* AsInstance;
	static Astar* GetAsInstance() { return (Astar*)AsInstance; }

	Astar();
	~Astar();

	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

	// A*アルゴリズム
	bool AstarAlgorithm(int startX, int startY,int goalX, int goalY);

	// ルート情報の設定
	void SetShiftInfo();

	// ゲッター

	// セッター
	void SetStartX(int x) { startX = x; }
	void SetStartY(int y) { startY = y; }
	void SetGoalX(int x) { goalX = x; }
	void SetGoalY(int y) { goalY = y; }

protected:
	// ノードの情報
	struct ROUTE_INFO {
		
		VECTOR goalPos;		// ゴールの座標
		int nodeX;			// ノードのX座標
		int nodeY;			// ノードのY座標
		bool isMoved;		// 移動したかどうか
	};
	// ルート
	std::vector<ROUTE_INFO> routeInfo;

	struct SHIFT_INFO {

		int shiftX;		// X軸のシフト
		int shiftY;		// Y軸のシフト
	};
	// シフト
	std::vector<SHIFT_INFO> shiftInfo;

	// ノード
	struct NODE_INFO {

		int nodeX;		// ノードのX座標
		int nodeY;		// ノードのY座標
		VECTOR position;	// ノードの位置
		int movedCost;		// コスト(g値)
		int heuristic;		// ヒューリスティック(h値)
		int totalCost;		// 合計コスト(f値)
		int nodeIndex;		// ノードのインデックス
		int parentNode;		// 親ノードのインデックス
		int stageIndex;		// ステージのインデックス(デバッグ用)
	};
	// ノードの情報
	std::vector<NODE_INFO> openList;
	std::vector<NODE_INFO> closeList;

	int x, y;
	int startX, startY;
	int goalX, goalY;

	int debugCount;
	int debugNodeNum;

public:
	// ゲッター
	const std::vector<ROUTE_INFO>& GetRouteInfo() const
	{
		return routeInfo;
	}

	// セッター
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