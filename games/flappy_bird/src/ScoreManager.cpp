#include "flappy_bird/include/ScoreManager.h"

#include "flappy_bird/include/Constants.h"

ScoreManager::ScoreManager(Engine& engine) 
    : engine_(engine)
    , position_(0.f, kScorePositionY) {
    UpdateScoreValue(0);
    LoadNumberTextures();
}

void ScoreManager::UpdateScoreValue(int val) {
    score_ = val;
    score_string_ = std::to_string(score_);
    position_.x = (static_cast<float>(engine_.GetWindowWidth()) * 0.5f - 
                  (static_cast<float>(score_string_.size()) * kNumberTextureWidth * 0.5f));
}
    
void ScoreManager::IncreaseScoreOneUnit() {
    UpdateScoreValue(++score_);
}


void ScoreManager::LoadNumberTextures() {
    for (std::size_t i = 0; i < number_textures_.size(); ++i) {
        number_textures_[i] = engine_.LoadTexture(kAssetsFolder + std::to_string(i) + ".png");
    }
}

void ScoreManager::Render() {
    float current_x = position_.x;
    for (auto& c : score_string_) {
        int num = c - '0';
        engine_.RenderTexture(
            number_textures_[num],
            {current_x, position_.y, kNumberTextureWidth, kNumberTextureHeight});
        
        current_x += kNumberTextureWidth;
    }
}

void ScoreManager::Reset() {
    UpdateScoreValue(0);
}
