#include "Astar.h"
#include "Stage.h"
#include "Enemy.h"

Astar* Astar::AsInstance = nullptr;
Astar::Astar()
{
	AsInstance = this;

	x = 0;
	y = 0;
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
	debugCount = 0;
	debugNodeNum = 0;
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
	VECTOR tempPos = VGet(0, 0, 0);
	VECTOR tempPos2 = VGet(0, 0, 0);
	for (auto&& route : routeInfo)
	{
		tempPos = route.goalPos;
		tempPos2 = VGet(route.goalPos.x, route.goalPos.y + 5, route.goalPos.z);
		DrawLine3D(tempPos, tempPos2, GetColor(255, 255, 255));
	}

	return true;
}

bool Astar::AstarAlgorithm(int nodeX, int nodeY, int goalX, int goalY)
{

	if (x == goalX && y == goalY) {
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
	if (debugCount != -1) {
		NODE_INFO startNode;
		startNode.nodeX = nodeX;
		startNode.nodeY = nodeY;
		startNode.position = Stage::GetStInstance()->GetStagePositoin(nodeX, nodeY);
		startNode.movedCost = 0;
		startNode.heuristic = abs(goalX - nodeX) + abs(goalY - nodeY);
		startNode.totalCost = startNode.movedCost + startNode.heuristic;
		startNode.nodeIndex = debugNodeNum;
		debugNodeNum++;
		startNode.parentNode = -1;
		openList.push_back(startNode);
		debugCount = -1;
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
					tempNode.position = stage.centerPos;
					tempNode.movedCost = openList[0].movedCost + 1;
					tempNode.heuristic = abs(goalX - tempNodeX) + abs(goalY - tempNodeY);
					tempNode.totalCost = tempNode.movedCost + tempNode.heuristic;
					tempNode.nodeIndex = debugNodeNum;
					debugNodeNum++;
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
	x = openList[0].nodeX;
	y = openList[0].nodeY;
	openList.erase(openList.begin());




	// ルートの設定
	if (x == goalX && y == goalY) {
		if (closeList.size() == 0)
		{
			return false;
		}

		std::sort
		(
			openList.begin(), openList.end(), [](const NODE_INFO& a, const NODE_INFO& b)
			{
				return a.totalCost < b.totalCost;
			}
		);

		int tempPereantNode = 0;

		ROUTE_INFO tempRoute;
		for (int i = closeList.size(); i > 0; i--)
		{
			auto&& node = closeList[i - 1];
			if (tempPereantNode == 0 || tempPereantNode == node.nodeIndex)
			{
				tempRoute.goalPos = node.position;
				tempRoute.nodeX = node.nodeX;
				tempRoute.nodeY = node.nodeY;
				tempRoute.isMoved = false;
				tempPereantNode = node.parentNode;
				Stage::GetStInstance()->SetStFillColor(node.stageIndex, GetColor(255, 255, 255));
				routeInfo.push_back(tempRoute);
			}
		}
		int a = 0;
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