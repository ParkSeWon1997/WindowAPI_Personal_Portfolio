#pragma once
#include "Obj.h"
class CollisionBox :
    public CObj
{
public:
    CollisionBox();
    virtual ~CollisionBox();
public:

    virtual void	Initialize();
    virtual int		Update();
    virtual void	Late_Update();
    virtual void	Render(HDC hDC);
    virtual void	Release();

    
public:
    void    Set_ImageKey(TCHAR* _ImageKey) { m_ImageKey = _ImageKey; }


private:

    TCHAR* m_ImageKey;



};

