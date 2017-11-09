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
            printf_ex(_T("*** FlyWeight!!\n"));
            page->state_ = &PageState::select;
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // ‘I‘ðŽˆ‚ð•`‰æ
            //drawSelector(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}
