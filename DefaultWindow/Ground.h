#pragma once
#include "Obj.h"
class Ground :
	public CObj
{
public:
	Ground();
	virtual ~Ground();

public:
	virtual void	Initialize() override;
	virtual int		Update()override;
	virtual void	Late_Update()override;
	virtual void	Render(HDC hDC)override;
	virtual void	Release()override;

public:
	bool Get_GroundCheck() { return GroundCheck; }

private:
	bool GroundCheck = true;

};
