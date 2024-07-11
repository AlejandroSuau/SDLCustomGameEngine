#pragma once

#include "engine/Engine.h"

#include "PipesPair.h"

#include <memory>

class PipesPairFactory {
public:
    PipesPairFactory(Engine& engine, float floor_height);

    std::unique_ptr<PipesPair> CreatePipesPair();

private:
    Engine& engine_;
    const float floor_height_;
};
