//
// Created by luniminex on 3/16/23.
//

#include "Box.h"

Box::Box(int x, int y, int w, int h) {
    body_.x = x;
    body_.y = y;
    body_.w = w;
    body_.h = h;
}

Box::Box(int x, int y, int w, int h, SDL_Color clr) {
    body_.x = x;
    body_.y = y;
    body_.w = w;
    body_.h = h;
    color_ = clr;
}

void Box::SetColor(SDL_Color clr) {
    color_ = clr;
}

void Box::Update(const float& dt) {

}

void Box::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    SDL_RenderFillRect(renderer, &body_);
}

SDL_Color &Box::GetColor() {
    return color_;
}


SDL_Rect &Box::GetBody() {
    return body_;
}
