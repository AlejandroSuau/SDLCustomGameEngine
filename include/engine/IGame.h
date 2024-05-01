#pragma once

class IGame {
public:
    virtual ~IGame() = default;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};
