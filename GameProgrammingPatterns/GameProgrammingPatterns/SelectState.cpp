#include "stdafx.h"
#include "SelectState.h"
#include "Page.h"
#include "FlyWeightState.h"

void SelectState::handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            const int mouse_x = GET_X_LPARAM(lParam);
            const int mouse_y = GET_Y_LPARAM(lParam);

            for (const int* s : SELECTOR_POS) {
                const int sel_x = *s;
                const int sel_y = *(s+1);

                if (
                    (sel_x < mouse_x && mouse_x < sel_x + SELECTOR_SIZE) &&
                    (sel_y < mouse_y && mouse_y < sel_y + SELECTOR_SIZE)
                   ) {
                    printf_ex(_T("*** Select!!\n"));
                    page->state_ = &PageState::flyWeight;
                }
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // ‘I‘ðŽˆ‚ð•`‰æ
            drawSelector(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}

