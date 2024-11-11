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
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	
	if (trg & PAD_INPUT_1) {
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
	// ノードの情報<heuristicCost,shiftX, shiftX>
	std::vector<std::tuple<int, int, int> >heuristicCost;

	// ステージが開けられるかのチェック
	int tempStIndex = 0;
	for (auto&& st : Stage::GetStInstance()->GetStageInfo())
	{
		for (auto&& shift : shiftInfo)
		{
			if (st.stXArray == nodeX + shift.shiftX
				&& st.stYArray == nodeY + shift.shiftY)
			{
				if (st.canOpen && !st.isOpen)
				{
					Stage::GetStInstance()->SetStOpenFlag(tempStIndex, true);
					heuristicCost.push_back(std::make_tuple(
						abs(goalX - (nodeX + shift.shiftX)) + abs(goalY - (nodeY + shift.shiftY)),
						shift.shiftX, shift.shiftY));
				}
			}
		}
		tempStIndex++;
	}

	// ソート
	std::sort(heuristicCost.begin(), heuristicCost.end());

	// ルートの設定
	if (heuristicCost.size() == 0)
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
	routeInfo.push_back(tempRoute);

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