#pragma once
#include "HpBar.h"
#include "Obj.h"
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

public:
	void Set_MaxHp(float _fMaxHp) { m_fMaxHp = _fMaxHp; }
	void Set_CurHp(float _fCurHp) { m_fCurHp = _fCurHp; }


	float Get_MaxHp() { return m_fMaxHp; }
	float Get_CurHp() { return m_fCurHp; }


	void Set_fCY(float _fCY) { m_tInfo.fCY = _fCY; }

protected:
	float m_fMaxHp;
	float m_fCurHp;

	float m_fPercent;



};



