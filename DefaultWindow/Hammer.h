#pragma once
#include "Obj.h"
class Hammer :
    public CObj
{


public:
    Hammer();
    virtual ~Hammer();
public:

    virtual void	Initialize();
    virtual int		Update();
    virtual void	Late_Update();
    virtual void	Render(HDC hDC);
    virtual void	Release();


    void MoveToEndEntry();
};

