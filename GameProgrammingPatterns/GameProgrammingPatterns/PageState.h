#pragma once

#include "stdafx.h"
#include <Windowsx.h>
#include "printfex.h"

class Page;
class SelectState;
class FlyWeightState;

class PageState
{
public:
    virtual ~PageState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page) {}
    static SelectState select;
    static FlyWeightState flyWeight;
};
