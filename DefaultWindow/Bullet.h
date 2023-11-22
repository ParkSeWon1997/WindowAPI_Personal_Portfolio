#pragma once
#include "Obj.h"
class CBullet :	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void Set_RotateAngle(float _Angle) { m_fRotateAngle = _Angle; }


protected:
	float m_fRotateAngle;
	//virtual void CheckOverrWindow() {};
};

