#include <SDL2/SDL.h>

#include <iostream>

#include "engine/Engine.h"

class Game : public IGame {
public:
    Game(Engine& engine) : engine_(engine) {}
    void Update(float dt) override {}
    void Render() override { engine_.DrawRectangle({50.f, 50.f, 10.f, 10.f}); }

private:
    Engine& engine_;
};

int main(int argc, char* argv[]) {
    Engine engine("Hola", 200, 200);
    Game game(engine);
    engine.Run(game);

    return 0;
}
