#pragma once
#include "appframe.h"

constexpr auto DISP_W = 1280;
constexpr auto DISP_H = 720;


class ApplicationMain : public ApplicationBase
{
	typedef ApplicationBase base;
public:
	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return DISP_W; }
	virtual int DispSizeH() { return DISP_H; }

protected:

}; 
