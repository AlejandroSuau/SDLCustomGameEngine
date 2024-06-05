#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

#include "Pipe.h"

#include <memory>
#include <tuple>

class PipeFactory {
public:
    PipeFactory(Engine& engine, Rectangle& floor_);

    std::unique_ptr<Pipe> CreatePipe(float x, float y, float height);
    std::tuple<std::unique_ptr<Pipe>, std::unique_ptr<Pipe>, Rectangle> CreatePipePair();

private:
    Engine& engine_;
    Rectangle& floor_;
};
