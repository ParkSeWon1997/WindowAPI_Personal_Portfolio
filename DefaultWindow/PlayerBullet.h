#pragma once
#include "Bullet.h"
class PlayerBullet :
    public CBullet
{

public:
	PlayerBullet();
	virtual ~PlayerBullet();

public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

