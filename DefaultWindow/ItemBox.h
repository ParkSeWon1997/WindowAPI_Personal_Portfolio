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

	void DropMove();


private:

	bool	m_bJump = false;
	float m_fPower = 0;
	float m_fAccelTime = 0;
};

