#pragma once
#include "HpBar.h"
class PlayerHPBar :
    public HpBar
{
public:
	PlayerHPBar();
	virtual ~PlayerHPBar();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();


};

