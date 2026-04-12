#include "CGameInput.h"
#include <algorithm>
InputState CGameInput::pollInput()
{
    InputState input{};
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            input.keyQ = true;
        }
    }
    static int cursorX = 0;
    static int cursorY = 0;
    static bool gp_crossPrev = false;
    static bool gp_circlePrev = false;
    static bool gp_trianglePrev = false;
    static bool gp_startPrev = false;
    static bool gp_homePrev = false;
    static bool gp_selectPrev = false;
    static bool gp_upPrev = false;
    static bool gp_downPrev = false;
    static bool gp_leftPrev = false;
    static bool gp_rightPrev = false;



    if (SDL_NumJoysticks() > 0)
    {
        static SDL_GameController *controller = SDL_GameControllerOpen(0);

        if (controller && SDL_GameControllerGetAttached(controller))
        {
            bool cross = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
            bool circle = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
            bool triangle = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
            bool start = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
            bool select = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
            bool home = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE);

            bool up = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
            bool down = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
            bool left = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
            bool right = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
            
            input.leftClick = cross && !gp_crossPrev;
            input.rightClick = circle && !gp_circlePrev;
            input.keyR = triangle && !gp_trianglePrev;
            input.keyQ = start && !gp_startPrev;
            input.home = home && !gp_homePrev;
            input.keyEnter = start && !gp_startPrev;
            input.select = select && !gp_selectPrev;
            gp_crossPrev = cross;
            gp_circlePrev = circle;
            gp_trianglePrev = triangle;
            gp_startPrev = start;

            if (up && !gp_upPrev)
                cursorY = std::max(0, cursorY - 1);
            if (down && !gp_downPrev)
                cursorY = std::min(9, cursorY + 1);
            if (left && !gp_leftPrev)
                cursorX = std::max(0, cursorX - 1);
            if (right && !gp_rightPrev)
                cursorX = std::min(9, cursorX + 1);

            gp_upPrev = up;
            gp_downPrev = down;
            gp_leftPrev = left;
            gp_rightPrev = right;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    static bool kb_zPrev = false;
    static bool kb_xPrev = false;
    static bool kb_cPrev = false;
    static bool kb_escPrev = false;
    static bool kb_enter = false;

    static bool kb_upPrev = false;
    static bool kb_downPrev = false;
    static bool kb_leftPrev = false;
    static bool kb_rightPrev = false;

    bool z = state[SDL_SCANCODE_Z];
    bool x = state[SDL_SCANCODE_X];
    bool c = state[SDL_SCANCODE_C];
    bool esc = state[SDL_SCANCODE_ESCAPE];
    bool enter = state[SDL_SCANCODE_V];

    bool up = state[SDL_SCANCODE_UP];
    bool down = state[SDL_SCANCODE_DOWN];
    bool left = state[SDL_SCANCODE_LEFT];
    bool right = state[SDL_SCANCODE_RIGHT];

    input.leftClick |= z && !kb_zPrev;
    input.rightClick |= x && !kb_xPrev;
    input.keyR |= c && !kb_cPrev;
    input.keyQ |= esc && !kb_escPrev;
    input.keyEnter |= enter && !kb_enter;
    kb_zPrev = z;
    kb_xPrev = x;
    kb_cPrev = c;
    kb_escPrev = esc;
    kb_enter = enter;

    if (up && !kb_upPrev)
        cursorY = std::max(0, cursorY - 1);
    if (down && !kb_downPrev)
        cursorY = std::min(9, cursorY + 1);
    if (left && !kb_leftPrev)
        cursorX = std::max(0, cursorX - 1);
    if (right && !kb_rightPrev)
        cursorX = std::min(9, cursorX + 1);

    kb_upPrev = up;
    kb_downPrev = down;
    kb_leftPrev = left;
    kb_rightPrev = right;
    input.cursorX = cursorX;
    input.cursorY = cursorY;

    return input;
}