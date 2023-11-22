#pragma once
#include "Bullet.h"
class IcicleBullet :
    public CBullet
{

public:
	IcicleBullet();
	virtual ~IcicleBullet();
public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Set_RotaeImage(float _RoateAngle) { RotaeImage = _RoateAngle; }


private:

	float		RotaeImage = 0;
};

