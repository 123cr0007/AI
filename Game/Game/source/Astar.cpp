#include "Astar.h"
#include "Stage.h"
#include "Enemy.h"

Astar* Astar::AsInstance = nullptr;
Astar::Astar() 
{
	AsInstance = this;

	if (Enemy::GetEnInstance() != nullptr)
	{
		startX = Enemy::GetEnInstance()->GetStartX();
		startY = Enemy::GetEnInstance()->GetStartY();
		goalX = Enemy::GetEnInstance()->GetGoalX();
		goalY = Enemy::GetEnInstance()->GetGoalY();
	}
	else
	{
		startX = 0;
		startY = 0;
		goalX = 0;
		goalY = 0;
	}

}

Astar::~Astar() 
{

}

bool Astar::Initialize() 
{
	// シフトの情報を設定
	SetShiftInfo();

	return true;
}

bool Astar::Terminate()
{

	return true;
}

bool Astar::Process()
{
	if (Enemy::GetEnInstance() == nullptr)
	{
		return false;
	}

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_1)
	{
		AstarAlgorithm(startX, startY, goalX, goalY);
	}

	int color = GetColor(0, 0, 255);
	Stage::GetStInstance()->SetStageFillcolor(goalX, goalY, color);
	Stage::GetStInstance()->SetStageFillFlag(goalX, goalY, true);

	return true;
}

bool Astar::Render()
{
	DrawFormatString(0, 400, GetColor(255, 255, 255), "x = %d,y = %d", startX, startY);
	return true;
}

bool Astar::AstarAlgorithm(int nodeX, int nodeY, int goalX, int goalY)
{

	if (nodeX == goalX && nodeY == goalY) {
		return true;
	}

	if (Stage::GetStInstance()->GetStageInfo().size() == 0)
	{
		return false;
	}

	// 
	int standardNodeX = 0;
	int standardNodeY = 0;


	// スタートのノードを設定
	if(degugCount != -1){
		NODE_INFO startNode;
		startNode.nodeX = nodeX;
		startNode.nodeY = nodeY;
		startNode.movedCost = 0;
		startNode.heuristic = abs(goalX - nodeX) + abs(goalY - nodeY);
		startNode.totalCost = startNode.movedCost + startNode.heuristic;
		startNode.nodeIndex = 0;
		startNode.parentNode = -1;
		openList.push_back(startNode);
		degugCount = -1;
	}

	// ソート
	std::sort
	(
		openList.begin(), openList.end(), [](const NODE_INFO& a, const NODE_INFO& b)
		{
			return a.totalCost < b.totalCost;
		}
	);

	if (openList.empty()) {
		return false;
	}
	// 基準ノードの設定
	standardNodeX = openList[0].nodeX;
	standardNodeY = openList[0].nodeY;

	// ノードの探索
	int tempStageIndex = 0;
	int tempShiftIndex = 0;
	for (auto&& stage : Stage::GetStInstance()->GetStageInfo()) {
		for (auto&& shift : shiftInfo)
		{
			int tempNodeX = standardNodeX + shift.shiftX;
			int tempNodeY = standardNodeY + shift.shiftY;

			if (tempShiftIndex >= OPEN_NUM)
			{
				continue;
			}

			if (stage.stXArray == tempNodeX && stage.stYArray == tempNodeY)
			{
				if (stage.canOpen && !stage.isOpen)
				{
					// ノードの設定
					NODE_INFO tempNode;
					tempNode.nodeX = tempNodeX;
					tempNode.nodeY = tempNodeY;
					tempNode.movedCost = openList[0].movedCost + 1;
					tempNode.heuristic = abs(goalX - tempNodeX) + abs(goalY - tempNodeY);
					tempNode.totalCost = tempNode.movedCost + tempNode.heuristic;
					tempNode.nodeIndex = openList.size();
					tempNode.parentNode = openList[0].nodeIndex;
					tempNode.stageIndex = tempStageIndex;

					openList.push_back(tempNode);
					Stage::GetStInstance()->SetStOpenFlag(tempStageIndex, true);
					Stage::GetStInstance()->SetStFillFlag(tempStageIndex, true);
					tempShiftIndex++;
				}
			}
		}

		if (stage.stXArray == standardNodeX && stage.stYArray == standardNodeY)
		{
			Stage::GetStInstance()->SetStOpenFlag(tempStageIndex, true);
			Stage::GetStInstance()->SetStFillFlag(tempStageIndex, true);
			openList[0].stageIndex = tempStageIndex;
		}
		
		tempStageIndex++;
	}

	// 基準をクローズリストに移動
	closeList.push_back(openList[0]);
	Stage::GetStInstance()->SetStFillColor(openList[0].stageIndex, GetColor(255, 0, 0));
	startX = openList[0].nodeX;
	startY = openList[0].nodeY;
	openList.erase(openList.begin());




	// ルートの設定
	{
		/*if (heuristicCost.size() == 0)
		{
			return false;
		}
		startX += std::get<1>(heuristicCost[0]);
		startY += std::get<2>(heuristicCost[0]);

		ROUTE_INFO tempRoute;
		for (auto&& st : Stage::GetStInstance()->GetStageInfo())
		{
			if (st.stXArray == nodeX && st.stYArray == nodeY)
			{
				tempRoute.nodeX = st.stXArray;
				tempRoute.nodeY = st.stYArray;
			}

			if (st.stXArray == startX && st.stYArray == startY)
			{
				tempRoute.goalPos = st.centerPos;
			}
			tempRoute.isMoved = false;
		}
		routeInfo.push_back(tempRoute);*/
	}

	Stage::GetStInstance()->SetStageFillFlag(startX, startY, true);

	return true;
}

void Astar::SetShiftInfo()
{
	// シフトの情報を初期化
	shiftInfo.clear();

	// シフトの情報を設定
	for (int i = 0; i < OPEN_NUM; i++)
	{
		SHIFT_INFO tempShift;
		tempShift.shiftX = 0;
		tempShift.shiftY = 0;

		switch (i)
		{
		case 0:
			// 上
			tempShift.shiftY = -1;
			break;
		case 1:
			// 右
			tempShift.shiftX = 1;
			break;
		case 2:
			// 下
			tempShift.shiftY = 1;
			break;
		case 3:
			// 左
			tempShift.shiftX = -1;
			break;
		}

		shiftInfo.push_back(tempShift);
	}
}