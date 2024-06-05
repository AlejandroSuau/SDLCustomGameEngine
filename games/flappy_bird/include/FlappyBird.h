#pragma once

#include <SDL2/SDL_image.h>

#include "engine/IGame.h"
#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Bird.h"
#include "ScoreManager.h"
#include "Pipe.h"
#include "PipeFactory.h"

#include <vector>
#include <memory>

class FlappyBird : public IGame {
public:
    FlappyBird();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Bird bird_;
    ScoreManager score_manager_;
    CountdownTimer pipe_spawn_timer_;
    PipeFactory pipe_factory_;
    std::vector<std::unique_ptr<Pipe>> pipes_;
    std::vector<Rectangle> score_checkpoints_;
    Rectangle floor1_;
    Rectangle floor2_;
    Rectangle tutorial_;
    Rectangle gameover_;
    bool is_paused_;

    SDL_Texture* texture_tutorial_;
    SDL_Texture* texture_gameover_;
    SDL_Texture* texture_background_;
    SDL_Texture* texture_floor_;

    void ResetGame();

    void Pause();
    void AddPipesPair();
    void RemoveOutOfScreenPipes();
    
    void SpawnPipesIfNeeded(float);
    void MoveFloor(float dt);
    void MovePipes(float dt);

    void IncreaseScoreOnCheckpointCollision();
    void NofityBirdOnPipeCollision();
    void NofityBirdOnFloorCollision();
};