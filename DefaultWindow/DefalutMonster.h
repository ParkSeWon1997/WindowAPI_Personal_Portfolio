#pragma once
#include "Monster.h"
class DefalutMonster :
    public CMonster
{
public:
    DefalutMonster();
	virtual ~DefalutMonster();


public:
	 virtual void Initialize() override;
	 virtual int Update() override;
	 virtual void Late_Update() override;
	 virtual void Render(HDC hDC) override;
	 virtual void Release() override;





};

