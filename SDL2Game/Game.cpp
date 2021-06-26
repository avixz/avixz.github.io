//==============================================================================
//
//==============================================================================

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>

#include <iostream>
#include "Game.h"

//==============================================================================
Game::Game() :
m_window(nullptr),
m_isRunning(true),
m_paddlePos(Vector2{20, 334}),
m_ballPos(Vector2{612, 334}),
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
    m_paddleDir = 0;

    while (SDL_PollEvent(&event)) {
       switch (event.type) {
           case SDL_QUIT:
               m_isRunning = false;
               break;
           case SDL_FINGERMOTION:
               event.tfinger.dy > 0? m_paddleDir += 1: m_paddleDir -= 1;
               break;
       }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        m_isRunning = false;
    }
    if (state[SDL_SCANCODE_W]) {
        m_paddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        m_paddleDir += 1;
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
    if (m_paddleDir != 0) {
        m_paddlePos.y += m_paddleDir * 300.0f * deltaTime;
    }
}

//==============================================================================
void Game::generateOutput() {
    const int thickness = 15;
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect wall {
        0, // Top left x
        0, // Top left y
        1024, // Width
        thickness // Width
    };
    SDL_Rect ball {
            static_cast<int>(m_ballPos.x - thickness/2),
            static_cast<int>(m_ballPos.y - thickness/2),
            thickness,
            thickness
    };
    SDL_Rect paddle {
        static_cast<int>(m_paddlePos.x - thickness/2),
        static_cast<int>(m_paddlePos.y - thickness/2),
        thickness,
        thickness * 6
    };
    SDL_RenderFillRect(m_renderer, &wall);
    SDL_RenderFillRect(m_renderer, &ball);
    SDL_RenderFillRect(m_renderer, &paddle);
    SDL_RenderPresent(m_renderer);
}