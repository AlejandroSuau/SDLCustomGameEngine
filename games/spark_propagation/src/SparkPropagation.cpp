#include "spark_propagation/include/SparkPropagation.h"

#include <iostream>

SparkPropagation::SparkPropagation() 
    : engine_("Spark Propagation", 800, 600)
    , grid_(engine_, 800, 600)
    , grid_tick_timer_(.05f) {}

void SparkPropagation::Start() {
    engine_.Run(*this);
}

void SparkPropagation::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    // particle_placer_.OnMouseEvent(event_type, x, y);
}

void SparkPropagation::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE) {
        grid_.ClearAllParticles();
    } else if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_1) {
        // grid_tick_timer_.AddSecondsToFinish(0.005f);
    } else if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_2) {
        // grid_tick_timer_.SubtractSecondsToFinish(0.005f);
    } else {
        //active_particle_manager_.OnKeyboardEvent(event_type, scancode);
    }
}

void SparkPropagation::Update(float dt) {
    grid_tick_timer_.Update(dt);
    if (!grid_tick_timer_.DidFinish()) return;

    grid_tick_timer_.Reset();
    grid_.UpdateCells(dt);
}

void SparkPropagation::Render() {
    grid_.RenderCells();
}
