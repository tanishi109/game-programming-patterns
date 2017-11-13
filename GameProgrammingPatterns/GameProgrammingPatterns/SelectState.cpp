#include "stdafx.h"
#include "SelectState.h"
#include "Page.h"
#include "FlyWeightState.h"
#include "ComponentState.h"

void SelectState::handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            const int mouse_x = GET_X_LPARAM(lParam);
            const int mouse_y = GET_Y_LPARAM(lParam);

            for (int index = 0; index < (sizeof(POS) / sizeof(*POS)); index++) {
                const int* pos = POS[index];
                const int sel_x = *(pos);
                const int sel_y = *(pos+1);

                if (
                    (sel_x < mouse_x && mouse_x < sel_x + SIZE) &&
                    (sel_y < mouse_y && mouse_y < sel_y + SIZE)
                   ) {
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
                    if (index == 0) {
                        page->state_ = &PageState::flyWeight;
                    } else if (index == 1) {
                        page->state_ = &PageState::component;
                    }
                }
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            // ‘I‘ðŽˆ‚ð•`‰æ
            drawSelector(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}

