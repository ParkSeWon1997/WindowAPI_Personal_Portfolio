#pragma once
#include "Scene.h"

class CObj;
class Village :
    public CScene
{
public:
	Village();
	virtual ~Village();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:
	CObj* m_pCPlayer;

};

