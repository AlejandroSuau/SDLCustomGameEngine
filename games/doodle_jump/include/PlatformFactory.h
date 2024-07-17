#pragma once

#include "engine/Engine.h"

#include "Platform.h"

class PlatformFactory {
public:
    PlatformFactory(Engine& engine);

    void InstantiatePlatforms(
        std::vector<std::unique_ptr<Platform>>& platforms,
        float min_height,
        float max_height);

private:
    Engine& engine_;
};
