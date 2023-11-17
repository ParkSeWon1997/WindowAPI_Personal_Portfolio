#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
	enum ImageSTATE { IDLE, ATTACK, HIT, DEAD, PS_END };
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;



	
	bool			Turn_By_Player();

public:
	void Set_Damage(float _Damage) { fDamage = _Damage; }
	float Get_Damage() { return fDamage; }

	void Set_HP(float _HP) { fHp = _HP; }
	float Get_HP() { return fHp; }

	 
protected:
	float	fHp;
	float	fDamage;


private:
	POINT		m_tPoint[3];
};

