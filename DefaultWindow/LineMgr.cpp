#include "stdafx.h"
#include "LineMgr.h"
#include "Player.h"


CLineMgr*	CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	LINEPOINT		tLinePoint[6]
	{
		{ 0.f, 700.f },
		{ 2000.f, 700.f },
		{220.f,667.f},
		{ 385.f, 500.f },
		{ 912.f, 500.f },
		{ 1080.f, 667.f },
	};

	m_LineList.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_LineList.push_back(new CLine(tLinePoint[2], tLinePoint[3]));
	m_LineList.push_back(new CLine(tLinePoint[3], tLinePoint[4]));
	m_LineList.push_back(new CLine(tLinePoint[4], tLinePoint[5]));

	//Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	//for (auto& iter : m_LineList)
	//	iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float* pHeight, float& _fX,float _fY, float _fCY)
{

	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX < iter->Get_Info().tRPoint.fX)
		{
			if (pTargetLine != nullptr)
			{
				if (max(pTargetLine->Get_Info().tLPoint.fY, pTargetLine->Get_Info().tRPoint.fY) > max(iter->Get_Info().tLPoint.fY, iter->Get_Info().tRPoint.fY)
					&& iter->Get_Info().tLPoint.fY > CPlayer::Get_Instance()->Get_Info().fY)
				{
					pTargetLine = iter;
				}
			}
			else pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;

	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;

	*pHeight = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;





	//if (m_LineList.empty())
	//	return false;
	//
	//CLine*		pTargetLine = nullptr;
	//
	//for (auto& iter : m_LineList)
	//{
	//	if (_fX >= iter->Get_Info().tLPoint.fX &&
	//		_fX < iter->Get_Info().tRPoint.fX 
	//		|| _fY <= iter->Get_Info().tLPoint.fY && _fY > iter->Get_Info().tRPoint.fY)
	//	{
	//		
	//		pTargetLine = iter;
	//		//if (pTargetLine->Get_Info().tLPoint.fY <=_fY&& pTargetLine->Get_Info().tRPoint.fY>_fY)
	//			break;
	//	}

	//}
	//
	//if (!pTargetLine)//|| pTargetLine->Get_Info().tLPoint.fX>= _fX)
	//	return false;
	//
	//float x1 = pTargetLine->Get_Info().tLPoint.fX;
	//float y1 = pTargetLine->Get_Info().tLPoint.fY;
	//
	//float x2 = pTargetLine->Get_Info().tRPoint.fX;
	//float y2 = pTargetLine->Get_Info().tRPoint.fY;
	//
	//*pHeight = (((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1)- (_fCY*0.5);
	//
	//return true;
}

void CLineMgr::Load_Line()
{
	// CreateFile: API ���� �����Լ�
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",		// ���� ��ο� �̸��� ���
		GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ���, GENERIC_READ : ���� �Է�)
		NULL,					// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���α׷��� �����ϰ��� �� �� �������� ���θ� ����, NULL ���� �� �������� ����
		NULL,					// ���� ��� ����, NULL�� ��� �⺻ �� ���� ����
		OPEN_EXISTING,			// ���� ���(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ������ ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ����̱� ������ NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"����", L"����", MB_OK);
		return;
	}

	DWORD		dwByte(0);
	LINE		tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tLine));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::SelectMapLine(MAPLINE _ID)
{



}
