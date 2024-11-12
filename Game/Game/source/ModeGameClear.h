#pragma once

#include "appframe.h"
#include <string>

// モード
class ModeGameClear : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGameClear();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	// 背景ハンドル
	int bgHandle;

};
