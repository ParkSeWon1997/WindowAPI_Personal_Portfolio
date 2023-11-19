#pragma once
#include "Obj.h"
class StageEntry :
    public CObj
{
	enum STAGESTATE{IDLE,OPEN,CLOSE,END};



public:
    StageEntry();
    virtual ~StageEntry();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


	void		EntryOpen();
	void		EntryClose();
	void		Motion_Change();





	STAGESTATE			m_ePreState;
	STAGESTATE			m_eCurState;
};

