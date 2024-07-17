#pragma once

#include "engine/IGame.h"
#include "engine/Engine.h"

#include "Player.h"
#include "Platform.h"
#include "PlatformFactory.h"

#include <vector>
#include <memory>

class DoodleJumpGame : public IGame {
public:
    DoodleJumpGame();

    // IGame
    void Start() override;
    void Update(float dt);
    void Render() override;

    // IMouseEventsListener
    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;

    // IKeyboardEventsListener
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Player player_;
    PlatformFactory platform_factory_;
    std::vector<std::unique_ptr<Platform>> platforms_;
    bool is_moving_down_platforms_;

    void MoveDownPlatforms(float dt);
};
