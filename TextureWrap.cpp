//
// Created by luniminex on 3/16/23.
//

#include "TextureWrap.h"


TextureWrap::TextureWrap() {
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
}

TextureWrap::TextureWrap(const std::string &path, SDL_Renderer *renderer) {
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;

    LoadFromFile(path, renderer);
}

bool TextureWrap::LoadFromFile(const std::string &path, SDL_Renderer* renderer) {
    if(path.empty()){
        std::cout << "Path is empty" << std::endl;
        return false;
    }
    if(texture_ != nullptr){
        SDL_DestroyTexture(texture_);
    }

    SDL_Surface* surf = IMG_Load(path.c_str());
    if(surf == nullptr){
        std::cout << "Could not create a surface" << std::endl;
        return false;
    }

    texture_ = SDL_CreateTextureFromSurface(renderer, surf);
    if(texture_ == nullptr){
        std::cout << "Could not create texture from surface" << std::endl;
        SDL_FreeSurface(surf);
        return false;
    }
    if(SDL_QueryTexture(texture_, nullptr, nullptr, &width_, &height_) != 0){
        std::cout << "Error in texture" << std::endl;
    }

    SDL_FreeSurface(surf);
    return true;
}

void TextureWrap::RenderTextureAt(int x, int y, int w, int h, SDL_Renderer *renderer) {
    SDL_Rect destRect = { .x = x, .y = y, .w = w, .h = h};
    SDL_RenderCopy(renderer, texture_, nullptr, &destRect);
}

void TextureWrap::SetAsRenderTarget(SDL_Renderer *renderer) {
    SDL_SetRenderTarget(renderer, texture_);
}

void TextureWrap::SetBlendMode(SDL_BlendMode blendMode) {
    SDL_SetTextureBlendMode(texture_, blendMode);
}

TextureWrap::~TextureWrap() {
    SDL_DestroyTexture(texture_);
}

bool TextureWrap::CreateBlankTexture(int width, int height, SDL_Renderer* renderer, SDL_TextureAccess textureAccess) {
    texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, textureAccess, width, height);
    if(texture_ == nullptr){
        std::cout << "Could not create a blank texture" << std::endl;
        return false;
    }
    width_ = width;
    height_ = height;

    return true;
}

void TextureWrap::RenderTextureAt(int x, int y, SDL_Renderer* renderer, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderDest = {x, y, width_, height_};
    if (clip != nullptr) {
        renderDest.w = clip->w;
        renderDest.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, texture_, clip, &renderDest, angle, center, flip);
}
