#include <SDL2/SDL.h>

#include <iostream>
#include <filesystem>
#include <array>

#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

class Game : public IGame {
public:
    Game() 
        : engine_("Hola", 200, 200)
        , animation_timer_(0.15f)
        , current_texture_index_(0) {
        // Helper for knowing the path.
        // std::cout << "Current path is " << std::filesystem::current_path() << '\n';
        flappy_textures_[0] = engine_.LoadTexture("assets/flappy_bird/yellowbird-upflap.png");
        flappy_textures_[1] = engine_.LoadTexture("assets/flappy_bird/yellowbird-midflap.png");
        flappy_textures_[2] = engine_.LoadTexture("assets/flappy_bird/yellowbird-downflap.png");
    }
    
    void Start() override { engine_.Run(*this); }
    
    void Update(float dt) override {
        animation_timer_.Update(dt);
        if (!animation_timer_.DidFinish()) return;

        animation_timer_.Reset();
        current_texture_index_ = ++current_texture_index_ % flappy_textures_.size();
    }

    void Render() override {
        engine_.RenderTexture(
            flappy_textures_[current_texture_index_],
            {0.f, 0.f, 34.f, 24.f},
            {50.f, 50.f, 34.f, 24.f});
    }

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override {}
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override {}

private:
    Engine engine_;
    CountdownTimer animation_timer_;
    std::array<SDL_Texture*, 3> flappy_textures_;
    std::size_t current_texture_index_;
};

int main(int argc, char* argv[]) {    
    Game game;
    game.Start();

    return 0;
}
