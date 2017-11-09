#include "stdafx.h"

#include "PageState.h"
#include "Page.h"

SelectState PageState::select = *new SelectState();
FlyWeightState PageState::flyWeight = *new FlyWeightState();


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

            // �I������`��
            drawSelector(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}

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

            // �I������`��
            //drawSelector(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}
