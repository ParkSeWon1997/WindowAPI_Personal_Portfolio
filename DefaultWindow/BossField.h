#pragma once
#include "Scene.h"
class BossField :
    public CScene
{


public:
	BossField();
	virtual ~BossField();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


	void	CreateSnow();
	void	CheckWindowOver();
};

