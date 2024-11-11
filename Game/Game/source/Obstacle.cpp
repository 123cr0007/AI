#include "Obstacle.h"


Obstacle* Obstacle::ObstInstance = nullptr;
Obstacle::Obstacle() 
{
	ObstInstance = this;
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		obstModel[i] = -1;
		obstCol[i] = -1;
	}
	setUpFlag = false;
}

Obstacle::~Obstacle() 
{
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		MV1DeleteModel(obstModel[i]);
	}
}

bool Obstacle::Initialize() 
{
	tempModel = MV1LoadModel("res/stage/StandardBox.mv1");

	return true;
}

bool Obstacle::Terminate() 
{
	return true;
}

bool Obstacle::Process() 
{

	if (!setUpFlag)
	{
		SetObstacle();
	}
	return true;
}

bool Obstacle::Render() 
{
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		MV1DrawModel(obstModel[i]);
	}

	return true;
}

int obstMap[ST_DIVNUM][ST_DIVNUM] = 
{
	0,0,0,0,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,1,1,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,1,0,0,
	0,0,1,0,0,0,0,1,0,0,
	0,0,0,0,0,0,0,0,0,0,
};

bool Obstacle::CheckSafety()
{
	return true;
}

bool Obstacle::SetObstacle()
{
	int tempObstNum = 0;
	int tempStIndexNum = 0;
	if (Stage::GetStInstance() != nullptr
		&& Stage::GetStInstance()->GetStageInfo().size() != 0)
	{
		for (auto&& st : Stage::GetStInstance()->GetStageInfo())
		{
			if (obstMap[st.stXArray][st.stYArray] == 1)
			{
				Stage::GetStInstance()->SetStCanOpenFlag(tempStIndexNum, false);

				// mv1のモデルをコピー
				VECTOR pos = st.centerPos;
				obstModel[tempObstNum] = MV1DuplicateModel(tempModel);
				obstCol[tempObstNum] = -1;

				// 位置と大きさを設定
				MV1SetScale(obstModel[tempObstNum], VGet(0.1f, 0.1f, 0.1f));
				MV1SetPosition(obstModel[tempObstNum], pos);

				// 当たり判定の設定
				MV1SetupCollInfo(obstModel[tempObstNum], obstCol[tempObstNum], 32, 32, 32);

				if (tempObstNum < OBSTACLE_NUM)
				{
					tempObstNum++;
				}
				else 
				{
					break;
				}
			}

			tempStIndexNum++;
		}

		setUpFlag = true;
		MV1DeleteModel(tempModel);
		tempModel = -1;
		tempStIndexNum = 0;
	}

	return true;
}