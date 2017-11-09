#pragma once

#include "PageState.h"

class FlyWeightState : public PageState
{
public:
    FlyWeightState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page);
};
