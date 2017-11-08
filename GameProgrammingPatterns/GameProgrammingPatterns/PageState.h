#pragma once

#include "stdafx.h"
#include <Windowsx.h>
#include "printfex.h"

class SelectState;
class FlyWeightState;

class PageState
{
public:
    virtual ~PageState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}
    static SelectState select;
    static FlyWeightState flyWeight;
};

class SelectState : public PageState
{
public:
    SelectState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
                       printf_ex(_T("*** CLICKED!"));
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
private:
    const int SELECTOR_POS[1][2] = {
        {60, 50}
    };
    const int SELECTOR_SIZE = 32;
    void drawSelector(HWND hWnd, PAINTSTRUCT ps)
    {
        // Obtain the size of the drawing area.
        RECT rc;
        GetClientRect(
            hWnd,
            &rc
        );
        // Save the original object
        HGDIOBJ original = NULL;
        original = SelectObject(
            ps.hdc,
            GetStockObject(DC_PEN)
        );
        // Create a pen.            
        HPEN blackPen = CreatePen(PS_SOLID, 3, 0x333333);

        SelectObject(ps.hdc, blackPen);
        // Draw a rectangle.
        for (const int* s: SELECTOR_POS) {
            int x = *s;
            int y = *(s+1);
            Rectangle(
                ps.hdc,
                x,
                y,
                x + SELECTOR_SIZE,
                y + SELECTOR_SIZE
            );
        }

        DeleteObject(blackPen);
        SelectObject(ps.hdc, original);
    }
};

class FlyWeightState : public PageState
{
public:
    FlyWeightState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    }
};
