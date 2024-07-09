#include "flappy_bird/include/UIManager.h"

#include "flappy_bird/include/Constants.h"

UIManager::UIManager(Engine& engine) 
    : engine_(engine)
    , rect_tutorial_(kRectTutorial.x + kRectBackground.w * 0.5f - kRectTutorial.w * 0.5f,
                     kRectTutorial.y,
                     kRectTutorial.w,
                     kRectTutorial.h)
    , rect_gameover_(kRectGameOver.x + kRectBackground.w * 0.5f - kRectGameOver.w * 0.5f,
                     kRectBackground.w * 0.5f,
                     kRectGameOver.w,
                     kRectGameOver.h) {
    LoadTextures();
}

void UIManager::LoadTextures() {
    texture_tutorial_ = engine_.LoadTexture(kAssetsFolder + "message.png");
    texture_gameover_ = engine_.LoadTexture(kAssetsFolder + "gameover.png");    
}

void UIManager::RenderTutorial() {
    engine_.RenderTexture(texture_tutorial_, rect_tutorial_);
}

void UIManager::RenderGameOver() {
    engine_.RenderTexture(texture_gameover_, rect_gameover_);
}
