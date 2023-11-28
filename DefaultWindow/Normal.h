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
	CObj* m_pEndBotton;
};

