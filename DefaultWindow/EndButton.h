#pragma once
#include "Obj.h"
class EndButton :
    public CObj
{
public:
	EndButton();
	virtual ~EndButton();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID;

};

