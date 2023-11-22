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
	void		Set_MoveCallRight(bool _Right) { MoveCallRight = _Right; }
	void		Set_RotaeImage(float _RoateAngle) { RotaeImage = _RoateAngle; }


	//void		MoveToWidth(float _X);
	void		Move();


	bool		MoveCallRight;


private:

	float		RotaeImage = 0;
	 
};

