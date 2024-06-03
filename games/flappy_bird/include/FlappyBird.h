#pragma once

#include <SDL2/SDL_image.h>

#include "engine/IGame.h"
#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Bird.h"
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
    CountdownTimer pipe_spawn_timer_;
    PipeFactory pipe_factory_;
    std::vector<std::unique_ptr<Pipe>> pipes_;
    Rectangle floor1_;
    Rectangle floor2_;
    std::unique_ptr<Rectangle> bonus_item_;
    bool is_paused_;

    SDL_Texture* texture_background_;
    SDL_Texture* texture_floor_;

    void Pause();
    void AddPipesPair();
    void RemoveOutOfScreenPipes();
    bool ShouldBirdDie() const;
    bool DidBirdColliderWithFloor() const;
    bool DidBirdCollideWithAPipe() const;

    void SpawnBonusItem(Rectangle pipe);
};