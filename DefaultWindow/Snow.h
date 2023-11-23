#pragma once
#include "Obj.h"
class Snow :
    public CObj
{
public:
	Snow();
	virtual ~Snow();




public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

};

