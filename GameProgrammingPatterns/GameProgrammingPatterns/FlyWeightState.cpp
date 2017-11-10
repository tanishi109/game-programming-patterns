#include "stdafx.h"
#include "FlyWeightState.h"
#include "Page.h"
#include "SelectState.h"

void FlyWeightState::handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
            page->state_ = &PageState::select;
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            drawField(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}
