#pragma once
#include"Obj.h"


class HpBar :public CObj
{


public:
	HpBar();
	virtual ~HpBar();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	void Set_MaxHp(float _fMaxHp) { m_fMaxHp = _fMaxHp; }
	void Set_CurHp(float _fCurHp) { m_fCurHp = _fCurHp; }
	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }

	float Get_MaxHp() { return m_fMaxHp; }
	float Get_CurHp() { return m_fCurHp; }
	INFO Get_Info() { return m_tInfo; }


protected:
	float m_fMaxHp;
	float m_fCurHp;

	float m_fPercent;

	INFO m_tInfo;

	RECT m_tOuterRect;
	RECT m_tInnerRect;


};

