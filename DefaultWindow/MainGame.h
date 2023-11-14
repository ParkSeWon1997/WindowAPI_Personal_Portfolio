#pragma once

#include "Define.h"

#include "Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};

// https://refactoring.guru/ko

// 추상 팩토리 패턴 : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화시키는 패턴, 즉 객체 생성 시, 동반되는 공통적인 작업을 추상화 시킨 것
// 반복자 패턴 : 내부 표현 방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴

// 메디에이터(중재자) 패턴  : 상호 작용하는 객체들이 서로 복잡한 관계를 맺고 있을 경우, 별도의 형식으로 정의하여 중재하는 객체를 두는 패턴, N : 1의 관계를 지향
// 싱글톤 패턴 : 단, 하나의 인스턴스(객체)를 생성하는 패턴, 인스턴스가 필요할 때 매번 생성하지 않고 기존의 인스턴스를 불러와서 사용하는 패턴

// 상태 패턴(state 패턴) : fsm(finite state machine : 유한 상태 기계)을 기반으로 하는 객체의 상태를 표현, 자신이 취할 수 있는 유한한 개수의 상태를 가진다는 의미의 디자인 패턴
// 여러 상태 중 오직 하나만 상태를 취해야 하고, 현재 상태에서 특정 조건이 성립했을 때만 다른 상태로 변할 수 있다는 의미의 패턴