#pragma once
#include "Obj.h"
class ItemBox :
    public CObj
{
public:
	ItemBox();
	virtual ~ItemBox();


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

