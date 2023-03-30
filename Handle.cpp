//
// Created by luniminex on 3/16/23.
//

#include "Handle.h"

std::shared_ptr<Handle> Handle::instance_;

std::shared_ptr<Handle> Handle::GetInstance() {
    if(instance_ == nullptr){
        Handle::instance_ = std::make_shared<Handle>();
        std::cout <<"Created Handle\n" << std::endl;
    }
    return instance_;
}

Handle::Handle() {
    win_info_.open = false;
    win_info_.height = 0;
    win_info_.width = 0;
    win_info_.title = "";
    win_info_.renderer_flags = 0;
    win_info_.win_flags = 0;
}

bool Handle::CreateWindow(const std::string &title, int width, int height, Uint32 window_flags) {
    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, win_info_.win_flags);
    if(window_ == nullptr){
        std::cout << "Failed to create window" << std::endl;
        return false;
    }
    win_info_.height = height;
    win_info_.width = width;
    win_info_.title = title;
    win_info_.win_flags = window_flags;
    win_info_.open = true;
    std::cout << "Created window" << std::endl;
    return true;
}

bool Handle::CreateRenderer(Uint32 renderer_flags) {
    renderer_ = SDL_CreateRenderer(window_, -1, win_info_.renderer_flags);
    if(renderer_ == nullptr){
        std::cout << "Failed to create renderer" << std::endl;
        return false;
    }
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    win_info_.renderer_flags = renderer_flags;
    std::cout << "Created renderer" << std::endl;
    return true;
}


bool Handle::Init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Failed to initialize SDL" << std::endl;
        return false;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        std::cout << "Failed to initialize SDL/IMG" << std::endl;
        return false;
    }
    return true;
}

SDL_Renderer *Handle::GetRenderer() {
    return renderer_;
}

WindowInfo Handle::GetWindowInfo() {
    return win_info_;
}

