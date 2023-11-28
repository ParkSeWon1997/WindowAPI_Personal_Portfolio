#pragma once
#include "Scene.h"

class CObj;
class Normal :
    public CScene
{


public:
	Normal();
	virtual ~Normal();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool	m_bOpenDoor = false;

	int m_iCloseCheckCount = 0;
	int	m_iOpenCheckCount = 0;
	CObj* m_pEndBotton;
};

