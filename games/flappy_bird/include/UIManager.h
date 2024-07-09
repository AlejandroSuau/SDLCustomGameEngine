#pragma once

#include "engine/Engine.h"

#include <SDL2/SDL_image.h>

class UIManager {
public:
    UIManager(Engine& engine);

    void RenderTutorial();
    void RenderGameOver();

private:
    Engine& engine_;
    Rectangle rect_tutorial_;
    Rectangle rect_gameover_;
    SDL_Texture* texture_tutorial_;
    SDL_Texture* texture_gameover_;

    void LoadTextures();
};
