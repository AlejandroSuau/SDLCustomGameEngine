#include <SDL2/SDL.h>

#include <iostream>

#include "engine/Engine.h"

class Game : public IGame {
public:
    Game() : engine_("Hola", 200, 200) {}
    
    void Start() override { engine_.Run(*this); }
    void Update(float dt) override {}
    void Render() override { engine_.DrawRectangle({50.f, 50.f, 10.f, 10.f}); }

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override {}
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override {}

private:
    Engine engine_;
};

int main(int argc, char* argv[]) {    
    Game game;
    game.Start();

    return 0;
}
