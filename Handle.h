//
// Created by luniminex on 3/16/23.
//

#ifndef LIGHTINGEXAMPLE_HANDLE_H
#define LIGHTINGEXAMPLE_HANDLE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

struct WindowInfo{
    std::string title;
    Uint32 win_flags;
    Uint32 renderer_flags;
    int height;
    int width;
    bool open;
};

class Handle {

public:
    Handle();
    static std::shared_ptr<Handle> GetInstance();
    bool Init();
    bool CreateWindow(const std::string& title, int width, int height, Uint32 window_flags);
    bool CreateRenderer(Uint32 renderer_flags);
    WindowInfo GetWindowInfo();
    SDL_Renderer* GetRenderer();
private:
    static std::shared_ptr<Handle> instance_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    WindowInfo win_info_;
};


#endif //LIGHTINGEXAMPLE_HANDLE_H
