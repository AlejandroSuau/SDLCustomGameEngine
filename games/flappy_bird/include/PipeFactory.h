#pragma once

#include "engine/Engine.h"

#include "Pipe.h"

#include <memory>

class PipeFactory {
public:
    PipeFactory(Engine& engine, Rectangle& floor_);

    std::unique_ptr<Pipe> CreatePipe(float x, float y, float height);
    std::pair<std::unique_ptr<Pipe>, std::unique_ptr<Pipe>> CreatePipePair();

private:
    Engine& engine_;
    Rectangle& floor_;
};
