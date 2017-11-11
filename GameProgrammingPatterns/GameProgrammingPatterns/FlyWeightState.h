#pragma once

#include "PageState.h"
#include <string>

class Terrain
{
public:
    Terrain(int moveCost, bool isWater, int color)
    : moveCost_(moveCost),
      isWater_(isWater),
      color_(color)
    {}
    int getColor() const { return color_; };
private:
    int moveCost_;
    bool isWater_;
    int color_;
};

class World
{
public:
    World()
      : grassTerrain_(1, false, 0x42c436),
      hillTerrain_(3, false, 0x1ad6e0),
      riverTerrain_(2, true, 0xc48c2d)
    {}
    void generateTerrain();
    void drawTerrain(HWND hWnd, PAINTSTRUCT ps);
private:
    static const int WIDTH = 10;
    static const int HEIGHT = 10;
    static const int SIZE = 32;
    Terrain* tiles_[WIDTH][HEIGHT];
    Terrain grassTerrain_;
    Terrain hillTerrain_;
    Terrain riverTerrain_;
};

class FlyWeightState : public PageState
{
public:
    FlyWeightState() {}
    virtual void handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page);
};
