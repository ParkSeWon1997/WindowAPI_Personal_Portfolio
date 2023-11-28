#pragma once
#include "Scene.h"
class GameEnd :
    public CScene
{



public:
	GameEnd();
	virtual ~GameEnd();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

