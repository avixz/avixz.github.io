//==============================================================================
// Game.h
//==============================================================================
#pragma once

#include <cstdint>

// Fwd declarations
struct SDL_Window;
struct SDL_Renderer;
typedef uint32_t Uint32;

struct Vector2 {
    float x;
    float y;
};

/**
*
*/
class Game {
public:
    Game();
    bool initialize();
    void doFrame();
    void shutdown();
    bool isRunning();
private:
    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isRunning;
    Vector2 m_paddlePos;
    Vector2 m_ballPos;
    Vector2 m_ballVel;
    Uint32 m_ticksCount;
    float m_paddleDir;
};