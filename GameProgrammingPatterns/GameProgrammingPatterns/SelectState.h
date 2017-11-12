#pragma once

#include "PageState.h"

class SelectState : public PageState
{
public:
    SelectState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page);
private:
    const int POS[2][2] = {
        {60, 50},
        {100, 50}
    };
    const int SIZE = 30;
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
        for (const int* s: POS) {
            int x = *s;
            int y = *(s+1);
            Rectangle(
                ps.hdc,
                x,
                y,
                x + SIZE,
                y + SIZE
            );
        }

        DeleteObject(blackPen);
        SelectObject(ps.hdc, original);
    }
};
