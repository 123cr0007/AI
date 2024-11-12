#pragma once
#include "appframe.h"

class ModeGameTitle : public ModeBase {
	typedef ModeBase base;
public:

	ModeGameTitle();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	// ”wŒiƒnƒ“ƒhƒ‹
	int bgHandle;
};
