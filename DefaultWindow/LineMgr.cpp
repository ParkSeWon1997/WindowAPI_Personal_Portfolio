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
		{ 1280.f, 700.f },
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

bool CLineMgr::DropItemCollision_Line(float* pHeight, float& _fX, float _fY, float _fCY)
{
	if (m_LineList.empty())
		return false;


	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX < iter->Get_Info().tRPoint.fX)
		{
			pTargetLine = iter;
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
}

bool CLineMgr::IsCollision_Line_to_item(float pHeight, float _fX, float _fY)
{

	if (m_LineList.empty())
		return false;


	CLine* pTargetLine = nullptr;
	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX < iter->Get_Info().tRPoint.fX)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;
	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;

	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;

	pHeight = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	if (_fY == pHeight) {
		return true;
	}

	
}

void CLineMgr::Load_Line()
{
	// CreateFile: API 파일 개방함수
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",		// 파일 경로와 이름을 명시
		GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 파일 출력, GENERIC_READ : 파일 입력)
		NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로그램이 오픈하고자 할 때 공유할지 여부를 물음, NULL 지정 시 공유하지 않음
		NULL,					// 보안 모드 설정, NULL인 경우 기본 값 보안 상태
		OPEN_EXISTING,			// 생성 방식(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 열기)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일을 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓸것이기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"에러", L"실패", MB_OK);
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

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::SelectMapLine(MAPLINE _ID)
{



}
