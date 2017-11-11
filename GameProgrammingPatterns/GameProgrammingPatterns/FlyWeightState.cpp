#include "stdafx.h"
#include "FlyWeightState.h"
#include "Page.h"
#include "SelectState.h"

#include <random>
#include <map>
using namespace std;

void World::generateTerrain()
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(1, 10);

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (dist(mt) == 10) {
                tiles_[x][y] = &hillTerrain_;
            } else {
                tiles_[x][y] = &grassTerrain_;
            }
        }
    }

    int x = dist(mt);
    for (int y = 0; y < HEIGHT; y++) {
        tiles_[x][y] = &riverTerrain_;
    }
}

void World::drawTerrain(HWND hWnd, PAINTSTRUCT ps)
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
    // Create a penMap.
    map<int, HPEN> penMap;

    // Draw world.
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            Terrain* tile = tiles_[x][y];
            int colorCode = tile->getColor();

            if (!penMap[colorCode]) {
                HPEN tilePen = CreatePen(PS_SOLID, 1, colorCode);

                penMap[colorCode] = tilePen;
            }
            SelectObject(ps.hdc, penMap[colorCode]);
            Rectangle(
                ps.hdc,
                x * SIZE,
                y * SIZE,
                x * SIZE + SIZE,
                y * SIZE + SIZE
            );
        }
    }

    //DeleteObject(blackPen);
    SelectObject(ps.hdc, original);
}

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

            World* world = new World();
            world->generateTerrain();
            world->drawTerrain(hWnd, ps);

            EndPaint(hWnd, &ps);
        }
        break;
    }
}
