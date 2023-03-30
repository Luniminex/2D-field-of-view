//
// Created by luniminex on 3/16/23.
//

#ifndef LIGHTINGEXAMPLE_TEXTUREWRAP_H
#define LIGHTINGEXAMPLE_TEXTUREWRAP_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class TextureWrap{
public:
    TextureWrap();

    TextureWrap(const std::string &path, SDL_Renderer* renderer);

    bool LoadFromFile(const std::string &path, SDL_Renderer* renderer);

    bool CreateBlankTexture(int width, int height, SDL_Renderer* renderer, SDL_TextureAccess textureAccess);

    void SetAsRenderTarget(SDL_Renderer* renderer);

    void SetBlendMode(SDL_BlendMode blendMode);

    void RenderTextureAt(int x, int y, int w, int h, SDL_Renderer* renderer);

    void RenderTextureAt(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr, double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    ~TextureWrap();
private:
    SDL_Texture* texture_;
    int width_;
    int height_;
};

#endif //LIGHTINGEXAMPLE_TEXTUREWRAP_H
