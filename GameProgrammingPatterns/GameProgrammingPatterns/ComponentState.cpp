#include "stdafx.h"
#include "ComponentState.h"
#include "Page.h"
#include "SelectState.h"

class Controller
{
public:
    Controller()
    :  key_(NULL)
    {}
    int key_;
    const int getKey() {
        return key_;
    }
};

Controller* controller = new Controller();

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class Player
{
public:
    int velocity=0;
    int x=30, y=30;

    Player(InputComponent* input)
    :  input_(input)
    {}
    void update(HWND hWnd);
private:
    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};

class InputComponent
{
public:
    virtual ~InputComponent() {}
    virtual void update(Player& player) = 0;
};
class PlayerInputComponent : public InputComponent
{
public:
    void update(Player& player) {
        switch (controller->getKey())
        {
            case VK_LEFT:
                {
                    player.velocity -= WALK_ACCELERATION;
                }
                break;
            case VK_RIGHT:
                {
                    player.velocity += WALK_ACCELERATION;
                }
                break;
        }
    }
private:
    static const int WALK_ACCELERATION = 1;
};

class PhysicsComponent
{
public:
    void update(Player& player) {
        player.x += player.velocity;
    }
};

class GraphicsComponent
{
public:
    void update(Player& player, HWND hWnd) {
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

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

        HPEN leftPen = CreatePen(PS_SOLID, 10,0x000000);
        HPEN rightPen = CreatePen(PS_SOLID, 10, 0xf4f442);
        if (player.velocity < 0) {
            SelectObject(ps.hdc, leftPen);
        } else {
            SelectObject(ps.hdc, rightPen);
        }
        Rectangle(
            ps.hdc,
            player.x,
            player.y,
            player.x + 10,
            player.y + 10
        );

        DeleteObject(leftPen);
        DeleteObject(rightPen);
        SelectObject(ps.hdc, original);
    }
private:
    static const int WALK_ACCELERATION = 1;
};


Player* player = new Player(new PlayerInputComponent());

void Player::update(HWND hWnd) {
    input_->update(*this);
    physics_->update(*this);
    graphics_->update(*this, hWnd);
};

void ComponentState::handleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, Page* page)
{
    controller->key_ = NULL;

    switch (message)
    {
    case WM_KEYDOWN:
        {
            controller->key_ = wParam;
        }
        break;
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

            EndPaint(hWnd, &ps);
        }
        break;
    }

    player->update(hWnd);
}
