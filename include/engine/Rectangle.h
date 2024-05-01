#pragma once

struct Rectangle {
    Rectangle(float x_, float y_, float w_, float h_) 
        : x(x_), y(y_), w(w_), h(h_) {}
    Rectangle() : x(0.f), y(0.f), w(0.f), h(0.f) {}
    
    float x, y, w, h;
};
