#pragma once
#include "Obj.h"
class CGuideBullet : public CObj
{
public:
	CGuideBullet();
	virtual ~CGuideBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;



private:
	void Move_LastTarget_Local();

	//Ãß°¡
	CObj* m_pTarget;
	float Last_Target_X;
	float Last_Target_Y;

};

