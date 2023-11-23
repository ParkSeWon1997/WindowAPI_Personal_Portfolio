#pragma once
#include "HpBar.h"
class BossHPBar :
    public HpBar
{
public:
	BossHPBar();
	virtual ~BossHPBar();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();
};

