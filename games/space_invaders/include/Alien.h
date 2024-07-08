#pragma once

#include <SDL2/SDL_image.h>

#include "engine/Engine.h"
#include "engine/Rectangle.h"
#include "engine/utils/Vec2.h"

#include "engine/collision/ICollidable.h"

#include <array>

enum class EAlienMovementDirection {
    RIGHT,
    LEFT,
    DOWN
};

class Alien : public ICollidable {
public:
    Alien(Engine& engine, Vec2 position, std::array<Rectangle, 2> source_rects);
    ~Alien();

    void LoadTextures();
    void MovementStep(EAlienMovementDirection movement_direction);
    void Render();

    void Hit();

    void SetPosition(Vec2 position);
    Vec2 GetPosition() const;
    bool IsAlive() const;
    bool IsMarkedForDestroy() const;

    const Rectangle& GetRectangle() const;

    // ICollidable
    const Rectangle& GetBoundingBox() const override;
    void OnCollision(ICollidable& other) override;
    unsigned int GetLayer() const override;
    unsigned int GetMask() const override;

private:
    Engine& engine_;
    Rectangle rect_;
    SDL_Texture* texture_atlas_;
    std::array<Rectangle, 2> source_rects_;
    std::size_t current_source_index_;
    int lifes_;
    bool is_marked_for_destroy_;
};
