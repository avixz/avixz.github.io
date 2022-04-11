//==============================================================================
//
//==============================================================================
#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
#endif
#include <iostream>
#include "Game.h"

//==============================================================================
void mainLoopCallback(void* arg)
{
    static_cast<Game*>(arg)->doFrame();
}

//==============================================================================
int main(int argc, char** argv) {
    Game game;
    bool success = game.initialize();

    if (success)
    {
#ifdef EMSCRIPTEN
        emscripten_set_main_loop_arg(&mainLoopCallback, &game, -1, 1);
#else
        while (game.isRunning()) {
            game.doFrame();
        }
#endif
    }

    game.shutdown();

    return 0;
}
