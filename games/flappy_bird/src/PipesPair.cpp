#include "flappy_bird/include/PipesPair.h"

#include "flappy_bird/include/Constants.h"

PipesPair::PipesPair(Engine& engine, float x, float height_top, float height_bottom)
    : engine_(engine)
    , pipe_top_(x, 0.f, kPipeWidth, height_top)
    , pipe_bottom_(x, height_top + kPipesPairGap, kPipeWidth, height_bottom)
    , pipe_texture_(nullptr)
    , score_check_hit_box_(std::make_unique<Rectangle>(
        pipe_top_.x + kPipeWidth / 2.f,
        height_top,
        1.f,
        kPipesPairGap)) {
    LoadTextures();
}

void PipesPair::LoadTextures() {
    pipe_texture_ = engine_.LoadTexture(kAssetsFolder + "pipe-green.png");
}

bool PipesPair::DoesCollideWithPipe(const Rectangle& rect) const {
    return (pipe_top_.CollidesWith(rect) || pipe_bottom_.CollidesWith(rect));
}

bool PipesPair::DoesCollideWithScoreCheck(const Rectangle& rect) const {
    return (score_check_hit_box_ && score_check_hit_box_->CollidesWith(rect));
}

void PipesPair::RemoveCheckPoint() {
    score_check_hit_box_ = nullptr;
}

bool PipesPair::CanBeDestroyed() const {
    return ((pipe_top_.x + pipe_top_.w) <= 0);
}

void PipesPair::Update(float dt) {
    const float dx = kScrollingVelocityX * dt;
    pipe_top_.x -= dx;
    pipe_bottom_.x -= dx;
    
    if (score_check_hit_box_) {
        score_check_hit_box_->x -= dx;
    }
}

void PipesPair::Render() {
    engine_.RenderTexture(pipe_texture_, pipe_top_, 180);
    engine_.RenderTexture(pipe_texture_, pipe_bottom_);
    
    if (score_check_hit_box_ && DEBUG) {
        engine_.DrawRectangle(*score_check_hit_box_.get());
    }
}
