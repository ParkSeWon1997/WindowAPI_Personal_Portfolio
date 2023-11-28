#include "stdafx.h"
#include "BossMapLineMgr.h"
#include "Player.h"


BossMapLineMgr* BossMapLineMgr::m_pInstance = nullptr;
BossMapLineMgr::BossMapLineMgr()
{
}

BossMapLineMgr::~BossMapLineMgr()
{
	Release();
}

void BossMapLineMgr::Initialize(void)
{
	LINEPOINT		tLinePoint[18]
	{
		{ 0.f, 670.f },	  //바닥
		{ 2000.f, 670.f },// 바닥

		{225.f,536.f},		//왼쪽 맨 아래
		{ 349.f, 536.f },	//왼쪽 맨 아래

		{ 225.f, 423.f },	//왼쪽 맨 위
		{ 349.f, 423.f },	//왼쪽 맨 위

		{576.f,536.f},		//가운데 맨 아래
		{702.f,536.f},		//가운데 맨 아래

		{576.f,423.f},		//가운데 중간
		{702.f,423.f},		//가운데 중간

		{576.f,317.f},		//가운데 맨위
		{702.f,317.f},		//가운데 맨위

		{953.f,536.f},		//오른쪽 맨 아래
		{1074.f,536.f},		//오른쪽 맨 아래

		{953.f,423.f},		//오른쪽 맨 위
		{1074.f,423.f},		//오른쪽 맨 위
	};

	m_LineList.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_LineList.push_back(new CLine(tLinePoint[2], tLinePoint[3]));
	m_LineList.push_back(new CLine(tLinePoint[4], tLinePoint[5]));
	m_LineList.push_back(new CLine(tLinePoint[6], tLinePoint[7]));
	m_LineList.push_back(new CLine(tLinePoint[8], tLinePoint[9]));
	m_LineList.push_back(new CLine(tLinePoint[10], tLinePoint[11]));
	m_LineList.push_back(new CLine(tLinePoint[12], tLinePoint[13]));
	m_LineList.push_back(new CLine(tLinePoint[14], tLinePoint[15]));
}

void BossMapLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void BossMapLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool BossMapLineMgr::Collision_Line(float* pHeight, float& _fX,float _fY, float _fCY)
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
					if (max(pTargetLine->Get_Info().tLPoint.fY, pTargetLine->Get_Info().tRPoint.fY)> max(iter->Get_Info().tLPoint.fY, iter->Get_Info().tRPoint.fY)
						&& iter->Get_Info().tLPoint.fY > CPlayer::Get_Instance()->Get_Info().fY)
					{
						pTargetLine = iter;
						m_pTargetLine= iter;
					}
				}
				else {
					pTargetLine = iter;
					m_pTargetLine = iter;
				}
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

void BossMapLineMgr::Load_Line()
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

void BossMapLineMgr::SelectMapLine(MAPLINE _ID)
{
}
