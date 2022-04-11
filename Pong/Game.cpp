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
m_paddlePos(Vector2{20, 334}),
m_ballPos(Vector2{612, 334}),
m_ballVel(Vector2{-200.0f, 235.0f}),
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

        // Make sure the paddle doesn't move off screen
        if (m_paddlePos.y < (0.0f + s_wallThickness)) {
            m_paddlePos.y = s_wallThickness;
        }
        else if ((m_paddlePos.y + s_paddleHeight) > (768.0f - s_wallThickness)) {
            m_paddlePos.y = 768.0f - s_paddleHeight - s_wallThickness;
        }
    }
    m_ballPos.x += m_ballVel.x * deltaTime;
    m_ballPos.y += m_ballVel.y * deltaTime;
    float diff = abs(m_ballPos.y - m_paddlePos.y);

    // Bounce the ball against top wall
    if (m_ballPos.y <= s_wallThickness && m_ballVel.y < 0.0f) {
        m_ballVel.y *= -1;
    }
    // Bounce the ball against bottom wall
    else if ((m_ballPos.y + s_ballThickness) >= (768.0f - s_wallThickness) && m_ballVel.y > 0.0f) {
        m_ballVel.y *= -1;
    }
    // Bounce the ball against the right wall
    else if ((m_ballPos.x + s_ballThickness) >= (1024.0f - s_wallThickness) && m_ballVel.x > 0.0f) {
        m_ballVel.x *= -1;
    }
    // Bounce the ball against the paddle
    else if (diff <= s_paddleHeight / 2.0f && m_ballPos.x >= 20.0f && m_ballPos.x <= 35.0f && m_ballVel.x < 0.0f) {
        m_ballVel.x *= -1.0f;
    }
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
    SDL_Rect wallBottom {
            0, // Top left x
            768 - s_wallThickness, // Top left y
            1024, // Width
            s_wallThickness // Width
    };
    SDL_Rect wallRight {
            1024 - s_wallThickness, // Top left x
            0, // Top left y
            s_wallThickness, // Width
            768 // Width
    };
    SDL_Rect ball {
            static_cast<int>(m_ballPos.x - s_ballThickness),
            static_cast<int>(m_ballPos.y - s_ballThickness),
            s_ballThickness,
            s_ballThickness
    };
    SDL_Rect paddle {
        static_cast<int>(m_paddlePos.x - s_wallThickness/2),
        static_cast<int>(m_paddlePos.y - s_wallThickness/2),
        s_wallThickness,
        s_paddleHeight
    };
    SDL_RenderFillRect(m_renderer, &wallTop);
    SDL_RenderFillRect(m_renderer, &wallBottom);
    SDL_RenderFillRect(m_renderer, &wallRight);
    SDL_RenderFillRect(m_renderer, &ball);
    SDL_RenderFillRect(m_renderer, &paddle);
    SDL_RenderPresent(m_renderer);
}