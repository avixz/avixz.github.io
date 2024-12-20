//==============================================================================
//
//==============================================================================

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include "Game.h"

const int s_ballThickness = 12;
const int s_wallThickness = 15;
const int s_paddleHeight = 90;

//==============================================================================
Game::Game() :
m_window(nullptr),
m_isRunning(true),
m_ticksCount(0)
{}

//==============================================================================
bool Game::isRunning() {
   return m_isRunning;
}
//==============================================================================
bool Game::initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    m_window = SDL_CreateWindow("Test window",
                                100, // top left x-coordinate
                                100, // top left y-coordinate
                                1024, // width
                                768, // height
                                0 // flags
                                );
    if (!m_window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Prevent default events
    SDL_EventState(SDL_FINGERMOTION, SDL_ENABLE);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return true;
}

//==============================================================================
void Game::shutdown() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

//==============================================================================
void Game::doFrame() {
   processInput();
   updateGame();
   generateOutput();
}

//==============================================================================
void Game::processInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
       switch (event.type) {
           case SDL_QUIT:
               m_isRunning = false;
               break;
           case SDL_FINGERMOTION:
               break;
       }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        m_isRunning = false;
    }
    if (state[SDL_SCANCODE_W]) {
    }
    if (state[SDL_SCANCODE_S]) {
    }
}

//==============================================================================
void Game::updateGame() {
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16));

    // Difference from last frame in seconds
    float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

    // Update tick count for next frame
    m_ticksCount = SDL_GetTicks();

    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    // TODO: Update objects in the game world as function of deltaTime
}

//==============================================================================
void Game::generateOutput() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect wallTop {
        0, // Top left x
        0, // Top left y
        1024, // Width
        s_wallThickness // Width
    };
    SDL_RenderPresent(m_renderer);
}