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
		{ 0.f, 670.f },	  //�ٴ�
		{ 2000.f, 670.f },// �ٴ�

		{225.f,536.f},		//���� �� �Ʒ�
		{ 349.f, 536.f },	//���� �� �Ʒ�

		{ 225.f, 423.f },	//���� �� ��
		{ 349.f, 423.f },	//���� �� ��

		{576.f,536.f},		//��� �� �Ʒ�
		{702.f,536.f},		//��� �� �Ʒ�

		{576.f,423.f},		//��� �߰�
		{702.f,423.f},		//��� �߰�

		{576.f,317.f},		//��� ����
		{702.f,317.f},		//��� ����

		{953.f,536.f},		//������ �� �Ʒ�
		{1074.f,536.f},		//������ �� �Ʒ�

		{953.f,423.f},		//������ �� ��
		{1074.f,423.f},		//������ �� ��
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

void BossMapLineMgr::SelectMapLine(MAPLINE _ID)
{
}
