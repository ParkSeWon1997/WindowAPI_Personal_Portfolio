#pragma once
#include "Obj.h"
class CShield :	public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	float			m_fDistance;
};

