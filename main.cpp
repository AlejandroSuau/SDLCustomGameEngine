#include <SDL2/SDL.h>

#include <iostream>

#include "engine/Engine.h"

int main(int argc, char* argv[]) {
    Engine engine("Hola", 200, 200);
    engine.Run();

    return 0;
}
