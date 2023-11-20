#pragma once
#include "Bullet.h"
class MonsterBullet :
    public CBullet
{
public:
    MonsterBullet();
    virtual ~MonsterBullet();
public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	

};

