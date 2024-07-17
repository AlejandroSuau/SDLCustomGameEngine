#include <SDL2/SDL.h>

#include <iostream>
#include <filesystem>
#include <array>
#include <cmath>

#include "engine/Engine.h"
#include "engine/Circle.h"
#include "engine/timer/CountdownTimer.h"

class CirclePlayer {
public:
    CirclePlayer(Engine& engine, float x, float y) 
        : engine_(engine)
        , position_{x, y}
        , velocity_{50.f, 100.f}
        , acceleration_{0.f, 0.f}
        , mass_(2.f)
        , radius_(sqrt(mass_) * 20.f) {}

    void Update(float dt) {
        Edges();
        velocity_ += acceleration_;
        position_ += velocity_ * dt;
        acceleration_ *= 0;
    }
    
    void Render() {
        engine_.DrawCircle({radius_, position_});
    }

    void Edges() {
        const auto width = engine_.GetFWindowWidth();
        const auto height = engine_.GetFWindowHeight();
        if (position_.x + 2.f*radius_ > width) {
            position_.x = width - 2.f*radius_;
            velocity_.x *= -1;
        } else if (position_.x < 0.f) {
            position_.x = 0.f;
            velocity_.x *= -1;
        }

        if (position_.y + 2.f*radius_> height) {
            position_.y = height - 2.f*radius_;
            velocity_.y *= -1;
        } else if (position_.y < 0.f) {
            position_.y = 0.f;
            velocity_.y *= -1;
        }
    }

    Engine& engine_;
    Vec2 position_;
    Vec2 velocity_;
    Vec2 acceleration_;
    float mass_;
    float radius_;
    bool is_colliding_;
};

class Game : public IGame {
public:
    Game() 
        : engine_("Hola", 200, 200)
        , animation_timer_(0.15f)
        , current_texture_index_(0)
        , ball_(engine_, 10.f, 10.f) {
        // Helper for knowing the path.
        // std::cout << "Current path is " << std::filesystem::current_path() << '\n';
        flappy_textures_[0] = engine_.LoadTexture("assets/flappy_bird/yellowbird-upflap.png");
        flappy_textures_[1] = engine_.LoadTexture("assets/flappy_bird/yellowbird-midflap.png");
        flappy_textures_[2] = engine_.LoadTexture("assets/flappy_bird/yellowbird-downflap.png");
    }
    
    void Start() override { engine_.Run(*this); }
    
    void Update(float dt) override {
        ball_.Update(dt);

        are_circles_colliding = circle_1_.CollidesWith(circle_2_);

        const auto dx = 50.f * dt;
        const auto dy = 50.f * dt;
        if (pressed_keys_[0]) circle_1_.center_.y -= dy;
        if (pressed_keys_[1]) circle_1_.center_.x -= dx;
        if (pressed_keys_[2]) circle_1_.center_.x += dx;
        if (pressed_keys_[3]) circle_1_.center_.y += dy;

        animation_timer_.Update(dt);
        if (!animation_timer_.DidFinish()) return;

        animation_timer_.Reset();
        current_texture_index_ = ++current_texture_index_ % flappy_textures_.size();
    }

    void Render() override {
        ball_.Render();
        engine_.RenderTexture(
            flappy_textures_[current_texture_index_],
            {0.f, 0.f, 34.f, 24.f},
            {50.f, 50.f, 34.f, 24.f});
    }

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override {}
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override {
        const auto is_key_down = (event_type == EKeyEventType::KEY_DOWN);
        switch(scancode) {
            case SDL_SCANCODE_UP: pressed_keys_[0] = is_key_down; break;
            case SDL_SCANCODE_LEFT: pressed_keys_[1] = is_key_down; break;
            case SDL_SCANCODE_RIGHT: pressed_keys_[2] = is_key_down; break;
            case SDL_SCANCODE_DOWN: pressed_keys_[3] = is_key_down; break;
        }
    }

private:
    Engine engine_;
    CountdownTimer animation_timer_;
    std::array<SDL_Texture*, 3> flappy_textures_;
    std::size_t current_texture_index_;

    std::array<bool, 4> pressed_keys_{{false, false, false, false}};

    CirclePlayer ball_;
    Circle circle_1_ {20, Vec2{50, 50}};
    Circle circle_2_ {10, Vec2{25, 25}};
    Color circle_color_ {100, 150, 200, 255};
    bool are_circles_colliding = true;

};

int main(int argc, char* argv[]) {    
    Game game;
    game.Start();

    return 0;
}
