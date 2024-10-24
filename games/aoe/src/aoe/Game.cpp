#include "aoe/Game.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <tuple>

static const int kGameWidth = 640;
static const int kGameHeight = 480;

static const int kGameMapWidth = 2048;
static const int kGameMapHeight = 1024;

// SDL_Init

// TTF_Init

// Todavia no importa quizas SDL_Image

Game::Game() 
    : sdl_initializer_(std::make_unique<SDLInitializer>())
    , sdl_ttf_initializer_(std::make_unique<SDLTTFInitializer>())
    , window_(
        SDL_CreateWindow(
            "game",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            kGameWidth,
            kGameHeight,
            0),
        SDL_DestroyWindow)
    , renderer_(
        SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer)
    , is_running_(false)
    , map_(kGameMapWidth, kGameMapHeight)
    , unit_mover_(map_, 0, 0, 0, 0) {
    if (!window_ || !renderer_) {
        throw std::runtime_error(
            std::string("Error creating the game") + SDL_GetError());
    }
    
    SDL_SetRenderDrawBlendMode(renderer_.get(), SDL_BLENDMODE_BLEND);

    font_ = TTF_OpenFont("assets/fonts/slkscre.ttf", 14);
    if (!font_) {
        std::runtime_error("Failed loading the font: " + std::string(TTF_GetError()) + "\n");
    }
}

Game::~Game() {
    TTF_CloseFont(font_);
}

void Game::Run() {
    // TEXTURE
    SDL_Color text_color {255, 255, 255, 255};

    SDL_Surface* text_surface = TTF_RenderText_Solid(font_, "Buen trabajo Alejandro!", text_color);
    if (!text_surface) {
        std::cerr << " Error: " << SDL_GetError() << "\n";
        throw std::runtime_error("Error al crear la surface: " + std::string(SDL_GetError()));
    }
    
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer_.get(), text_surface);
    if (!text_texture) {
        throw std::runtime_error("Error al crear la texture: " + std::string(SDL_GetError()));
    }

    SDL_Rect text_rect {100, 100, text_surface->w, text_surface->h};
    SDL_FreeSurface(text_surface);
    // END TEXTURE

    is_running_ = true;
    SDL_ShowWindow(window_.get());

    /*auto& u = units_.emplace_back(std::make_unique<Unit>(16.f * 2.f, 16.f * 2.f));
    auto [row_from, col_from] = map_.FromCoordsToRowCol(u->GetX(), u->GetY());
    std::cout << "From [" << row_from << ", " << col_from << "]\n";
    map_.Occupy(row_from, col_from);*/
    
    from_row_ = 2;//row_from;
    from_col_ = 6;//col_from;
    placing_from_ = true;
    
    to_row_ = 2;
    to_col_ = 1;

    map_.SetIsWalkable(1, 3, false);
    map_.SetIsWalkable(2, 3, false);

    unit_mover_.Reset(from_row_, from_col_, to_row_, to_col_);

    //u->SetPosition(105.f, 105.f);
    const int FPS = 60;  // Número de frames por segundo deseados
    const int frameDelay = 1000 / FPS;  // Duración de cada frame en milisegundos

    Uint32 frameStart;
    int frameTime;

    while (is_running_) {
        // Timestamp para calcular el tiempo de inicio del frame
        frameStart = SDL_GetTicks();
        // Timestamp

        HandleEvents();
        // Update
        Update();

        if (should_step) {
            unit_mover_.Step(*renderer_.get(), *font_);
            should_step = false;
        }

        //Render();

        auto* renderer = renderer_.get();
        SDL_RenderClear(renderer);
        
        // Render Game
        map_.Render(*renderer);
        for (auto& unit : units_) {
            unit->Render(*renderer);
        }
        unit_mover_.Render(*renderer);

        if (left_button_data_.is_button_down_) {
            SDL_RenderDrawRect(renderer, &left_button_data_.rect_);
        }

        SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
        // End render game

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyTexture(text_texture);
}

void Game::Update() {

}

void Game::Render() {
    auto* renderer = renderer_.get();
    SDL_RenderClear(renderer);
    
    // Render Game
    map_.Render(*renderer);

    for (auto& unit : units_) {
        unit->Render(*renderer);
    }

    if (left_button_data_.is_button_down_) {
        SDL_RenderDrawRect(renderer, &left_button_data_.rect_);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running_ = false;
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_D) {
            should_step = true;
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_R) {
            unit_mover_.Reset(from_row_, from_col_, to_row_, to_col_);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT && !left_button_data_.is_button_down_) {
                left_button_data_.is_button_down_ = true;
                left_button_data_.first_button_down_x_ = static_cast<float>(event.button.x);
                left_button_data_.first_button_down_y_ = static_cast<float>(event.button.y);
                left_button_data_.current_button_down_x_ = left_button_data_.first_button_down_x_;
                left_button_data_.current_button_down_y_ = left_button_data_.first_button_down_y_;
                left_button_data_.rect_.x = static_cast<int>(event.button.x);
                left_button_data_.rect_.y = static_cast<int>(event.button.y);
                left_button_data_.rect_.w = (static_cast<int>(event.button.x) - static_cast<int>(left_button_data_.first_button_down_x_));
                left_button_data_.rect_.h = (static_cast<int>(event.button.y) - static_cast<int>(left_button_data_.first_button_down_y_));

                const auto [row, col] = map_.FromCoordsToRowCol(left_button_data_.rect_.x, left_button_data_.rect_.y);
                // Set occupied row, col
                map_.SetIsWalkable(row, col, !(map_.IsWalkable(row, col)));
            }
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                left_button_data_.is_button_down_ = false;
                left_button_data_.did_move_ = false;    
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                const auto [row, col] = map_.FromCoordsToRowCol(static_cast<int>(event.button.x), static_cast<int>(event.button.y));
                if (placing_from_) {
                    from_row_ = row;
                    from_col_ = col;
                } else {
                    to_row_ = row;
                    to_col_ = col;
                }
                unit_mover_.Reset(from_row_, from_col_, to_row_, to_col_);
                placing_from_ = !placing_from_;
            }
        } else if (event.type == SDL_MOUSEMOTION) {
            if (left_button_data_.is_button_down_) {
                left_button_data_.did_move_ = true;
                left_button_data_.current_button_down_x_ = static_cast<float>(event.button.x);
                left_button_data_.current_button_down_y_ = static_cast<float>(event.button.y);
                left_button_data_.rect_.w = (static_cast<int>(event.button.x) - static_cast<int>(left_button_data_.first_button_down_x_));
                left_button_data_.rect_.h = (static_cast<int>(event.button.y) - static_cast<int>(left_button_data_.first_button_down_y_));
                
                
                std::cout << "First: x: " << left_button_data_.first_button_down_x_;
                std::cout << "y: " << left_button_data_.first_button_down_y_ << "\n\n";

                std::cout << "x: " << left_button_data_.current_button_down_x_;
                std::cout << ", y: " << left_button_data_.current_button_down_y_ << "\n";
            }
        }
        // DOWN
        // Click izquierda => select
        // Click izquierdo + drag => draw rectangle area
        // Click derecho move

        // UP
        // click izquierdo up => si estaba dragging select en el area
    }
}
/*
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window_;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer_;
    
    bool is_running_;

    void Init();
    void HandleEvents();
};*/
