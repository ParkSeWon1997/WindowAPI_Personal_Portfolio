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

	void		Set_RotaeImage(float _RoateAngle) { RotaeImage = _RoateAngle; }
	void		SEt_Move_DIR(BOSSMONSTER_SPEAR_DIR _ID) { m_eMoveDir = _ID; }


	//void		MoveToWidth(float _X);
	void		Move(BOSSMONSTER_SPEAR_DIR _ID);



private:
	BOSSMONSTER_SPEAR_DIR m_eMoveDir;
	float		RotaeImage = 0;
	 
};

