#pragma once
#include "Bullet.h"
class MonsterIceSpear :
    public CBullet
{
public:
	MonsterIceSpear();
	virtual ~MonsterIceSpear();
public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	//void		MoveToWidth(float _X);


};

