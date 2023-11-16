#pragma once
#include "Obj.h"
class CMouse :
	public CObj
{
private:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Offset();

public:
	static CObj* Get_Instance()
	{
		if (!m_Instance)
			m_Instance = new CMouse;

		m_Instance->Initialize();

		return m_Instance;
	}

	static void Destroy_Instance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

private:
	static CObj* m_Instance;
	POINT ptMouse{};
	
};

