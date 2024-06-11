#pragma once

#include "engine/Rectangle.h"

class Entity {
public:

    void Update(float dt);
    void Render();

    const Rectangle& GetRect() const;
    
protected:
    Rectangle rect_;
};
