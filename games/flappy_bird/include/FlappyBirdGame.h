#pragma once

#include <SDL2/SDL_image.h>

#include "engine/IGame.h"
#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Bird.h"
#include "ScoreManager.h"
#include "PipesPair.h"
#include "PipesPairFactory.h"
#include "UIManager.h"

#include <vector>
#include <memory>
#include <string>

enum class EGameState {
    READY,
    PLAYING,
    ENDING,
    GAMEOVER
};

class FlappyBirdGame : public IGame {
public:
    FlappyBirdGame();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    EGameState state_;
    Bird bird_;
    UIManager ui_manager_;
    ScoreManager score_manager_;
    Rectangle floor1_;
    Rectangle floor2_;

    CountdownTimer pipe_spawn_timer_;
    PipesPairFactory pipes_pair_factory_;
    std::vector<std::unique_ptr<PipesPair>> pipes_;

    SDL_Texture* texture_background_;
    SDL_Texture* texture_floor_;

    void ResetGame();

    void RemoveOutOfScreenPipes();
    
    void SpawnPipesIfNeeded(float);
    void UpdateFloor(float dt);
    void UpdatePipes(float dt);

    void ProcessCheckPointCollisions();
    void ProcessPipeCollisions();
    void ProcessFloorCollisions();
};