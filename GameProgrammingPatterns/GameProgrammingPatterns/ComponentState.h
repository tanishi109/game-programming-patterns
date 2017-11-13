#pragma once

#include "PageState.h"

class ComponentState : public PageState
{
public:
    ComponentState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page);
};
