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
		m_iXNum = _iDrawID;
		m_iYNum = _iOption;
	}
	int		Get_DrawID() { return m_iXNum; }
	int		Get_Option() { return m_iYNum; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void Set_TileKey(int i);

private:
	int			m_iXNum;
	int			m_iYNum;
	TCHAR*		m_TileKey;

};

