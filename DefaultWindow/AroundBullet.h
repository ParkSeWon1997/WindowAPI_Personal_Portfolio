#pragma once
#include "Obj.h"
class AroundBullet :
    public CObj

{
public:
	AroundBullet();
	virtual ~AroundBullet();

public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;




};

