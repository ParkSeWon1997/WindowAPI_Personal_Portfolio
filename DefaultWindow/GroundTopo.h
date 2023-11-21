#pragma once
#include "Obj.h"
class GroundTopo :
    public CObj
{
public:
	GroundTopo();
	virtual ~GroundTopo();


public:
		virtual void Initialize() override;
		virtual int Update() override;
		virtual void Late_Update() override;
		virtual void Render(HDC hDC) override;
		virtual void Release() override;
};

