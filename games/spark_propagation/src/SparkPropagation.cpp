#include "spark_propagation/include/SparkPropagation.h"

#include "spark_propagation/include/Constants.h"

SparkPropagation::SparkPropagation() 
    : engine_("Spark Propagation", 800, 600)
    , grid_(engine_, 800, 600)
    , grid_tick_timer_(kSpawnSparkTickTime) {}

void SparkPropagation::Start() {
    engine_.Run(*this);
}

void SparkPropagation::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    if (event_type != EMouseEventType::LEFT_DOWN) return;
    
    grid_.SpawnSparkInCoords(x, y);
}

void SparkPropagation::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE) {
        grid_.ClearAllParticles();
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
