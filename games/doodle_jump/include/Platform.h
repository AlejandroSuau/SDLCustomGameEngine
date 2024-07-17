#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

#include "engine/utils/Vec2.h"

class Platform : public ICollidable {
public:
    Platform(Engine& engine, Vec2 position);
    ~Platform();

    void Update(float dt);
    void Render();

    Vec2 GetPosition() const;
    void SetPosition(Vec2 position);

    // ICollidable
    const Rectangle& GetBoundingBox() const override;
    void OnCollision(ICollidable& other) override;
    unsigned int GetLayer() const override;
    unsigned int GetMask() const override;

private:
    Engine& engine_;
    Rectangle rect_;
};
