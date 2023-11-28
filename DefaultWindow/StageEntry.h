#pragma once
#include "Obj.h"
class StageEntry :
    public CObj
{
	enum STAGESTATE{IDLE,OPEN,CLOSE,END};



public:
    StageEntry();
    StageEntry(float _X,float _Y);
    virtual ~StageEntry();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	bool	GetOpenCondition() { return m_bOpenCondition; }
	void	SetOpenCondition(bool _Condition)
	{  m_bOpenCondition= _Condition;
		IsOpenCondition = _Condition;
	}
	bool	GetCloseCondition() { return m_bCloseCondition; }
	void	SetcloseCondition(bool _Condition) { m_bCloseCondition = _Condition; }

	void		EntryOpen();
	void		EntryClose();
	void		Motion_Change();




private:
	bool		IsOpenCondition;
	bool		m_bCloseCondition;
	bool		m_bOpenCondition;
	STAGESTATE			m_ePreState;
	STAGESTATE			m_eCurState;
};

