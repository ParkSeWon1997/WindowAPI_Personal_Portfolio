#pragma once
#include "Obj.h"
class BossUI :
    public CObj
{
public:
    BossUI();
	virtual ~BossUI();

public:
      virtual  void	Initialize() override;
      virtual  int		Update() override;
      virtual  void	Late_Update() override;
      virtual  void	Render(HDC hDC) override;
      virtual  void	Release() override;
      void    Set_UI_HpBar(float _MaxHp, float _CurHp);

private:

    CObj* m_pBossHpBar;


};

