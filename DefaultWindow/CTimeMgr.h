// 23.11.09 (��) _���α�

#pragma once

class CTimeMgr
{
	//�̱���
public:
	void Update();
	void Initialize();
	float GetDT() { return m_fDT; }

public:
	static	CTimeMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTimeMgr;

		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CTimeMgr();
	~CTimeMgr();
private:
	static CTimeMgr* m_pInstance;
private:
	ULONGLONG m_dwCurTime;
	ULONGLONG m_dwPrevTime;
	float m_fDT;
};

