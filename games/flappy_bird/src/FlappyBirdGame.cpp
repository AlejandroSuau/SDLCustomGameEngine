#include "flappy_bird/include/FlappyBirdGame.h"

#include "flappy_bird/include/Constants.h"

#include <ranges>

FlappyBirdGame::FlappyBirdGame() 
    : engine_("Flappy Bird",
              static_cast<int>(kRectBackground.w),
              static_cast<int>(kRectBackground.h))
    , state_(EGameState::READY)
    , bird_(engine_, static_cast<float>(engine_.GetWindowWidth()) * 0.45f, static_cast<float>(engine_.GetWindowHeight()) * 0.45f)
    , ui_manager_(engine_)
    , score_manager_(engine_)
    , floor1_(0.f,
              static_cast<float>(engine_.GetWindowHeight()) - kFloorHeight,
              static_cast<float>(engine_.GetWindowWidth()),
              kFloorHeight)
    , floor2_(static_cast<float>(engine_.GetWindowWidth()),
              static_cast<float>(engine_.GetWindowHeight()) - kFloorHeight,
              static_cast<float>(engine_.GetWindowWidth()),
              kFloorHeight)
    , pipe_spawn_timer_(2.f)              
    , pipes_pair_factory_(engine_, floor1_.h) {
    texture_background_ = engine_.LoadTexture(kAssetsFolder + "background-night.png");
    texture_floor_ = engine_.LoadTexture(kAssetsFolder + "base.png");
}

void FlappyBirdGame::Start() {
    engine_.Run(*this);
}

void FlappyBirdGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void FlappyBirdGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bool space_key_pressed = (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE);
    if (!space_key_pressed) return;

    switch(state_) {
        case EGameState::GAMEOVER:
            ResetGame();
        break;
        case EGameState::READY:
            state_ = EGameState::PLAYING;
        case EGameState::PLAYING:
            bird_.Jump();
        break;
    }
}

void FlappyBirdGame::Update(float dt) {
    if (state_ == EGameState::GAMEOVER) return;

    bird_.Update(dt);
    
    ProcessCheckPointCollisions();
    ProcessPipeCollisions();
    ProcessFloorCollisions();

    bool should_move_floor = (state_ == EGameState::READY || state_ == EGameState::PLAYING);
    if (should_move_floor) {
        UpdateFloor(dt);
    }

    if (state_ == EGameState::PLAYING) {
        SpawnPipesIfNeeded(dt);
        UpdatePipes(dt);
        RemoveOutOfScreenPipes();
    }
}

void FlappyBirdGame::ProcessCheckPointCollisions() {
    auto bird_collides_with_checkpoint = [&](const auto& pipes_pair) {
        return pipes_pair->DoesCollideWithScoreCheck(bird_.GetHitBox());
    };
    for (auto& pipes : pipes_ | std::views::filter(bird_collides_with_checkpoint)) {
        pipes->RemoveCheckPoint();
        score_manager_.IncreaseScoreOneUnit();
    }
}

void FlappyBirdGame::ProcessPipeCollisions() {
    auto bird_collides_with_pipe = [&](const auto& pipes_pair) {
        return pipes_pair->DoesCollideWithPipe(bird_.GetHitBox());
    };
    for (auto& pipes : pipes_ | std::views::filter(bird_collides_with_pipe)) {
        state_ = EGameState::ENDING;
        bird_.OnCollisionWithPipe();
    }
}

void FlappyBirdGame::ProcessFloorCollisions() {
    if (floor1_.CollidesWith(bird_.GetHitBox()) || floor2_.CollidesWith(bird_.GetHitBox())) {
        state_ = EGameState::GAMEOVER;
        bird_.OnCollisionWithFloor(floor1_.y);
    }
}

void FlappyBirdGame::SpawnPipesIfNeeded(float dt) {
    pipe_spawn_timer_.Update(dt);
    if (pipe_spawn_timer_.DidFinish()) {
        pipes_.emplace_back(pipes_pair_factory_.CreatePipesPair());
    }
}

void FlappyBirdGame::UpdateFloor(float dt) {
    const float dx = kScrollingVelocityX * dt;
    float window_width = static_cast<float>(engine_.GetWindowWidth());
    floor1_.x -= dx;
    floor2_.x -= dx;
    if (floor1_.x + floor1_.w <= 0) {
        floor1_.x = static_cast<float>(engine_.GetWindowWidth());
    } else if (floor2_.x + floor2_.w <= 0) {
        floor2_.x = static_cast<float>(engine_.GetWindowWidth());
    }
}

void FlappyBirdGame::UpdatePipes(float dt) {
    for (auto& pipe : pipes_) {
        pipe->Update(dt);
    }
}

void FlappyBirdGame::RemoveOutOfScreenPipes() {
    pipes_.erase(
        std::remove_if(pipes_.begin(), pipes_.end(), [](const auto& pipe) { return pipe->CanBeDestroyed(); }),
        pipes_.end()
    );
}

void FlappyBirdGame::ResetGame() {
    bird_.Reset();
    score_manager_.Reset();
    pipes_.clear();
    state_ = EGameState::READY;
}

void FlappyBirdGame::Render() {   
    if (DEBUG) {
        engine_.DrawRectangle(floor1_, kFloorHitBoxColor, false);
        engine_.DrawRectangle(floor2_, kFloorHitBoxColor, false);
    } else {
        engine_.RenderTexture(texture_background_, kRectBackground);
        
        engine_.RenderTexture(texture_floor_, floor1_);
        engine_.RenderTexture(texture_floor_, floor2_);
    }
    
    for (auto& pipe : pipes_) {
        pipe->Render();
    }
    
    bird_.Render();

    switch(state_) {
        case EGameState::READY:
            ui_manager_.RenderTutorial();
        break;
        case EGameState::GAMEOVER:
            ui_manager_.RenderGameOver();
        default:
            score_manager_.Render();    
    }
}
