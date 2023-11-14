#pragma once
#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void		Set_Tile(int _iDrawID, int _iOption)
	{
		m_iDrawID = _iDrawID;
		m_iOption = _iOption;
	}
	int		Get_DrawID() { return m_iDrawID; }
	int		Get_Option() { return m_iOption; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int			m_iDrawID;
	int			m_iOption;

};

