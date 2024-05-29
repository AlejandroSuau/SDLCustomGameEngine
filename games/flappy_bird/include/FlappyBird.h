#pragma once

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
    bool is_paused_;

    bool DidBirdCollideWithAPipe() const;
    void Pause();
    void AddPipesPair();
    void RemoveOutOfScreenPipes();
};