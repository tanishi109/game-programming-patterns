#pragma once

#include "stdafx.h"
#include <Windowsx.h>

class PageState;

class Page
{
public:
    Page();
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    PageState* state_;
};