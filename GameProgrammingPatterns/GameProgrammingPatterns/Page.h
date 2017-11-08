#pragma once

#include "PageState.h"

class Page
{
public:
    Page() {
        state_ = &PageState::select;
    }
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        state_->handleInput(hWnd, message, wParam, lParam);
    }
private:
    PageState* state_;
};