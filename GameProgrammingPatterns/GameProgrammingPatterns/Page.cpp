#include "stdafx.h"
#include "Page.h"

#include "PageState.h";
#include "SelectState.h"

Page::Page() {
    state_ = &PageState::select;
}
void Page::handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    state_->handleInput(hWnd, message, wParam, lParam, this);
};
