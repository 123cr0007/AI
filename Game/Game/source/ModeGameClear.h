#pragma once

#include "appframe.h"
#include <string>

// ���[�h
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

	// �w�i�n���h��
	int bgHandle;

};
