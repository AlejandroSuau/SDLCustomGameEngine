
#include "flappy_bird/include/ScoreManager.h"

namespace {
    static const float kScorePositionY = 25.f;
    static const float kNumberTextureWidth = 24.f;
    static const float kNumberTextureHeight = 36.f;
}

ScoreManager::ScoreManager(Engine& engine) 
    : engine_(engine)
    , score_(0)
    , score_string_(std::to_string(score_))
    , position_(0.f, kScorePositionY) {
    LoadNumberTextures();
    SetScoreXPosition();
}

void ScoreManager::SetScoreXPosition() {
    position_.x = (static_cast<float>(engine_.GetWindowWidth()) * 0.5f - 
                  (static_cast<float>(score_string_.size()) * kNumberTextureWidth * 0.5f));
}
    
void ScoreManager::IncreaseScoreOneUnit() {
    ++score_;
    score_string_ = std::to_string(score_);
    SetScoreXPosition();
}

void ScoreManager::Render() {
    float current_x = position_.x;
    for (auto& c : score_string_) {
        int num = c - '0';
        engine_.RenderTexture(number_textures_[num],
                              {0.f, 0.f, kNumberTextureWidth, kNumberTextureHeight},
                              {current_x, position_.y, kNumberTextureWidth, kNumberTextureHeight});
        current_x += kNumberTextureWidth;
    }
}

void ScoreManager::LoadNumberTextures() {
    for (std::size_t i = 0; i < number_textures_.size(); ++i) {
        number_textures_[i] = engine_.LoadTexture("assets/flappy_bird/" + std::to_string(i) + ".png");
    }
}
