#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINE tLine);
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CLine();

public:
	const LINE&		Get_Info() const { return m_tInfo; }

public:
	void	Render(HDC hDC);

public:
	LINE	m_tInfo;
};

