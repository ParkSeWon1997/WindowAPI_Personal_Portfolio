#pragma once
#include "Scene.h"
class CMyEdit :	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void	Initialize(void);
	virtual void	Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();

private:
	void		Key_Input();
private:
	int Image_NextX;
	int Image_NextY;

};

