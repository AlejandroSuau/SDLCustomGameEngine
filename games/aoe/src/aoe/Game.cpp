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
    , unit_mover_(map_) {
    if (!window_ || !renderer_) {
        throw std::runtime_error(
            std::string("Error creating the game") + SDL_GetError());
    }
    
    SDL_SetRenderDrawBlendMode(renderer_.get(), SDL_BLENDMODE_BLEND);

    font_ = TTF_OpenFont("assets/fonts/slkscre.ttf", 26);
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

    auto& u = units_.emplace_back(std::make_unique<Unit>(16.f * 5.f, 16.f * 5.f));
    auto map_coords = map_.FromCoordsToRowCol(u->GetX(), u->GetY());
    std::cout << std::get<0>(map_coords) << " " << std::get<1>(map_coords) << "\n";
    const auto row_from = std::get<0>(map_coords);
    const auto col_from = std::get<1>(map_coords);
    map_.Occupy(row_from, col_from);
    
    const auto path = unit_mover_.FindPath(row_from, col_from, 0, 0);
    std::cout << "Path:\n";
    for (const auto [x, y] : path) {
        std::cout << "x: " << x << ", y: " << y << "\n";
    }

    //u->SetPosition(105.f, 105.f);

    while (is_running_) {
        // Timestamp

        HandleEvents();
        Update();
        //Render();

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

        SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
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
            }
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                left_button_data_.is_button_down_ = false;
                left_button_data_.did_move_ = false;    
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
